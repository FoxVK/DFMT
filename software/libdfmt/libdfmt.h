#ifndef LIBDFMT_H
#define COM_H

typedef struct {
    int is_open;
}Libdfmt_tuner;

#ifdef __cplusplus
extern "C" {
#endif

int libdfmt_open(Libdfmt_tuner * tuner);
void libdfmt_close(Libdfmt_tuner * tuner);
void libdfmt_seek(Libdfmt_tuner * tuner, int up);
void libdfmt_tune(Libdfmt_tuner * tuner, unsigned freq);

#ifdef __cplusplus
}
#endif

#endif
