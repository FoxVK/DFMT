#ifndef LIBDFMT_H
#define COM_H

typedef struct Libdfmt_device Libdfmt_device;

typedef enum Libdfmt_tuner Libdfmt_tuner; //TODO This is probably not so clever

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
