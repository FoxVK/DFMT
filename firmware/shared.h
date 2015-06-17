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

#define USB_VID 0x00a6
#define USB_PID 0xff01

#define TUNNEL_INTERFACE_ID 2
#define TUNNEL_EP_IN (0x02 | (1<<7))
#define TUNNEL_EP_OUT 0x02

#define TUNNEL_TUNER_SELECT_MASK 1
#define TUNNEL_RW_SELECT_MASK 2
#define TUNNEL_PING_MASK 4
#define TUNNEL_ERROR_MASK 128

typedef enum {
        TUNER_COM_IDLE, TUNER_COM_BUSY, TUNER_COM_WRONG_ADDR, TUNER_COM_WRITE_NAK, TUNER_COM_DEV_BUSY
    }Tuner_com_state;

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

#endif	/* SHARED_H */
