#include "libdfmt.h"
#include "shared.h"
#include "libdfmt_tuner.h"
#include "libdfmt_cmds_props.h"

Libdfmt_error libdfmt_cmd_status(Libdfmt_tuner *tuner, char *status_byte)
{
    Libdfmt_error err;
    size_t s = 1;

    if(!tuner || !status_byte)
        return LIBDFMT_ERROR_BAD_ARGUMENT;

    err = libdfmt_i2c_recv(tuner, status_byte, &s, 20);

    if(!err)
        tuner->is_busy = (*status_byte & LIBDFMT_TUNER_STAT_CTS) ? 0 : 1;

    return err;
}

Libdfmt_error libdfmt_check_bussy(Libdfmt_tuner *tuner)
{
    char status = 0;
    Libdfmt_error err;

    if(!tuner)
        return LIBDFMT_ERROR_BAD_ARGUMENT;

    if(!tuner->is_busy)
        return LIBDFMT_OK;

    err = libdfmt_cmd_status(tuner, &status);
    if((status & LIBDFMT_TUNER_STAT_CTS) && !err)
        return LIBDFMT_OK;
    else
        return err;

}

Libdfmt_error libdfmt_cmd_send_nocheck(Libdfmt_tuner *tuner, char cmd,
                                       char *arg, size_t size)
{
    unsigned i;
    Libdfmt_error err;
    char cmd_buf[size+1];


    cmd_buf[0]=cmd;

    for(i=0; i<size; i++)
        cmd_buf[i+1] = arg[i];

    err = libdfmt_i2c_send(tuner, cmd_buf, size+1);
    tuner->is_busy = 1;

    return err;
}

Libdfmt_error libdfmt_cmd_send(Libdfmt_tuner *tuner, char cmd,
                               char *arg, size_t size)
{
    char status;
    Libdfmt_error err;

    err =  libdfmt_check_bussy(tuner);
    if(err)
        return err;


    err = libdfmt_cmd_send_nocheck(tuner, cmd, arg, size);
    if(err)
        return err;


    err =  libdfmt_cmd_status(tuner, &status);
    if(err)
        return err;
    if(status & LIBDFMT_TUNER_STAT_ERR)
        return LIBDFMT_ERROR_TUNER_ERROR;

    return err;
}

Libdfmt_error libdfmt_cmd_recv_reply(Libdfmt_tuner *tuner,
                                     char *buf, size_t size)
{
    Libdfmt_error err = libdfmt_i2c_recv(tuner, buf, &size, 100);

    if(!err)
        tuner->is_busy = (buf[0] & LIBDFMT_TUNER_STAT_CTS) ? 0 : 1;

    return err;
}


Libdfmt_error libdfmt_check_int(Libdfmt_tuner *tuner, char *status_byte)
{
    Libdfmt_error err;

    //err = cmd_
    size_t received = 1;

    err =  libdfmt_cmd_status(tuner, status_byte);
    if(err)
        return err;
    if( !(*status_byte & LIBDFMT_TUNER_STAT_CTS))
        return LIBDFMT_ERROR_TUNER_BUSY;

    return libdfmt_i2c_recv(tuner, status_byte, &received, 20);
}
