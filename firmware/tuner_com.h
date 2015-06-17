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


#ifndef TUNER_COM_H
#define	TUNER_COM_H

#include <inttypes.h>
#include "shared.h"

void tuner_init();
void tuner_write(int tuner_id, void* data, size_t len);
void tuner_read(int tuner_id, void* data, size_t len);
void tuner_hold_in_rst(int state);
Tuner_com_state tuner_com_state();
size_t tuner_rwed_bytes();

void tuner_audio_run(int tuner_id, int state);
int16_t * tuner_audio_get(const int tuner_id);

#endif	/* TUNER_COM_H */

