#ifndef LIBDFMT_DEVICE_H
#define LIBDFMT_DEVICE_H
#include "libusb.h"
#include "libdfmt_tuner.h"

struct Libdfmt_device{
    libusb_device *lusb_dev;
    libusb_device_handle *lusb_handle;
    struct Libdfmt_device *next;
    int present;
    Libdfmt_tuner tunerA, tunerB;
};

#endif // LIBDFMT_DEVICE_H
