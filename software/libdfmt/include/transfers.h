#ifndef TRANSFERS_H
#define TRANSFERS_H

#include "devices.h"

int transfers_cmd(Libdfmt_device *dev, int tuner,
                  unsigned char *cmd, size_t cmd_size);

int transfers_status_check(Libdfmt_device *dev, int tuner);
int transfers_int_check(Libdfmt_device *dev, int tuner);

int transfers_prop_set(Libdfmt_device *dev, int tuner,
                       unsigned int prop, unsigned int value);
int transfers_prop_get(Libdfmt_device *dev, int tuner,
                       unsigned int prop, unsigned int *value);

#endif // TRANSFERS_H
