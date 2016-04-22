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

#ifndef SHARED_H
#define	SHARED_H

#include <inttypes.h>

#define USB_VID 0x04D8
#define USB_PID 0xF32C

#define TUNNEL_INTERFACE_ID 2

#define TUNNEL_EP 0x02
#define TUNNEL_EP_OUT TUNNEL_EP
#define TUNNEL_EP_IN (TUNNEL_EP | (1<<7))

typedef struct{

    union{
        uint8_t byte;
        struct {
            char STCINT:1;       //Tune complete has been triggered.
            char reserved1_2:2;
            char RSQINT:1;       //Received Signal Quality measurement has been triggered.
            char reserved4_5:2;
            char ERR:1;          //Error
            char CTS:1;          //Clear to send next command.
        }bits;
    }STATUS;
    uint8_t ARGS[15];
}Tuner_read_reply;



typedef enum {
    TUNNEL_REQ_WRITE=0, TUNNEL_REQ_READ=1,TUNNEL_REQ_PING=2
}Tunnel_req_type;

typedef enum {
    TUNNEL_ERROR_OK=0, TUNNEL_ERROR_I2CBUSY=1, TUNNEL_ERROR_I2C=2,  
    TUNNEL_ERROR_TUNERNOTUP=3, TUNNEL_ERROR_REQINPORGRESS=4,
    TUNNEL_ERROR_BADTYPE = 5,
    TUNNEL_ERROR = 128
}Tunnel_error;

typedef struct
{
    char id;
    union {
        struct {
            char error;
            Tuner_read_reply reply;
        }in; //reply
        struct {
            char tuner;
            char type;
            char rw_size;
            uint8_t cmd[16];
        }out;//request
    };
}Tunnel_msg;

#endif	/* SHARED_H */
