// <editor-fold defaultstate="collapsed" desc="Copyright">
/*
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
 
    Copyright: Pavel Kovar 2015 <pavel.kovar@vsetin.org>.
 */
// </editor-fold>
#include "tuner_com.h"
#include "drv/usb.h"
#include "drv/utils.h"
#include "shared.h"

#include "drv/debug_uart.h"

#define MSG_COUNT 6

enum {ST_READY, ST_REQUEST_COMES, ST_WAITNG_FOR_I2C}state;
static Tunnel_msg msg[MSG_COUNT];
static Queue msg_queue;
static void *queue_array[MSG_COUNT];

static Tunnel_msg *request;
static size_t request_size;

static inline void send(Tunnel_msg *msg, size_t size)
{
    usb_arm_ep(TUNNEL_EP, USB_EP_IN, (void*)msg, size, 0);
}

static void callback_in(void *buf, size_t size, void * usrptr)
{   //reply was sent
    (void) usrptr;
    (void) size;
    queue_push(&msg_queue, buf);
    
    static char *t = "buf_returned\r\n";
    debug_uart_write(t);
}

static void callback_out(void *buf, size_t size, void * usrptr)
{   //request comes
    (void) usrptr;
    (void) size;
    
    static char *t = "req comes\r\n";
    debug_uart_write(t);
    
    if(state = ST_READY)
    {
        ((Tunnel_msg*)buf)->in.error = TUNNEL_ERROR_REQINPORGRESS;
        send(buf, size);
    }
    request = buf;
    request_size = size;
    state = ST_REQUEST_COMES;
    
    usb_arm_ep(TUNNEL_EP, USB_EP_OUT, queue_pop(&msg_queue), sizeof(Tunnel_msg), 1);
}

void tunnel_init()
{
    int i;
    state = ST_READY;
    
    queue_init(&msg_queue, queue_array, MSG_COUNT);
    
    for(i=0; i<MSG_COUNT; i++)
        queue_push(&msg_queue, &msg[i]);
    
    request = NULL;
    
    usb_set_transfer_callback(TUNNEL_EP, USB_EP_IN, callback_in,  NULL);
    usb_set_transfer_callback(TUNNEL_EP, USB_EP_OUT, callback_out, NULL);
    usb_enable_ep(TUNNEL_EP, USB_EP_IN,  true, false);
    usb_enable_ep(TUNNEL_EP, USB_EP_OUT, true, false);
    
    usb_arm_ep(TUNNEL_EP, USB_EP_OUT, queue_pop(&msg_queue), sizeof(Tunnel_msg), 1);
    usb_arm_ep(TUNNEL_EP, USB_EP_OUT, queue_pop(&msg_queue), sizeof(Tunnel_msg), 1);  
}

void tunnel_task()
{
    static char *req_w = "tunnel write\n\r";
    static char *req_r = "tunnel read\n\r";
    static char *req_rw_bus = "tunnel rw i2c bussy\n\r";
    
    switch(state)
    {
        case ST_READY:
            if(request)
            {
                queue_push(&msg_queue, request);
                request = NULL;
            }
            break;
        case ST_REQUEST_COMES:
            
            switch(request->out.type)
            {
                case TUNNEL_REQ_PING:
                    send(request, request_size);
                    state = ST_READY;
                    break;
                case TUNNEL_REQ_READ:
                case TUNNEL_REQ_WRITE:
                    if(tuner_com_state()==TUNER_COM_BUSY)
                    {
                        debug_uart_write(req_rw_bus);
                        request->in.error=TUNNEL_ERROR_I2CBUSY;
                        send(request, request_size);
                        state = ST_READY;
                    }
                    else
                    {
                        if(request->out.type == TUNNEL_REQ_READ)
                        {   debug_uart_write(req_r);
                        
                            int tuner = request->out.tuner;
                            size_t read_size = request->out.rw_size;
                            
                            if(read_size > sizeof(Tuner_read_reply) || tuner > 1)
                            {
                                request->in.error=TUNNEL_ERROR;
                                send(request, request_size);
                                state = ST_READY;
                            }
                            else
                            {                                
                                tuner_read(tuner, &request->in.reply, read_size);
                                state = ST_WAITNG_FOR_I2C;
                            }
                        }
                        else
                        {
                            debug_uart_write(req_w);
                            
                            int tuner = request->out.tuner;
                            size_t write_size = request->out.rw_size;
                            
                            if(write_size > 16 || tuner > 1)
                            {
                                request->in.error=TUNNEL_ERROR;
                                send(request, request_size);
                                state = ST_READY;
                            }
                            else
                            {
                            
                                tuner_write(tuner, request->out.cmd, write_size);
                                state = ST_READY;

                                Tunnel_msg *ok_msg = (Tunnel_msg *)queue_pop(&msg_queue);
                                if(!ok_msg)
                                {
                                    static char *s = "PRUSER!!!\n\r";
                                }
                                ok_msg->in.error=TUNNEL_ERROR_OK;
                                ok_msg->id = request->id;
                                send(ok_msg, request_size);
                            }
                        }
                    }
                    break;
                default:
                    request->in.error = TUNNEL_ERROR_BADTYPE;
                    send(request, request_size);
                    state = ST_READY;
            }
            break;
        case ST_WAITNG_FOR_I2C:
            state = ST_READY;
            switch(tuner_com_state())
            {
                case TUNER_COM_BUSY:
                    state = ST_WAITNG_FOR_I2C;
                    break;
                
                case TUNER_COM_IDLE:
                case TUNER_COM_DEV_BUSY:
                    request->in.error = TUNNEL_ERROR_OK;
                    send(request, request_size);
                    break;
                    
                default:
                    request->in.error = TUNNEL_ERROR_I2C;
                    send(request, request_size);
                    break;
            }
            break;
    }
}
