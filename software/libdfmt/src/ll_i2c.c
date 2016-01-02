#include <libusb.h>
#include <stdio.h>

#include "libdfmt_device.h"
#include "libdfmt_tuner.h"
#include "libdfmt.h"
#include "shared.h"
#include "lusb_error_tr.h"

static char transaction = 0;

static Libdfmt_error usb_com(Libdfmt_device *dev, void *buf, size_t *size,
                             int send,unsigned int timeout)
{
    int transferred;
    enum libusb_error ret;

    if(!dev || !dev->lusb_handle) return LIBDFMT_DEVICE_CLOSED;

    ret = libusb_bulk_transfer( dev->lusb_handle,
                                send ? TUNNEL_EP_OUT : TUNNEL_EP_IN,
                                (unsigned char*)buf,
                                (int)*size,
                                &transferred,
                                timeout
                               );

    if(ret)
        return lusb_error_tr(ret);

    *size = transferred;
    return LIBDFMT_OK;
}


const size_t hdr_out = 4;
const size_t hdr_in  = 2;

static Libdfmt_error tunnel_error_tr(Tunnel_error err)
{
    switch (err)
    {
    case TUNNEL_ERROR_I2C:
        return LIBDFMT_ERROR_DEVICE_INTERNAL;

    case TUNNEL_ERROR_I2CBUSY:
    case TUNNEL_ERROR_REQINPORGRESS:
    case TUNNEL_ERROR_TUNERNOTUP:
        return LIBDFMT_ERROR_TUNER_BUSY;

    case TUNNEL_ERROR_OK:
        return LIBDFMT_OK;

    default:
         return TUNNEL_ERROR;
    }
}

Libdfmt_error  libdfmt_i2c_com(Libdfmt_tuner *tuner, char *buf, size_t *size,
                              int read, unsigned int timeout)
{
    Tunnel_msg msg;
    Libdfmt_error err;
    int i;
    size_t sz = *size;

    if(!buf || *size < 1)
        return LIBDFMT_ERROR_BAD_ARGUMENT;

    if(!tuner || !tuner->dev)
        return LIBDFMT_DEVICE_CLOSED;

    //send req
    transaction ++;
    transaction &= 0xff;

    msg.id = transaction;
    msg.out.type = read ? TUNNEL_REQ_READ : TUNNEL_REQ_WRITE;
    msg.out.tuner = tuner->tuner;
    msg.out.rw_size = sz;
    if(!read)
    {
        for (i=0; i<sz; i++)
            msg.out.cmd[i] = buf[i];
    }

    sz += hdr_out;
    err = usb_com(tuner->dev, &msg, &sz, 1, 10);

    if(err)
        return err;


    //get response
    for(i=0;i<5;i++)
    {
        sz = sizeof(msg);
        err = usb_com(tuner->dev, &msg, &sz, 0, timeout);

        if(err)
            return err;

        if(sz<hdr_in)
            continue;

        err = tunnel_error_tr(msg.in.error);
        if(err)
            return err;

        if(msg.id == transaction)
        {
            if(read)
            {
                sz = (sz>*size) ? *size : sz;
                for (i=0; i<sz ; i++)
                    buf[i] = ((char*)&msg.in.reply)[i];
                *size = sz;
            }
            return LIBDFMT_OK;
        }
    }
    return LIBDFMT_ERROR_TIMEOUT;
}

Libdfmt_error  libdfmt_i2c_send(Libdfmt_tuner *tuner, char *buf, size_t size)
{
    return  libdfmt_i2c_com(tuner, buf, &size, 0, 10);
}

Libdfmt_error  libdfmt_i2c_recv(Libdfmt_tuner *tuner, char *buf, size_t *size,
                       unsigned int timeout)
{
    return  libdfmt_i2c_com(tuner, buf, size, 1, timeout);
}
