#include "lusb_error_tr.h"

Libdfmt_error lusb_error_tr(enum libusb_error lusb_err)
{
    //    LIBUSB_SUCCESS              Success (no error)
    //    LIBUSB_ERROR_IO             Input/output error.
    //    LIBUSB_ERROR_INVALID_PARAM	Invalid parameter.
    //    LIBUSB_ERROR_ACCESS         Access denied (insufficient permissions)
    //    LIBUSB_ERROR_NO_DEVICE		No such device (it may have been disconnected)
    //    LIBUSB_ERROR_NOT_FOUND		Entity not found.
    //    LIBUSB_ERROR_BUSY           Resource busy.
    //    LIBUSB_ERROR_TIMEOUT		Operation timed out.
    //    LIBUSB_ERROR_OVERFLOW		Overflow.
    //    LIBUSB_ERROR_PIPE           Pipe error.
    //    LIBUSB_ERROR_INTERRUPTED	System call interrupted (perhaps due to signal)
    //    LIBUSB_ERROR_NO_MEM         Insufficient memory.
    //    LIBUSB_ERROR_NOT_SUPPORTED	Operation not supported or unimplemented on this platform.
    //    LIBUSB_ERROR_OTHER          Other error.

    switch (lusb_err)
    {
    case LIBUSB_SUCCESS:
        return LIBDFMT_OK;

    case LIBUSB_ERROR_TIMEOUT:
        return LIBDFMT_ERROR_TIMEOUT;

    case LIBUSB_ERROR_ACCESS:
        return LIBDFMT_ERROR_NO_PERMISSION;

    case LIBUSB_ERROR_NO_DEVICE:
    case LIBUSB_ERROR_NOT_FOUND:
        libdfmt_scan_devs();
        return LIBDFMT_ERROR_DEVICE_DISCONNECTED;

    default:
        return LIBDFMT_ERROR_USB_ERROR;
    }
}
