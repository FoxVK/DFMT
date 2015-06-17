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

