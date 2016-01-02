#ifndef LIBDFMT_H
#define LIBDFMT_H

#include <stdlib.h>
#include <stdint.h>

/** @file libdfmt.h
 * @brief libdfmt public header file.
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

#ifdef __cplusplus
extern "C" {
#endif

/** @brief Physical device with two tuners on it.*/
typedef struct Libdfmt_device Libdfmt_device;

/** @brief Tuner on device.*/
typedef struct Libdfmt_tuner Libdfmt_tuner;

/** @brief Error codes returned by most of functions.
 * @todo check it
*/
typedef enum {
    LIBDFMT_OK                        =0, ///< No error
    LIBDFMT_ERROR_TIMEOUT             =1, ///< Timeour
    LIBDFMT_ERROR_TUNER_BUSY          =2, ///< CTS bit != 1 or tuner is alraday performing I2C communication.
    LIBDFMT_ERROR_TUNER_ERROR         =3, ///< ERR bit = 1
    LIBDFMT_ERROR_DEVICE_ERROR        =4, ///< Device received not enough data to recognize what to do.
    LIBDFMT_ERROR_DEVICE_DISCONNECTED =5, ///< Device is not present.
    LIBDFMT_ERROR_DEVICE_INTERNAL     =6, ///< Hardware or firmware malfunction.
    LIBDFMT_ERROR_USB_ERROR           =7, ///< Libusb error, probably more than one instaces is running.
    LIBDFMT_ERROR_BAD_ARGUMENT        =8, ///< Argument of invalid value or out of range.
    LIBDFMT_ERROR_NO_PERMISSION       =9, ///< You have insufficient permissions to open device. (probably missing udev rules on linux)
    LIBDFMT_DEVICE_CLOSED             =10,///< Device is not opened or was closed.
    LIBDFMT_ERROR                     =255///< General error
}Libdfmt_error;


/** @brief Flags for determining tuner status. See @ref libdfmt_cmd_status(Libdfmt_tuner *tuner, char *status_byte) */
enum Libdfmt_tuner_stat_flags{
    LIBDFMT_TUNER_STAT_STCINT = 0x01,
    LIBDFMT_TUNER_STAT_RSQINT = 0x08,
    LIBDFMT_TUNER_STAT_ERR    = 0x40,
    LIBDFMT_TUNER_STAT_CTS    = 0x80
};


/** @defgroup dev Operations with devices
 *  @brief Library basic functions and manipulation with devices.
 *  @{
 */


/**
 * @brief Performs initialization of library.
 * @warning Should be called only once.
 * @param libusb_debug 0=No debug prints 3=maximal verbosity.
 * @see libdfmt_exit()
 */
void libdfmt_init(int libusb_debug);

/**
 * @brief Frees resources. Should be called on app exit.
 * @see libdfmt_init()
 */
void libdfmt_exit();


/**
 * @brief Type of callback functions.
 * @see libdfmt_removed_dev_cb()
 * @see libdfmt_new_dev_cb()
 */
typedef void(*Libdfmt_dev_callback)(Libdfmt_device*);

/**
 * @brief Performs scan for connected devices.
 * Causes call callbacks for new and removed devices and updates list of connected devs retuned by libdfmt_get_all_devs().
 * @see libdfmt_removed_dev_cb()
 * @see libdfmt_new_dev_cb()
 */
void libdfmt_scan_devs();

/**
 * @brief Returns connected devices
 *
 * To update list use libdfmt_scan_devs().
 * You can go through list usign libdfmt_next().
 * To reset list just call this function again. It does not perform any scan.
 * @return List of connected devices or NULL if no device is connected.
 */
Libdfmt_device* libdfmt_get_all_devs();

/**
 * @brief Walks through list of @ref Libdfmt_device.
 * @param current_dev Current device.
 * @see libdfmt_get_all_devs()
 * @return next @ref Libdfmt_device or NULL on end of list.
 */
Libdfmt_device* libdfmt_next(Libdfmt_device* current_dev);

/**
 * @brief Opens dev.
 * @param dev Device to open.
 * @return @ref LIBDFMT_OK on success, @ref LIBDFMT_ERROR_NO_PERMISSION if you have no permission to open device. Or other @ref Libdfmt_error.
 * @see libdfmt_dev_close()
 */
Libdfmt_error libdfmt_dev_open (Libdfmt_device *dev);

