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

Libdfmt_error libdfmt_prop_set(Libdfmt_tuner *tuner,
                               unsigned prop, unsigned value)
{
    char arg[5];
    arg[0] = 0;

    arg[1] = prop >> 8 & 0xff;
    arg[2] = prop & 0xff;

    arg[3] = value >> 8 & 0xff;
    arg[4] = value & 0xff;

    return libdfmt_cmd_send(tuner, LIBDFMT_CMD_SET_PROPERTY, arg, sizeof(arg));
}

Libdfmt_error libdfmt_prop_get(Libdfmt_tuner *tuner,
                               unsigned prop, unsigned *value)
{
    Libdfmt_error err;
    char reply[4];
    char arg[3];

    arg[0] = 0;

    arg[1] = prop >> 8 & 0xff;
    arg[2] = prop & 0xff;


    err = libdfmt_cmd_send(tuner, LIBDFMT_CMD_GET_PROPERTY, arg, sizeof(arg));
    if(err != LIBDFMT_OK)
        return err;

    err = libdfmt_cmd_recv_reply(tuner, reply, sizeof(reply));
    if(err != LIBDFMT_OK)
        return err;

    *value = reply[2]<<8 | reply[3];

    return err;
}
