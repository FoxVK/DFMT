#include "../libdfmt.h"

#include <stdlib.h>
#include "devices.h"
#include "transfers.h"






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

int libdfmt_seek(Libdfmt_device * device, int up)
{
    //TODO:
    (void) device;
    (void) up;

    return 0;
}

int libdfmt_tune(Libdfmt_device * dev,int tuner, unsigned freq)
{
    //freq must be multiply of 50:

    //0x20 FM_TUNE_FREQ
     unsigned char cmd[]={0x20, 0, freq>>8, freq};
     int err = transfers_cmd(dev, tuner, cmd, sizeof(cmd));
     //if (err<0)
     //    return err;

     transfers_status_check(dev, tuner);
     return err;
}



Libdfmt_device* libdfmt_get_next(Libdfmt_device* current_dev)
{
    if(!current_dev)
        return NULL;
    return current_dev->next;
}