/**
 * @brief Closes device.
 * @param dev Device to close
 * @see libdfmt_dev_open()
 */
void          libdfmt_dev_close(Libdfmt_device *dev);

/**
 * @brief Registes a function which will be called when a device is connected.
 * Inforamtions about devices are updated only by function libdfmt_scan_devs().
 * @param callback A function to call or NULL.
 */
void libdfmt_new_dev_cb    (Libdfmt_dev_callback callback);

/**
 * @brief Registes a function which will be called when a device was disconnected.
 * Inforamtions about devices are updated only by function libdfmt_scan_devs().
 * @param callback A function to call or NULL.
 */
void libdfmt_removed_dev_cb(Libdfmt_dev_callback callback);

/**
 * @brief Returns address of device unique for all connected devices.
 * Lowest byte is device address on bus asigned during enumeration of device (see usb specification).
 * Second lowest byte is a number of bus to which device is connected.
 * Other bytes are always zero.
 * @param dev Device.
 * @warning Addres may vary on every reconnection even if same connector is used.
 * @return Device address.
 */
unsigned int libdfmt_get_dev_address(Libdfmt_device *dev);

/**
 * @brief set pointers to particular tunners of dev.
 * @param dev Device with tunners.
 * @param tunA Tuner A (The one used for capturing sound)
 * @param tunB Tuner B.
 */
void libdfmt_get_tuners(Libdfmt_device *dev,
                        Libdfmt_tuner **tunA, Libdfmt_tuner **tunB);

/** @} */ // end of dev group

// ll_i2c.c

/** @defgroup ll Low level tuner access
 *  @brief Low level access to I2C
 *  @{
 */

/**
 * @brief Perofrms I2C read or write to specifed tuner.
 * @param tuner Tuner to communicate with.
 * @param buf Data to write or bufer where data will be read to.
 * @param size Size of buf. In case of write will be updated to ammount of received data.
 * @param read If == 0 then write will be performed. Otherwise read.
 * @param timeout Timeot in ms
 * @return @ref LIBDFMT_OK on success or @ref Libdfmt_error.
 */
Libdfmt_error libdfmt_i2c_com(Libdfmt_tuner *tuner, char *buf, size_t *size,
                             int read, unsigned int timeout);
/**
 * @brief Perofrms I2C write to specifed tuner.
 * There is no timeout because function does not wait for device response. Use libusb_i2c_com() if zou need timeout.
 * @param tuner Tuner to write to.
 * @param buf Data for tuner.
 * @param size Size of buf.
 * @return @ref LIBDFMT_OK on success or @ref Libdfmt_error.
 */
Libdfmt_error libdfmt_i2c_send(Libdfmt_tuner *tuner, char *buf, size_t size);

/**
 * @brief Perofrms I2C read from specifed tuner.
 * @param tuner Tuner to communicate with.
 * @param buf Bufer where data will be read to.
 * @param size Size of buf. Will be updated to ammount of received data.
 * @param timeout Timeot in ms
 * @return @ref LIBDFMT_OK on success or @ref Libdfmt_error.
 */
Libdfmt_error libdfmt_i2c_recv(Libdfmt_tuner *tuner, char *buf, size_t *size,
                              unsigned int timeout);

//ll_ping.c

/** @} */ // end of ll group



/** @defgroup ml Middle level tuner access
 *  @brief Functions for sending commands, checking statuses and interrupts and manipulation with properties.
 *  @{
 */

//ml_command.c
/**
 * @brief Gets status byte of tuner.
 * Useful for determining is is safe to send next command.
 *
 * Unlike libdfmt_check_bussy() this function does not return @ref LIBDFMT_ERROR_TUNER_BUSY as result of status byte.
 * This error code will be returned only in case unfinished previvous I2C read or write.
 * @param tuner Selected tuner
 * @param status_byte Pointer to store status byte.
 * @return LIBDFMT_OK on success or other @ref Libdfmt_error.
 **/
Libdfmt_error libdfmt_cmd_status(Libdfmt_tuner *tuner, char *status_byte);

/**
 * @brief Checks if is safe to send comand to tuner.
 * @param tuner Selected tuner
 * @return LIBDFMT_ERROR_TUNER_BUSY if dev is busy, @ref LIBDFMT_OK if dev is not busy. Or other @ref Libdfmt_error.
 **/
Libdfmt_error libdfmt_check_bussy(Libdfmt_tuner *tuner);

