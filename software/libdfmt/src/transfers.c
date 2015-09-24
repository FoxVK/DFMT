#include "devices.h"
#include "shared.h"
#include <stdlib.h>
#include "stdio.h"

typedef struct
{
    char id;
    union {
        struct {
            char error;
            Tuner_read_reply reply;
        }in; //reply
        struct {
            char tuner;
            char type;
            char rw_size;
            uint8_t cmd[16];
        }out;//request
    };
}Tunnel_msg_test;

const size_t overhead_send    = 4;
const size_t overhead_receive = 2;

static void flush_dev(Libdfmt_device *dev)
{
    char buf[10];
    while( !dev_usb_receive(dev, buf, sizeof(buf), 2) );
}

static int parse_tuner_err(int tuner_err)
{
    switch(tuner_err)
    {
    case TUNNEL_ERROR_OK:
        return LIBDFMT_OK;

    case TUNNEL_ERROR_TUNERNOTUP:
    case TUNNEL_ERROR_I2CBUSY:
    case TUNNEL_ERROR_REQINPORGRESS:
        return LIBDFMT_ERROR_DEV_BUSY;

    case TUNNEL_ERROR_I2C:
    case TUNNEL_ERROR_BADTYPE:
    default:
        return LIBDFMT_ERROR_INTERNAL;
    }
}

static char transaction = 1;

int transfers_cmd(Libdfmt_device *dev, int tuner,
                  unsigned char *cmd, size_t cmd_size)
{
    int i, err;
    Tunnel_msg msg, reply;
    msg.id = transaction;
    msg.out.tuner = tuner;
    msg.out.rw_size = cmd_size;
    msg.out.type = TUNNEL_REQ_WRITE;

    //flush_dev(dev);

    for (i=0; i<cmd_size; i++)
        msg.out.cmd[i] = cmd[i];

    err = dev_usb_send(dev, &msg, cmd_size + overhead_send, 10);
    if(err >= 0)
    {
        for(i=0; i<5; i++)
        {
            err = dev_usb_receive(dev, &reply, sizeof(reply), 30);

            if(reply.in.error == TUNNEL_ERROR_OK && reply.id == transaction)
            {
                break;
            }
        }

        if(err > 1)
            err = parse_tuner_err(reply.in.error);
        else if(err >= 0)
            err = LIBDFMT_ERROR_INTERNAL;
    }
    else
        printf("dev_usb_send = %d", err);

    transaction++;
    return err;
}

int transfers_status_check(Libdfmt_device *dev, int tuner)
{
    int i, err;

    Tunnel_msg msg;
    msg.id = transaction;
    msg.out.tuner = tuner;
    msg.out.type = TUNNEL_REQ_READ;
    msg.out.rw_size = 1;
    err = dev_usb_send(dev, &msg, 4, 10);

    for(i=0; i<5; i++)
    {
        err = dev_usb_receive(dev, &msg, 3, 300);
        if(err >= 2)
            break;
    }
    if(err > 3)
        return ((Tuner_read_reply)msg.in.reply).STATUS.byte;
    else
        return err;
}

int transfers_int_check(Libdfmt_device *dev, int tuner)
{
    flush_dev(dev);
    return 0;
}

int transfers_prop_set(Libdfmt_device *dev, int tuner,
                       unsigned int prop, unsigned int value)
{
    //TODO endianity !!
    flush_dev(dev);
    return 0;
}

int transfers_prop_get(Libdfmt_device *dev, int tuner,
                       unsigned int prop, unsigned int *value)
{   //TODO endianity !!
    return 0;
}
