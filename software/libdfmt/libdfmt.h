#ifndef LIBDFMT_H
#define LIBDFMT_H

typedef struct Libdfmt_device Libdfmt_device;

typedef enum {
    TUNER_A=0, TUNER_B=1
}Libdfmt_tuner;

#ifdef __cplusplus
extern "C" {
#endif

void libdfmt_init(int libusb_debug);
void libdfmt_exit();

void libdfmt_seek(Libdfmt_device * device, int up);
void libdfmt_tune(Libdfmt_device * device, unsigned freq);



typedef void(*Libdfmt_dev_callback)(Libdfmt_device*);

void libdfmt_scan_devs();
Libdfmt_device* libdfmt_get_all_devs();
Libdfmt_device* libdfmt_next(Libdfmt_device* current_dev);

int  libdfmt_dev_open(Libdfmt_device *dev);
void libdfmt_dev_close(Libdfmt_device *dev);

void libdfmt_new_dev_cb    (Libdfmt_dev_callback callback);
void libdfmt_removed_dev_cb(Libdfmt_dev_callback callback);

unsigned int libdfmt_get_dev_address(Libdfmt_device *dev);


#ifdef __cplusplus
}
#endif

#endif
