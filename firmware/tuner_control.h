#ifndef TUNER_CONTROL_H
#define	TUNER_CONTROL_H

#include "drv/utils.h"

void tuner_control_init();
void tuner_control_task();

void tuner_control_pwr(bool state);
bool tuner_control_tun_ready();



#endif	/* TUNER_CONTROL_H */

