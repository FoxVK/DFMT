#ifndef DEVICES_H
#define DEVICES_H

#include "libusb.h"

typedef enum {
    LIBDFMT_OK                      = 0,
    LIBDFMT_ERROR_TIMEOUT           =-1,
    LIBDFMT_ERROR_DEV_BUSY          =-2,
    LIBDFMT_ERROR_DEV_NOT_CONNECTED =-3,
    LIBDFMT_ERROR_DEV_IN_USE        =-4,
    LIBDFMT_ERROR_NO_PERMISSION     =-5,
    LIBDFMT_ERROR_INVALID_TUNER     =-6,
    LIBDFMT_ERROR_LUSB_GENERAL      =-7,
    LIBDFMT_ERROR_INTERNAL          =-8
}Libdfmt_error;

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