/**
 * @brief Sends comand to tuner without checks CTS flag before and ERR flag after.
 * @param tuner Tuner.
 * @param cmd Comand byte.
 * @param arg Array with optional comand argumets.
 * @param size  Length of array with arg.
 * @return @ref LIBDFMT_OK on success or other @ref Libdfmt_error.
 * @see libdfmt_cmd_send()
 */
Libdfmt_error libdfmt_cmd_send_nocheck(Libdfmt_tuner *tuner, char cmd,
                                       char *arg, size_t size);

/**
 * @brief Sends comand to tuner. Checks CTS flag before and ERR flag after issuing command.
 * @param tuner Tuner.
 * @param cmd Comand byte.
 * @param arg Array with optional comand argumets.
 * @param size  Length of array with arg.
 * @return @ref LIBDFMT_OK on success or other @ref Libdfmt_error.
 */
Libdfmt_error libdfmt_cmd_send(Libdfmt_tuner *tuner, char cmd,
                               char *arg, size_t size);

/**
 * @brief Receives reply from tuner including status byte.
 * Size should equal to expected reply size.
 * @warning If CTS flag is not set or ERR flag is set only first byte is valid.
 * @param tuner Selected tuner.
 * @param buf Buffer to store reply.
 * @param size size of buffer
 * @return @ref LIBDFMT_OK on success or other @ref Libdfmt_error.
 */
Libdfmt_error libdfmt_cmd_recv_reply(Libdfmt_tuner *tuner,
                                     char *buf, size_t size);


/**
 * @brief Checks interrupt bits of selected tuner.
 * Unlike libdfmt_cmd_status() this function send command which updates interrupt flags in status byte.
 * @param tuner Selected tuner
 * @param status_byte pointer where status byte will be set.
 * @return LIBDFMT_ERROR_TUNER_BUSY if dev is busy, @ref LIBDFMT_OK if dev is not busy. Or other @ref Libdfmt_error.
 **/
Libdfmt_error libdfmt_check_int(Libdfmt_tuner *, char *status_byte);

//ml_property.c

/**
 * @brief libdfmt_prop_set Sets property.
 * @param tuner Tuner on which porperty wil be set.
 * @param prop Property
 * @param value Desired value of property.
 * @return @ref LIBDFMT_OK on success or other @ref Libdfmt_error.
 */
Libdfmt_error libdfmt_prop_set(Libdfmt_tuner *tuner,
                               unsigned prop, unsigned value);

/**
 * @brief libdfmt_prop_set Gets property.
 * @param tuner Selected tuner.
 * @param prop Property
 * @param value Pointer to memory where value of property will be stored.
 * @return @ref LIBDFMT_OK on success or other @ref Libdfmt_error.
 */
Libdfmt_error libdfmt_prop_get(Libdfmt_tuner *tuner,
                               unsigned prop, unsigned *value);

/** @} */ // end of ml group



/** @defgroup hl High level tuner access
 *  @brief Funcitons for tunning, retrieving metrics and RDS.
 *
 *  For better understanding to RDS see <a href=https://en.wikipedia.org/wiki/Radio_Data_System>wikipedia</a> or for more detailed description,
 *  folowing article <a href=http://www.2wcom.com/fileadmin/redaktion/dokumente/Company/RDS_Basics.pdf>2wcom - RDS Basics</a>.
 *  @{
 */

/**
 * @brief Search for valid frequency.
 *
 * Function check if tuner is bussy before tune cmd and error responce after issuing cmd.
 * Seek starts on current frequency and goes up (up=1) or down(up=0). Tuner automaticaly rollover end of frequency range and continues in selected direction. If whole band is scanned and no station was found tunner stops seeking.
 * Function does not wait until tunning is done.
 * @param tuner Selected tuner.
 * @param up Direction of seek.
 * @return @ref LIBDFMT_OK on success, @ref LIBDFMT_ERROR_BAD_ARGUMENT if frequency is not in range or other @ref Libdfmt_error .
 **/
Libdfmt_error libdfmt_seek(Libdfmt_tuner *tuner, int up);

/**
 * @brief Tune to frequency.
 * Function check if tuner is bussy before tune cmd and error response after issuing cmd.
 * Function does not wait until tunning is done.
 * @param tuner Selected tuner.
 * @param freq Frequency in MHz. Must be between 76.0 and 108.0.
 * @return @ref LIBDFMT_OK on success, @ref LIBDFMT_ERROR_BAD_ARGUMENT if frequency is not in range or other @ref Libdfmt_error .
 **/
