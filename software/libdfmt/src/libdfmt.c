#include "../libdfmt.h"
#include "com.h"

void libdfmt_init(int libusb_debug)
{
    com_init(libusb_debug);
    com_test();
}

void libdfmt_exit()
{
    com_exit();
}

int libdfmt_open(Libdfmt_device * tuner)
{
    //TODO:
    (void) tuner;
    return 0;
}

void libdfmt_close(Libdfmt_device * tuner)
{
    //TODO:
    (void) tuner;
}

void libdfmt_seek(Libdfmt_device * tuner, int up)
{
    //TODO:
    (void) tuner;
    (void) up;
}

void libdfmt_tune(Libdfmt_device * tuner, unsigned freq)
{
    //TODO:
    (void) tuner;
    (void) freq;
}
