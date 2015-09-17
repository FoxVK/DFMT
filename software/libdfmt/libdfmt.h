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

int libdfmt_open(Libdfmt_device * device);
void libdfmt_close(Libdfmt_device * device);
void libdfmt_seek(Libdfmt_device * device, int up);
void libdfmt_tune(Libdfmt_device * tuner, unsigned freq);

#ifdef __cplusplus
}
#endif

#endif
