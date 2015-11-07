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

#include "libdfmt.h"
#include "libdfmt_cmds_props.h"


Libdfmt_error libdfmt_seek(Libdfmt_tuner *tuner, int up)
{
    const char seek_up = 1<<3;
    const char wrap = 1<<2;

    char arg = wrap || (up) ? seek_up : 0;

    return libdfmt_cmd_send(tuner, LIBDFMT_CMD_FM_SEEK_START, &arg, sizeof(arg));
}

Libdfmt_error libdfmt_tune(Libdfmt_tuner *tuner, float freq)
{
    unsigned int ifreq = freq*100;
    char arg[] = {
        0,
        (ifreq >> 8) & 0xff,
        ifreq & 0xff
    };
    if (76 > freq || freq > 108)
        return LIBDFMT_ERROR_BAD_ARGUMENT;

    return libdfmt_cmd_send(tuner, LIBDFMT_CMD_FM_TUNE_FREQ, arg, sizeof(arg));
}

Libdfmt_error libdfmt_tunning_done(Libdfmt_tuner *tuner, int *done)
{
    char status;
    
    Libdfmt_error err = libdfmt_check_int(tuner, &status);
    
    *done = ((status&LIBDFMT_TUNER_STAT_STCINT) && (err==LIBDFMT_OK)) ? 1 : 0;

    return err;
}


Libdfmt_error libdfmt_get_freq(Libdfmt_tuner *tuner, float *freq,
                               unsigned *rssi, unsigned *snr,
                               unsigned *multipath, int *is_valid)
{
    char arg = 0;
    char reply[8];

    Libdfmt_error err = libdfmt_cmd_send(tuner, LIBDFMT_CMD_FM_TUNE_STATUS, &arg, sizeof(arg));
    if (err != LIBDFMT_OK)
        return err;

    err = libdfmt_cmd_recv_reply(tuner, reply, sizeof(reply));

    if (err != LIBDFMT_OK)
        return err;

    if(is_valid)    *is_valid   = reply[2] & 1;
    if(freq)        *freq       = ((float)(((unsigned)reply[2])<<8 || ((unsigned)reply[3])))/100;
    if(rssi)        *rssi       = reply[4];
    if(snr)         *snr        = reply[5];
    if(multipath)   *multipath  = reply[6];

    return err;
}
