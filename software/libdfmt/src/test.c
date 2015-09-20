#include <stdio.h>
#include "../libdfmt.h"

void cb(Libdfmt_device *dev)
{
    printf(" Callback: Found tuner 0x%04x\n", libdfmt_get_dev_address(dev));
}

int main(void)
{
    printf("jedu\n");
    libdfmt_init(2);

    printf("CB reg\n");
    libdfmt_new_dev_cb(cb);

    printf("scan\n");
    libdfmt_scan_devs();
    Libdfmt_device *devs = libdfmt_get_all_devs();

    while(devs)
    {
        printf("Found tuner 0x%04x\n", libdfmt_get_dev_address(devs));

        printf("Opening\n");
        libdfmt_dev_open(devs);

        printf("Closing\n");
        libdfmt_dev_close(devs);

        devs = libdfmt_next(devs);
    }

    libdfmt_exit();

    printf("hotovo\n");
    return 0;

}
