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

#ifndef TUNER_AUDIO_H
#define	TUNER_AUDIO_H

#define AUDIO_SAMPLE_CHAN_BYTES 2
#define AUDIO_PACKET_BUFS 5

#include <inttypes.h>

typedef struct {
    union {
        struct {
            int16_t left;
            int16_t right;
        };
        uint32_t both;
    }sample[48];
}AudioFrame;

void tuner_audio_init(); 

void* tuner_audio_get_buf(int tuner); 
bool  tuner_audio_put_buf(int tuner, void* buf); 

void tuner_audio_task();

#endif	/* TUNER_AUDIO_H */

