#include "../libdfmt.h"

#include <stdlib.h>
#include "devices.h"
#include "libusb.h"

#include "../../../firmware/shared.h"


int usb_send(Libdfmt_device *dev, void *data, size_t size, int timeout)
{
    int transferred;

    int err = libusb_bulk_transfer(
            dev->lusb_handle,
            TUNNEL_EP_OUT,
            (unsigned char*)data,
            (int) size,
            &transferred,
            (unsigned int)timeout
        );

    return err;
}

int usb_receive(Libdfmt_device *dev, void *data, size_t size, int timeout)
{
    int transferred;
    int err = libusb_bulk_transfer(
            dev->lusb_handle,
            TUNNEL_EP_IN,
            (unsigned char*)data,
            (int) size,
            &transferred,
            (unsigned int)timeout
        );

    return err;
}

int com_read (Libdfmt_device *dev, int tuner, void *data, size_t size, int timeout)
{
    //http://libusb.org/static/api-1.0/group__syncio.html#gab8ae853ab492c22d707241dc26c8a805
    int transferred;

    int err = libusb_bulk_transfer(
            dev->lusb_handle,
            TUNNEL_EP_IN,
            (unsigned char*)data,
            (int) size,
            &transferred,
            (unsigned int)timeout
        );

    if(!err)
    {
        Tunnel_msg reply;
        err = com_read(dev, tuner, &reply, sizeof(reply), 10);
        if(!err && reply.in.error)
            err = 1000 + reply.in.error;
    }
    return err;
}

int com_write(Libdfmt_device *dev, int tuner, void *data, size_t size, int timeout)
{
    //http://libusb.org/static/api-1.0/group__syncio.html#gab8ae853ab492c22d707241dc26c8a805
    int transferred;

    int err = libusb_bulk_transfer(
            dev->lusb_handle,
            TUNNEL_EP_OUT,
            (unsigned char*)data,
            (int) size,
            &transferred,
            (unsigned int)timeout
        );

    if(!err && ((Tunnel_msg*)data)->in.error)
        err = ((Tunnel_msg*)data)->in.error + 1000;

    return err;
}



// ------------------- PUBLIC FUNCTIOS -----------------------
void libdfmt_init(int libusb_debug)
{

    libusb_init(NULL);
    libusb_set_debug(NULL, libusb_debug);
    dev_init();
}

void libdfmt_exit()
{
    dev_exit();
    libusb_exit(NULL);
}

void libdfmt_seek(Libdfmt_device * device, int up)
{
    //TODO:
    (void) device;
    (void) up;
}

void libdfmt_tune(Libdfmt_device * device, unsigned freq)
{
    //TODO:
    (void) device;
    (void) freq;
}



Libdfmt_device* libdfmt_get_next(Libdfmt_device* current_dev)
{
    if(!current_dev)
        return NULL;
    return current_dev->next;
}


void libdfmt_open(Libdfmt_device *dev)
{
    if(!dev)
        return;

    libusb_open(dev->lusb_dev, &dev->lusb_handle);


    libusb_claim_interface(dev->lusb_handle, TUNNEL_INTERFACE_ID);
}

void libdfmt_close(Libdfmt_device *dev)
{
    //TODO nastavit dev na NULL ??
    libusb_release_interface(dev->lusb_handle, TUNNEL_INTERFACE_ID);
    libusb_close(dev->lusb_handle);
    free((void*)dev);
}
