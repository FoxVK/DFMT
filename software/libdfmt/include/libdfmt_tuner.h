#ifndef LIBDFMT_TUNER_H
#define LIBDFMT_TUNER_H

#include "libdfmt.h"

typedef struct Libdfmt_tuner{
    int tuner;
    int is_busy;
    Libdfmt_device *dev;
}Libdfmt_tuner;

#endif // LIBDFMT_TUNER_H
