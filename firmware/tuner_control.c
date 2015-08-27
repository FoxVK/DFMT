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

#include "tuner_control.h"
#include "inttypes.h"

#include "tuner_com.h"

static bool tuner_on    = false;
static int tuners_are_on = 0; 

void tuner_control_init()
{
    
}

void tuner_control_pwr(bool state) 
{
    tuner_on = state;
}

bool tuner_control_tun_ready()
{
    return (tuners_are_on == 3) ? true : false ;
}

void tuner_control_task()
{
    //TODO check it
    
    static uint8_t cmd_power_up[]   = {0x01, 0x00, 0xB5};
    static uint8_t cmd_power_down[] = {0x11};
    static uint8_t cmd_tune[]       = {0x20,0x01,0x24,0x9A,0x00}; //0x01 = inaccurate but fast tunning alowed to 93.7
    static uint8_t cmd_int_update[] = {0x14};
    static uint8_t cmd_int_clear[]  = {0x22, 0x01};
    static uint8_t cmd_dosr[]       = {0x12, 0x00, 0x01, 0x04, 0xBB, 0x80}; //sample rate
    static uint8_t cmd_refclk_presc[]= {0x12, 0x00, 0x02, 0x02, 0x10, 0x2F}; //1538461,538461538 / 47 -> 32733,2Hz bit 12 = 1 (colck from dclk) 0x102f
    static uint8_t cmd_refclk_freq[]= {0x12, 0x00, 0x02, 0x01, 0x7F, 0xDD}; //32733 0x7fdd

    static uint8_t * cmd_list[] = {
        NULL,
        cmd_power_up,
        cmd_refclk_freq, cmd_refclk_presc,
        cmd_tune, cmd_int_update, cmd_int_clear,
        cmd_dosr,
        NULL
    };

    static size_t cmd_sizes[] =
    {
        0,
        sizeof(cmd_power_up),
        sizeof(cmd_refclk_freq) ,sizeof(cmd_refclk_presc),
        sizeof(cmd_tune), sizeof(cmd_int_update), sizeof(cmd_int_clear),
        sizeof(cmd_dosr),
        0,

    };

    static enum {
        ST_DOWN = 0,
        ST_PWRUP,
        ST_RCLK_FREQ, ST_RCLK_PRESC,
        ST_TUNE, ST_TUNE_INT_UPDATE, ST_TUNE_INT_CLR,
        ST_DOSR,
        ST_UP,
    } state[] = {ST_DOWN, ST_DOWN};

    static enum {
        CST_DONE, CST_CHCK_REPLY, CST_READING
    } com_st[2] = {CST_DONE, CST_DONE};

    static Tuner_read_reply reply[2];
    static int tid = 1;     //ID of currently porcessed tunner

   
           
    {

        Tuner_com_state tun_s = tuner_com_state();

        static bool bus = false;
        if(tun_s == TUNER_COM_BUSY)
        {
            if(!bus)
                U1TXREG = 'B';
            bus = true;
        }
        else
        {
            if(bus)
                U1TXREG = 'b';
            bus = false;
        }


        if( tun_s == TUNER_COM_BUSY)
            return;

        tid = (tid+1)&1;

        Nop();

        switch(com_st[tid])
        {
            case CST_DONE:
                break;

            case CST_CHCK_REPLY:
                tuner_read(tid, &reply[tid], 1);
                com_st[tid] = CST_READING;
                return;

            case CST_READING:
                if(reply[tid].STATUS.bits.CTS)
                    com_st[tid] = CST_DONE;
                else
                {
                    com_st[tid] = CST_CHCK_REPLY;
                }
                return;
        }

        switch(state[tid])
        {
            case ST_UP:
                if(!tuner_on)
                {
                    tuner_hold_in_rst(1);
                    //tuner_audio_run(tid, 0);
                    state[tid] = ST_DOWN;
                }
                break;

            case ST_DOWN:
                if(tuner_on)
                {
                    //tuner_audio_run(tid, 1);
                    tuner_hold_in_rst(0);
                    state[tid]++;
                }
                break;

            case ST_TUNE_INT_CLR:
                if(!reply[tid].STATUS.bits.STCINT)
                {
                    state[tid] = ST_TUNE_INT_UPDATE;
                    break;
                }
                //do not put break here or another state

            default:
                tuner_write(tid, cmd_list[state[tid]], cmd_sizes[state[tid]]);
                com_st[tid] = CST_CHCK_REPLY;
                state[tid]++;
                break;
        }
        if(state[tid] != ST_UP)
            tuners_are_on &= ~(1 << tid);
        else
            tuners_are_on |=  (1 << tid);
    }
}
