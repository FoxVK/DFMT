#include <libusb.h>
#include "libdfmt.h"
#include "libdfmt_device.h"
#include "libdfmt_tuner.h"
#include "shared.h"
#include "lusb_error_tr.h"

Libdfmt_error libdfmt_dev_open(Libdfmt_device *dev)
{
    int ret = libusb_open(dev->lusb_dev, &dev->lusb_handle);
    if(!ret)
        ret = libusb_claim_interface(dev->lusb_handle, TUNNEL_INTERFACE_ID);
    //if(ret)
        //printf("libdfmt_dev_open > %s\n",libusb_error_name(ret));
    return lusb_error_tr(ret);
}

void libdfmt_dev_close(Libdfmt_device *dev)
{
    if(dev->lusb_handle)
    {
        libusb_release_interface(dev->lusb_handle, TUNNEL_INTERFACE_ID);
        libusb_close(dev->lusb_handle);
        dev->lusb_handle = NULL;
    }
}

unsigned int libdfmt_get_dev_address(Libdfmt_device *dev)
{
    const unsigned int bus  = libusb_get_bus_number(dev->lusb_dev);
    const unsigned int addr = libusb_get_device_address(dev->lusb_dev);

    return addr | (bus<<8);
}

void libdfmt_get_tuners(Libdfmt_device *dev,
                        Libdfmt_tuner **tunA, Libdfmt_tuner **tunB)
{
    *tunA = &dev->tunerA;
    *tunB = &dev->tunerB;
}


