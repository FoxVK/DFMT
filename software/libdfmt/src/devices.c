#include <stdlib.h>
#include <libusb.h>

#include "libdfmt.h"
#include "shared.h"
#include "libdfmt_device.h"

#include "stdio.h"

static Libdfmt_device *devices_connected, *devices_disconnected;
static Libdfmt_dev_callback cb_new, cb_removed;

void devs_init()
{
    devices_connected = devices_disconnected = NULL;

    cb_new = cb_removed = NULL;
}

void devs_exit()
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

static void fill_dev(libusb_device *lusb_dev, Libdfmt_device *dev, Libdfmt_device *next)
{
    dev->lusb_dev = lusb_dev;
    dev->lusb_handle = NULL;
    dev->next = next;
    dev->present = 1;

    dev->tunerA.dev = dev->tunerB.dev = dev;
    dev->tunerA.is_busy = dev->tunerB.is_busy = 1;
    dev->tunerA.tuner = 0;
    dev->tunerB.tuner = 1;
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

    fill_dev(lusb_dev, d, devices_connected);
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

        if(!d->present) //remove d from linked list
        {
            if(!d_prev) //d is first
                devices_connected = d->next;
            else        //d is not first
                d_prev->next = d->next;

            //put to the front of disconnected list
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





void libdfmt_scan_devs()
{
    const unsigned vid=libusb_cpu_to_le16(USB_VID);
    const unsigned pid=libusb_cpu_to_le16(USB_PID);

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





void libdfmt_new_dev_cb    (Libdfmt_dev_callback callback)
{
    cb_new = callback;
}

void libdfmt_removed_dev_cb(Libdfmt_dev_callback callback)
{
    cb_removed = callback;
}
