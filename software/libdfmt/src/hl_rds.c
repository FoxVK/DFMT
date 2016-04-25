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

Libdfmt_error libdfmt_rds_receiving(Libdfmt_tuner *tuner, int receive)
{
    const uint16_t BLETHA_SFT = 14, BLETHB_SFT = 12, BLETHC_SFT = 10, BLETHD_SFT = 8;
    const uint16_t RDSEN = 1<<0;
    const uint16_t CORRECTED = 2;
    //const char NO_ERROR = 0;

    unsigned fm_rds_config = (CORRECTED<<BLETHA_SFT) | (CORRECTED<<BLETHB_SFT) |
                             (CORRECTED<<BLETHC_SFT) | (CORRECTED<<BLETHD_SFT) |
                             ((receive) ? RDSEN : 0);

    return libdfmt_prop_set(tuner, LIBDFMT_PROP_FM_RDS_CONFIG, fm_rds_config);
}

Libdfmt_error libdfmt_rds_read(Libdfmt_tuner *tuner, Libdfmt_rds_group *group, int *groups_cnt)
{
    const char INTACK       = 1<<0;
    //const char MTFIFO     = 1<<1;
    const char STATUSONLY   = 1<<2;
    char arg  = INTACK ;
         arg |= ((!group) ? STATUSONLY : 0);

    char reply[13];
    unsigned cnt;
    Libdfmt_error err;

    err = libdfmt_cmd_send(tuner, LIBDFMT_CMD_FM_RDS_STATUS, &arg, sizeof(arg));
    if(err != LIBDFMT_OK) return err;

    err = libdfmt_cmd_recv_reply(tuner, reply, sizeof(reply));
    if(err != LIBDFMT_OK) return err;

    cnt = reply[3];

    if(group && cnt != 0)
    {
        group->blockA = ((reply[ 4]<<8) & 0xFF00) | (reply[ 5] & 0x00FF );
        group->blockB = ((reply[ 6]<<8) & 0xFF00) | (reply[ 7] & 0x00FF );
        group->blockC = ((reply[ 8]<<8) & 0xFF00) | (reply[ 9] & 0x00FF );
        group->blockD = ((reply[10]<<8) & 0xFF00) | (reply[11] & 0x00FF );

        group->blockAvalid = (((reply[12]>>6) & 0x03) < 3) ? 1 : 0;
        group->blockBvalid = (((reply[12]>>4) & 0x03) < 3) ? 1 : 0;
        group->blockCvalid = (((reply[12]>>2) & 0x03) < 3) ? 1 : 0;
        group->blockDvalid = (((reply[12]   ) & 0x03) < 3) ? 1 : 0;
    }

    if(groups_cnt)
        *groups_cnt = cnt;

    return err;
}
