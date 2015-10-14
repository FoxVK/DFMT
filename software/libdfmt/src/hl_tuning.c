#include "libdfmt.h"
#include "libdfmt_commands.h"

/*
 *Test
*/
Libdfmt_error libdfmt_tune(Libdfmt_tuner *tuner, float freq)
{
    unsigned int ifreq = freq*100;
    char arg[] = {
        0,
        (ifreq >> 8) & 0xff,
        ifreq & 0xff
    };
    if (76 > freq || freq > 108)
        return LIBDFMT_ERROR_BAD_ARGUMENT;

    return libdfmt_cmd_send(tuner, LIBDFMT_CMD_FM_TUNE_FREQ, arg, sizeof(arg));
}
