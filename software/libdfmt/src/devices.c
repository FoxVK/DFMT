#include <stdlib.h>
#include "devices.h"
#include "../../../firmware/shared.h"

static Libdfmt_device *devices_connected, *devices_disconnected;
static Libdfmt_dev_callback cb_new, cb_removed;

void dev_init()
{
    devices_connected = devices_disconnected = NULL;

    cb_new = cb_removed = NULL;
}

static void add_dev(libusb_device *lusb_dev)
{
    Libdfmt_device *d, *d_prev;

    const int bus  = libusb_get_bus_number(lusb_dev);
    const int addr = libusb_get_device_address(lusb_dev);

    d = devices_connected;

    while(d)
    {
        if( (bus  == libusb_get_bus_number(d->lusb_dev)) &&
            (addr == libusb_get_device_address(d->lusb_dev)) )
        {
            return;
        }
        d = d->next;
    }
    //not in connected list

    d_prev = NULL;
    d = devices_disconnected;

    while(d)
    {
        if( (bus  == libusb_get_bus_number(d->lusb_dev)) &&
            (addr == libusb_get_device_address(d->lusb_dev)) )
        {
            //take from list of disconnected devs
            if(!d_prev)
            {
                devices_disconnected = d->next;
            }
            else
            {
                d_prev->next = d->next;
            }

            break;
        }
        d_prev = d;
        d = d->next;
    }

    if(!d)
        d = malloc(sizeof(Libdfmt_device));

    d->next = devices_connected;
    d->lusb_dev = lusb_dev;
    d->lusb_handle = NULL;
    devices_connected = d;

    if(cb_new)
        cb_new(d);
}

static void mark_all_not_present()
{
    Libdfmt_device *d = devices_connected;
    while(d)
    {
        d->present = 0;
        d = d->next;
    }
}

static void mark_presence(libusb_device *lusb_dev)
{
    const int bus  = libusb_get_bus_number(lusb_dev);
    const int addr = libusb_get_device_address(lusb_dev);

    Libdfmt_device *d = devices_connected;

    while(d)
    {
        if( (bus  == libusb_get_bus_number(d->lusb_dev)) &&
           (addr == libusb_get_device_address(d->lusb_dev)) )
        {
            d->present =  1;
            break;
        }

        d = d->next;
    }
}

static void remove_not_present()
{
    Libdfmt_device *d_prev = NULL;
    Libdfmt_device *d = devices_connected;

    while(d)
    {
        Libdfmt_device *next = d->next;

        if(!d->present)
        {
            if(!d_prev)
                devices_connected->next = d->next;
            else
                d_prev->next = d->next;

            d->next = devices_disconnected;
            devices_disconnected = d;

            if(cb_removed)
                cb_removed(d);
        }
        else
            d_prev = d;

        d = next;
    }
}

void dev_exit()
{
    while(devices_disconnected)
    {
        Libdfmt_device *next = devices_disconnected->next;
        if(devices_disconnected->lusb_handle)
            libdfmt_dev_close(devices_disconnected);
        free(devices_disconnected);
        devices_disconnected = next;
    }

    while(devices_connected)
    {
        Libdfmt_device *next = devices_connected->next;
        if(devices_connected->lusb_handle)
            libdfmt_dev_close(devices_connected);
        free(devices_connected);
        devices_connected = next;
    }
}

static int parse_lusb_err(int err)
{
    //TODO if dev is not available - remove from list
    return err;
}

void libdfmt_scan_devs()
{
    const u_int16_t vid=libusb_cpu_to_le16(USB_VID);
    const u_int16_t pid=libusb_cpu_to_le16(USB_PID);

    libusb_device **lusb_list;
    ssize_t cnt = libusb_get_device_list(NULL, &lusb_list);
    ssize_t i = 0;

    if (cnt < 0)
        return ;

    mark_all_not_present();

    for (i = 0; i < cnt; i++)
    {
        struct libusb_device_descriptor desc;

        libusb_device *lusb_dev = lusb_list[i];
        libusb_get_device_descriptor(lusb_dev, &desc);

        if (desc.idVendor == vid && desc.idProduct == pid)
        {
            add_dev(lusb_dev);
            mark_presence(lusb_dev);
        }
    }
    remove_not_present();

}

Libdfmt_device* libdfmt_get_all_devs()
{
    return devices_connected;
}

Libdfmt_device* libdfmt_next(Libdfmt_device* current_dev)
{
    if(current_dev)
        return current_dev->next;
    else
        return NULL;
}

int libdfmt_dev_open(Libdfmt_device *dev)
{
    int ret = libusb_open(dev->lusb_dev, &dev->lusb_handle);
    if(!ret)
        ret = libusb_claim_interface(dev->lusb_handle, TUNNEL_EP_IN);
    if(!ret)
        ret = libusb_claim_interface(dev->lusb_handle, TUNNEL_EP_OUT);

    return parse_lusb_err(ret);
}

void libdfmt_dev_close(Libdfmt_device *dev)
{
    libusb_release_interface(dev->lusb_handle, TUNNEL_EP_OUT);
    libusb_release_interface(dev->lusb_handle, TUNNEL_EP_IN);
    libusb_close(dev->lusb_handle);
    dev->lusb_handle = NULL;
}

int dev_usb_send(Libdfmt_device *dev, void *buf, size_t buf_size, unsigned int timeout)
{
    int transferred;
    int ret = libusb_bulk_transfer( dev->lusb_handle,
                                    TUNNEL_EP_OUT,
                                    (unsigned char*)buf,
                                    (int)buf_size,
                                    &transferred,
                                    timeout
                                  );
    if(ret)
        return parse_lusb_err(ret);

    return transferred;
}

int dev_usb_receive(Libdfmt_device *dev, void *buf, size_t buf_size, unsigned int timeout)
{
    int transferred;
    int ret = libusb_bulk_transfer( dev->lusb_handle,
                                    TUNNEL_EP_IN,
                                    (unsigned char*)buf,
                                    (int)buf_size,
                                    &transferred,
                                    timeout
                                  );
    if(ret)
        return parse_lusb_err(ret);

    return transferred;
}

void libdfmt_new_dev_cb    (Libdfmt_dev_callback callback)
{
    cb_new = callback;
}

void libdfmt_removed_dev_cb(Libdfmt_dev_callback callback)
{
    cb_removed = callback;
}

unsigned int libdfmt_get_dev_address(Libdfmt_device *dev)
{
    const unsigned int bus  = libusb_get_bus_number(dev->lusb_dev);
    const unsigned int addr = libusb_get_device_address(dev->lusb_dev);

    return addr | (bus<<8);
}
