#include <stdio.h>
#include "libdfmt.h"

void cb(Libdfmt_device *dev)
{
    printf(" Callback: Found tuner 0x%04x\n", libdfmt_get_dev_address(dev));
}


int main(void)
{
    printf("Test started\n");
    libdfmt_init(2);

    printf("CB reg\n");
    libdfmt_new_dev_cb(cb);

    printf("scan\n");
    libdfmt_scan_devs();
    Libdfmt_device *devs = libdfmt_get_all_devs();

    while(devs)
    {
        //printf("Found tuner 0x%04x\n", libdfmt_get_dev_address(devs));

        Libdfmt_tuner *t_a, *t_b;
        libdfmt_get_tuners(devs, &t_a, &t_b);

        printf("Opening %d \n", libdfmt_dev_open(devs));

        printf("tunning A\n");
        printf(" err=%d\n", libdfmt_tune(t_a, 97.3));

        //printf("tunning B\n");
        //printf(" err=%d\n", libdfmt_tune(devs, 1, 9730));

        printf("Closing\n");
        libdfmt_dev_close(devs);

        devs = libdfmt_next(devs);
    }

    libdfmt_exit();

    printf("Test done\n");
    return 0;

}
