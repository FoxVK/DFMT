#include <libusb.h>

#include "libdfmt.h"
#include "devices.h"







// ------------------- PUBLIC FUNCTIOS -----------------------
void libdfmt_init(int libusb_debug)
{

    libusb_init(NULL);
    libusb_set_debug(NULL, libusb_debug);
    devs_init();
}

void libdfmt_exit()
{
    devs_exit();
    libusb_exit(NULL);
}

#if 0
int libdfmt_seek(Libdfmt_device * device, int up)
{
    //TODO:
    (void) device;
    (void) up;

    return 0;
}
#endif
