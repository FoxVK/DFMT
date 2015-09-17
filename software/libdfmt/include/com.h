#ifndef COM_H
#define COM_H

#include <stddef.h>
#include "libusb.h"

typedef struct Libdfmt_device{
    int open;
    libusb_device *lusb_dev;
    libusb_device_handle *lusb_handle;
    struct Libdfmt_device *next;
}Libdfmt_device;

void com_init(int libusb_debug);
void com_exit();

int com_read (int tuner, void *data, size_t size, int timeout);
int com_write(int tuner, void *data, size_t size, int timeout);

#endif // COM_H_
