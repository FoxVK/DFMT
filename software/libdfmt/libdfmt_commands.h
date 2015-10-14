#ifndef LIBDFMT_COMMANDS_H
#define LIBDFMT_COMMANDS_H

/**
  * @file libdfmt_commands.h
  * @brief Commands and Properties constatnts for tuner
  * @todo Properties
  */

#ifdef __cplusplus
extern "C" {
#endif

/**
  * @brief Commands for tuner.
  */
typedef enum{
    LIBDFMT_CMD_POWER_UP = 0x01,
    LIBDFMT_CMD_GET_REV = 0x10,
    LIBDFMT_CMD_POWER_DOWN = 0x11,
    LIBDFMT_CMD_SET_PROPERTY = 0x12,
    LIBDFMT_CMD_GET_PROPERTY = 0x13,
    LIBDFMT_CMD_GET_INT_STATUS = 0x14,
    LIBDFMT_CMD_PATCH_ARGS = 0x15,
    LIBDFMT_CMD_PATCH_DATA = 0x16,
    LIBDFMT_CMD_FM_TUNE_FREQ = 0x20,
    LIBDFMT_CMD_FM_SEEK_START = 0x21,
    LIBDFMT_CMD_FM_TUNE_STATUS = 0x22,
    LIBDFMT_CMD_FM_RSQ_STATUS = 0x23,
    LIBDFMT_CMD_FM_RDS_STATUS = 0x24,
    LIBDFMT_CMD_FM_AGC_STATUS = 0x27,
    LIBDFMT_CMD_FM_AGC_OVERRIDE = 0x28,
    LIBDFMT_CMD_GPIO_CTL = 0x80,
    LIBDFMT_CMD_GPIO_SET = 0x81,
}Libdfmt_cmd;

#ifdef __cplusplus
}
#endif

#endif // LIBDFMT_COMMANDS_H
