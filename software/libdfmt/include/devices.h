#ifndef DEVICES_H
#define DEVICES_H

#include "libusb.h"

typedef struct Libdfmt_device{
    libusb_device *lusb_dev;
    libusb_device_handle *lusb_handle;
    struct Libdfmt_device *next;
    int present;
}Libdfmt_device;

typedef void(*Libdfmt_dev_callback)(Libdfmt_device*);

void libdfmt_scan_devs();
Libdfmt_device* libdfmt_get_all_devs();
Libdfmt_device* libdfmt_next(Libdfmt_device* current_dev);

int libdfmt_dev_open(Libdfmt_device *dev);
void libdfmt_dev_close(Libdfmt_device *dev);

void libdfmt_new_dev_cb    (Libdfmt_dev_callback callback);
void libdfmt_removed_dev_cb(Libdfmt_dev_callback callback);

unsigned int libdfmt_get_dev_address(Libdfmt_device *dev);


int dev_usb_send(Libdfmt_device *dev, void *buf, size_t buf_size, unsigned int timeout);
int dev_usb_receive(Libdfmt_device *dev, void *buf, size_t buf_size, unsigned int timeout);

void dev_init();
void dev_exit();

#endif // DEVICES_H
