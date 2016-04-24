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
#include "tunnel.h"

#define MSG_COUNT 1

#define RPL_HDR_SIZE 2

enum {ST_READY, ST_REQUEST_COMES, ST_WAITNG_I2C_WRITE, ST_WAITNG_I2C_READ}state;
static Tunnel_msg msg[MSG_COUNT];
static Queue msg_queue;
static void *queue_array[MSG_COUNT];

static Tunnel_msg *request;
static size_t request_size;

static int data01;

void tunnel_reset_data01()
{
    data01 = 0;
}

int armed_rx = 0;
int armed_tx = 0;

static inline void send(Tunnel_msg *msg, size_t size)
{
    if(usb_arm_ep(TUNNEL_EP, USB_EP_IN, (void*)msg, size, data01) == USB_RW_REQ_OK)
    {
        data01 ^= 1;
        armed_tx++;
    }
    else
        queue_push(&msg_queue, msg);
    
}

static void arm_rx()
{
    while(1)
    {
        void * new_buf = queue_pop(&msg_queue);
        
        if(!new_buf)
        {                  
            //debughalt();
            break;
        }
        
        if( usb_arm_ep(TUNNEL_EP, USB_EP_OUT, new_buf, sizeof(Tunnel_msg), 1) != USB_RW_REQ_OK)
        {
            queue_push(&msg_queue, new_buf);
            break;
        }
        else
            armed_rx++;
    }
}

static void callback_in(void *buf, size_t size, void * usrptr)
{   //reply was sent
    (void) usrptr;
    (void) size;
    queue_push(&msg_queue, buf);
    
    armed_tx--;
}

static void callback_out(void *buf, size_t size, void * usrptr)
{   //request comes
    (void) usrptr;
    (void) size;
    
    armed_rx--;
        
    if(state != ST_READY)
    {
        ((Tunnel_msg*)buf)->in.error = TUNNEL_ERROR_REQINPORGRESS;
        send(buf, RPL_HDR_SIZE);
    }
    else
    {
        request = buf;
        request_size = size;
        state = ST_REQUEST_COMES;
    }
  
    arm_rx();
}

void tunnel_init()
{
    int i;
    state = ST_READY;
    
    tunnel_reset_data01();
    
    queue_init(&msg_queue, queue_array, MSG_COUNT);
    
    for(i=0; i<MSG_COUNT; i++)
        queue_push(&msg_queue, &msg[i]);
    
    request = NULL;
    
    usb_set_transfer_callback(TUNNEL_EP, USB_EP_IN, callback_in,  NULL);
    usb_set_transfer_callback(TUNNEL_EP, USB_EP_OUT, callback_out, NULL);
    usb_enable_ep(TUNNEL_EP, USB_EP_IN,  true, false);
    usb_enable_ep(TUNNEL_EP, USB_EP_OUT, true, false);
    
    arm_rx();
}

void tunnel_task()
{
    switch(state)
    {
        case ST_READY:
            if(request)
            {
                queue_push(&msg_queue, request);
                request = NULL;
            }
            
            arm_rx();            
            if ( usb_queued_bufs(TUNNEL_EP, USB_EP_OUT) == 0 &&
                 usb_queued_bufs(TUNNEL_EP, USB_EP_IN)  == 0 &&
                 queue_count(&msg_queue) == 0)
                queue_push(&msg_queue, &msg[0]);
                
            break;
        case ST_REQUEST_COMES:
            
            switch(request->out.type)
            {
                case TUNNEL_REQ_PING:
                    send(request, RPL_HDR_SIZE);
                    request = NULL;
                    state = ST_READY;
                    break;
                case TUNNEL_REQ_READ:
                case TUNNEL_REQ_WRITE:
                    if(tuner_com_state()==TUNER_COM_BUSY)
                    {
                        request->in.error=TUNNEL_ERROR_I2CBUSY;
                        send(request, RPL_HDR_SIZE);
                        request = NULL;
                        state = ST_READY;
                    }
                    else
                    {
                        if(request->out.type == TUNNEL_REQ_READ)
                        {  
                        
                            int tuner = request->out.tuner;
                            size_t read_size = request->out.rw_size;
                            
                            if(read_size > sizeof(Tuner_read_reply) || tuner > 1)
                            {
                                request->in.error=TUNNEL_ERROR;
                                send(request, RPL_HDR_SIZE);
                                request = NULL;
                                state = ST_READY;
                            }
                            else
                            {                                
                                tuner_read(tuner, &request->in.reply, read_size);
                                state = ST_WAITNG_I2C_READ;
                                request_size = RPL_HDR_SIZE + read_size;
                            }
                        }
                        else
                        {
                            int tuner = request->out.tuner;
                            size_t write_size = request->out.rw_size;
                            
                            if(write_size > 16 || tuner > 1)
                            {
                                request->in.error=TUNNEL_ERROR;
                                send(request, RPL_HDR_SIZE);
                                request = NULL;
                                state = ST_READY;
                            }
                            else
                            {                           
                                tuner_write(tuner, request->out.cmd, write_size);
                                state = ST_WAITNG_I2C_WRITE;
                            }
                        }
                    }
                    break;
                default:
                    request->in.error = TUNNEL_ERROR_BADTYPE;
                    send(request, RPL_HDR_SIZE);
                    state = ST_READY;
                    request = NULL;
            }
            break;
        case ST_WAITNG_I2C_READ:
        case ST_WAITNG_I2C_WRITE:
            switch(tuner_com_state())
            {
                case TUNER_COM_BUSY:
                    break;
                
                case TUNER_COM_IDLE:
                case TUNER_COM_DEV_BUSY:
                    request->in.error = TUNNEL_ERROR_OK;
                    send(request, request_size);
                    request = NULL;
                    state = ST_READY;
                    break;
                    
                default:
                    request->in.error = TUNNEL_ERROR_I2C;
                    send(request, RPL_HDR_SIZE);
                    request = NULL;
                    state = ST_READY;
                    break;
            }
            break;
    }
}
