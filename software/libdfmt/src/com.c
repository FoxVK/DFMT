#include <stdlib.h>
#include "libusb.h"
#include "com.h"

#define USB_VID 0x00a6
#define USB_PID 0xff01

#define TUNNEL_INTERFACE_ID 2

#define TUNNEL_EP 0x02
#define TUNNEL_EP_OUT TUNNEL_EP
#define TUNNEL_EP_IN (TUNNEL_EP | (1<<7))

static libusb_device **list;

static Libdfmt_device* new_device()
{
    Libdfmt_device* dev = malloc(sizeof(Libdfmt_device));
    if(dev)
    {
        dev->open = 0;
        dev->next = NULL;
        dev->lusb_dev = NULL;
        dev->lusb_handle = NULL;
    }
    return dev;
}

void com_init(int libusb_debug)
{
    libusb_init(NULL);
    libusb_set_debug(NULL, libusb_debug);
}

void com_exit()
{
    libusb_exit(NULL);
}

int com_get_tuners(Libdfmt_device **devices)
{
    // discover devices

    Libdfmt_device *devs = NULL, *last_dev = NULL;
    int dev_count = 0;
    ssize_t cnt = libusb_get_device_list(NULL, &list);
    ssize_t i = 0;

    if (cnt < 0)
        return -1;

    u_int16_t vid=libusb_cpu_to_le16(USB_VID), pid=libusb_cpu_to_le16(USB_PID);

    for (i = 0; i < cnt; i++)
    {
        struct libusb_device_descriptor desc;

        libusb_device *device = list[i];
        libusb_get_device_descriptor(device, &desc);

        if (desc.idVendor == vid && desc.idProduct == pid)
        {
            Libdfmt_device *d = new_device();
            if(d)
            {
                if(!devs)
                    devs = d;

                if(last_dev)
                    devs->next = d;

                d->lusb_dev = device;

                last_dev = d;
                dev_count++;
            }
            break;
        }
    }
    *devices = devs;
    return dev_count;
}

void com_free_unopened_tuners(Libdfmt_device **devices)
{
    Libdfmt_device *next = *devices;
    while(next)
    {
        Libdfmt_device *current = next;
        next = current->next;
        if(!current->open)
            free((void*)current);
    }

    libusb_free_device_list(list, 1);
}

void com_open(Libdfmt_device *dev)
{
    if(!dev)
        return;

    if(!libusb_open(dev->lusb_dev, &dev->lusb_handle))
       dev->open = 1;

    libusb_claim_interface(dev->lusb_handle, TUNNEL_INTERFACE_ID);
}

void com_close(Libdfmt_device *dev)
{
    //TODO nastavit dev na NULL ??
    libusb_release_interface(dev->lusb_handle, TUNNEL_INTERFACE_ID);
    libusb_close(dev->lusb_handle);
    free((void*)dev);
}

int com_read (int tuner, void *data, size_t size, int timeout)
{
    //TODO http://libusb.org/static/api-1.0/group__syncio.html#gab8ae853ab492c22d707241dc26c8a805
    return 0;
}

int com_write(int tuner, void *data, size_t size, int timeout)
{
    //TODO http://libusb.org/static/api-1.0/group__syncio.html#gab8ae853ab492c22d707241dc26c8a805
    return 0;
}