Libdfmt_error libdfmt_tune(Libdfmt_tuner *tuner, double freq);

/**
 * @brief Libdfmt_tunning_done Call this function after libdfmt_tune() or libdfmt_seek() to get know if tunning was done.
 * If called multiple times, it resturns 1 only once.
 * @param tuner Selected tuner
 * @param done  Pointer to int where 1 will be set if tunning is done or 0 if not
 * @return @ref LIBDFMT_OK on success or @ref Libdfmt_error.
 */
Libdfmt_error libdfmt_tunning_done(Libdfmt_tuner *tuner, int *done);

/**
 * @brief Libdfmt_get_freq reads tunned frequency and metrics from tuner <b>after tunnig/seek</b>.
 * Each parameter of this function (exept tuner) can be NULL if not needed.
 * @param tuner Selected tuner.
 * @param freq Frequency in MHz.
 * @param rssi Reseived signal strength indicator in dBμV.
 * @param snr Signal to noise ration 0-127dB.
 * @param multipath Current multipath metric (0 = no multipath; 100 = full multipath).
 * See Silicon lab's <a href=http://www.silabs.com/Marcom%20Documents/WhitePapers/Automotive-Radio-Key-Requirements.pdf>
 * Key Requirements for Multi-Tuner Automotive Radio Designs</a>.
 * @param is_valid True if tuned frequency is valid channel - you are not receiving noise.
 * @return @ref LIBDFMT_OK on success or @ref Libdfmt_error.
 */  
Libdfmt_error libdfmt_get_freq(Libdfmt_tuner *tuner, double *freq,
                               unsigned *rssi, unsigned *snr,
                               unsigned *multipath, int *is_valid);

/**
 * @brief Libdfmt_get_freq reads metrics from tuner.
 * Each parameter of this function (exept tuner) can be NULL if not needed. Function can be called multiple times.
 * @param tuner Selected tuner..
 * @param rssi Reseived signal strength indicator in dBμV.
 * @param snr Signal to noise ration 0-127dB.
 * @param multipath Current multipath metric (0 = no multipath; 100 = full multipath).
 * See Silicon lab's <a href=http://www.silabs.com/Marcom%20Documents/WhitePapers/Automotive-Radio-Key-Requirements.pdf>
 * Key Requirements for Multi-Tuner Automotive Radio Designs</a>.
 * @param is_valid True if tuned frequency is valid channel - you are not receiving noise.
 * @param freq_offset Frequency offset in kHz.
 * @param stereo_blend 0=full mono 100 full stereo.
 * @return @ref LIBDFMT_OK on success or @ref Libdfmt_error.
 */  
Libdfmt_error libdfmt_get_metrics(Libdfmt_tuner *tuner,
                               unsigned *rssi, unsigned *snr,
                               unsigned *multipath, int *is_valid,
                               int *freq_offset, unsigned *stereo_blend);

/**
 * @brief libdfmt_rds_receiving
 * @param tuner Selected tuner to turn receiving on or off.
 * @param receive 0 stop receiving of rds, any other value turs receiving on.
 * @return @ref LIBDFMT_OK on success or @ref Libdfmt_error.
 */
Libdfmt_error libdfmt_rds_receiving(Libdfmt_tuner *tuner, int receive);

/** @brief Struct representing one group of RDS data.
 *  @see libdfmt_rds_read()
  */
typedef struct{
    uint16_t blockA;
    uint16_t blockB;
    uint16_t blockC;
    uint16_t blockD;
}Libdfmt_rds_group;


/**
 * @brief libdfmt_rds_read Reads one group from tuner's FIFO and/or returns how many groups are stored in tuner.
 *
 * Tuner's FIFO is discarded on every call of libdfmt_seek() or libdfmt_tune().
 * @param tuner Tuner to read from.
 * @param group @ref pointer to Libdfmt_rds_group were received blocks of one group will be stored,
 * or NULL to get only information (without touching FIFO) how many groups are received in tuner's FIFO.
 * Data is only valid when grps_received is greater than zero.
 * @param grps_received Returns how many groups are stored in tuner.
 */
Libdfmt_error libdfmt_rds_read(Libdfmt_tuner *tuner, Libdfmt_rds_group *group, int *grps_received);

/** @} */ // end of hl group

#ifdef __cplusplus
}
#endif

#endif
