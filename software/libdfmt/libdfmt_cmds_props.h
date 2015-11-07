/** @file libdfmt_commands.h
 * @brief Definitions of some tuner commands and properties.
 * @copyright
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * @copyright
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * @copyright
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 * @copyright
 * Copyright: Pavel Kovar 2015 <pavel.kovar@vsetin.org>.
 */

#ifndef LIBDFMT_COMMANDS_H
#define LIBDFMT_COMMANDS_H

/**
  * @file libdfmt_commands.h
  * @brief Commands and Properties constatnts for tuner.
  */

#ifdef __cplusplus
extern "C" {
#endif

/**
  * @brief Tuner commands.
  *
  * Only FM commands are present.
  * @see AN332 Si47xx Programming Guide by Silicon Labs.
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

/** @brief Tuner porperties. (Only few).
  * @see AN332 Si47xx Programming Guide by Silicon Labs.
  */
typedef enum{
    LIBDFMT_PROP_FM_RDS_INT_FIFO_COUNT = 0x1501,
    LIBDFMT_PROP_FM_RDS_CONFIG = 0x1502,
}Libdfmt_property;

#ifdef __cplusplus
}
#endif

#endif // LIBDFMT_COMMANDS_H
