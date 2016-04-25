// <editor-fold defaultstate="collapsed" desc="Copyright">
/*
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
 
    Copyright: Pavel Kovar 2015 <pavel.kovar@vsetin.org>.
 */
// </editor-fold>

#include <inttypes.h>

#include "drv/usb.h"
#include "drv/config.h"
#include "shared.h"

typedef enum {
USB_DSC_DEVICE = 0x01,
USB_DSC_CONFIGURATION = 0x02,
USB_DSC_STRING = 0x03,
USB_DSC_INTERFACE = 0x04,
USB_DSC_ENDPOINT = 0x05,
}USB_descriptor_types;


const static Usb_descriptor_device usb_desc_device =
{
    .bLength            = sizeof(Usb_descriptor_device),
    .bDescriptorType    = USB_DSC_DEVICE,
    .bcdUSB             = 0x0200, //2.0
    .bDeviceClass       = 0x00,
    .bDeviceSubClass    = 0x00,
    .bDeviceProtocol    = 0x00,
    .bMaxPacketSize0    = 64,
    .idVendor           = USB_VID,
    .idProduct          = USB_PID,
    .bcdDevice          = 0x0003,
    .iManufacturer      = 1,
    .iProduct           = 2,
    .iSerialNumber      = 0,
    .bNumConfigurations = 1
};

const static uint8_t usb_desc_conf[] = {
    0x09,//sizeof(USB_CFG_DSC),     // Size of this descriptor in bytes
    0x02,                           // CONFIGURATION descriptor type
    0x09,0x00,                      // Total length of data for this cfg
    0,                              // Number of interfaces in this cfg
    1,                              // Index value of this configuration
    0,                              // Configuration string index
    0b11000000,                     // Attributes
    50,                             // Max power consumption (2X mA) //FIXME:
};
const void * usb_desc_conf1 = usb_desc_conf;



//<editor-fold defaultstate="collapsed" desc="USB strings">
/*******************************************
 *  Language code string descriptor
 *******************************************/
const static struct
{
    uint8_t bLength;
    uint8_t bDscType;
    uint16_t string[1];
}usb_desc_str000=
{
    sizeof(usb_desc_str000),
    USB_DSC_STRING,
    {0x0409}
};

/*******************************************
 *  Manufacturer string descriptor
 *******************************************/
const static struct
{
    uint8_t bLength;
    uint8_t bDscType;
    uint16_t string[15];
}usb_desc_str001=
{
    sizeof(usb_desc_str001),
    USB_DSC_STRING,
    {
        'V','S','B','-','T','U','O',' ','D','i','p','l','o','m','a'
    }
};

/*******************************************
 *  Product string descriptor
 *******************************************/
const static struct
{
    uint8_t bLength;
    uint8_t bDscType;
    uint16_t string[13];
}usb_desc_str002=
{
    sizeof(usb_desc_str002),
    USB_DSC_STRING,
    {
        'D','u','a','l',' ','F','M',' ','T','u','n','e','r'
    }
};
// </editor-fold>

//<editor-fold defaultstate="collapsed" desc="USB configuration descriptor constants">

#define AUDIO_STREAMING_INTERFACE_ID 1
#define AUDIO_CONTROL_INTERFACE_ID 0
#define TUNER_CONTROL_INTERFACE_ID TUNNEL_INTERFACE_ID

#define AUDIO_EP (0x01|(1<<7))

#define ID_INPUT_TERMINAL 1
#define ID_OUTPUT_TERMINAL 2


#define  USB_AUDIO_CLASS_CODE 0x01
typedef enum
{
    USB_AUDIO_SUBCLASS_UNDEFINED    = 0x00,
    USB_AUDIO_AUDIOCONTROL          = 0x01,
    USB_AUDIO_AUDIOSTREAMING        = 0x02,
    USB_AUDIO_MIDISTREAMING         = 0x03

} USB_AUDIO_SUBCLASS_CODE;

typedef enum
{
    USB_AUDIO_CS_UNDEFINED       = 0x20,
    USB_AUDIO_CS_DEVICE          = 0x21,
    USB_AUDIO_CS_CONFIGURATION   = 0x22,
    USB_AUDIO_CS_STRING          = 0x23,
    USB_AUDIO_CS_INTERFACE       = 0x24,
    USB_AUDIO_CS_ENDPOINT        = 0x25

} USB_AUDIO_CS_DESCRIPTOR_TYPE;
typedef enum
{
    USB_AUDIO_AC_DESCRIPTOR_UNDEFINED    = 0x00,
    USB_AUDIO_HEADER                     = 0x01,
    USB_AUDIO_INPUT_TERMINAL             = 0x02,
    USB_AUDIO_OUTPUT_TERMINAL            = 0x03,
    USB_AUDIO_MIXER_UNIT                 = 0x04,
    USB_AUDIO_SELECTOR_UNIT              = 0x05,
    USB_AUDIO_FEATURE_UNIT               = 0x06,
    USB_AUDIO_PROCESSING_UNIT            = 0x07,
    USB_AUDIO_EXTENSION_UNIT             = 0x08,

} USB_AUDIO_CS_AC_INTERFACE_DESCRIPTOR_SUBTYPE;
typedef enum
{
    USB_AUDIO_AS_DESCRIPTOR_UNDEFINED    = 0x00,
    USB_AUDIO_AS_GENERAL                 = 0x01,
    USB_AUDIO_FORMAT_TYPE                = 0x02,
    USB_AUDIO_FORMAT_SPECIFIC            = 0x03

} USB_AUDIO_CS_AS_INTERFACE_DESCRIPTOR_SUBTYPE;


// </editor-fold>

//<editor-fold defaultstate="collapsed" desc="USB configuration descriptor">

const uint8_t conf_desc[] =
{
    /* USB Microphone Configuration Descriptor */
    0x09,//sizeof(USB_CFG_DSC),     // Size of this descriptor in bytes
    USB_DSC_CONFIGURATION,          // CONFIGURATION descriptor type
    0x7F,0x00,                      // Total length of data for this cfg
    3,                              // Number of interfaces in this cfg
    1,                              // Index value of this configuration
    0,                              // Configuration string index
    0b10000000,                     // Attributes
    50,                             // Max power consumption (2X mA) //FIXME

    /* USB Microphone Standard AC Interface Descriptor	*/
    0x09,//sizeof(USB_INTF_DSC),    // Size of this descriptor in bytes
    USB_DSC_INTERFACE,              // INTERFACE descriptor type
    AUDIO_CONTROL_INTERFACE_ID,     // Interface Number
    0x00,                           // Alternate Setting Number
    0x00,                           // Number of endpoints in this intf
    USB_AUDIO_CLASS_CODE,           // Class code
    USB_AUDIO_AUDIOCONTROL,         // Subclass code
    0x00,                           // Protocol code
    0x00,                           // Interface string index

    /* USB Microphone Class-specific AC Interface Descriptor  */
    0x09,                           // Size of this descriptor, in bytes.
    USB_AUDIO_CS_INTERFACE,         // CS_INTERFACE Descriptor Type
    USB_AUDIO_HEADER,               // HEADER descriptor subtype
    0x00,0x01,                      // Audio Device compliant to the USB Audio specification version 1.00
    0x1E,0x00,                      // Total number of bytes returned for the class-specific AudioControl interface descriptor.
                                    // Includes the combined length of this descriptor header and all Unit and Terminal descriptors.
    0x01,                           // The number of AudioStreaming interfaces in the Audio Interface Collection to which this AudioControl interface belongs
    0x01,                           // AudioStreaming interface 1 belongs to this AudioControl interface.

    /*USB Microphone Input Terminal Descriptor */
    0x0C,                           // Size of the descriptor, in bytes
    USB_AUDIO_CS_INTERFACE,         // CS_INTERFACE Descriptor Type
    USB_AUDIO_INPUT_TERMINAL,       // INPUT_TERMINAL descriptor subtype
    ID_INPUT_TERMINAL,              // ID of this Terminal.
    0x10,0x07,                      //Terminal is Fm Rx
    0x00,                           // No association
    0x02,//0x01,                    //two chans
    0x03,0x00,//0x00,0x00,          // L+R cannels
    0x00,                           // Unused.
    0x00,                           // Unused.

    /* USB Microphone Output Terminal Descriptor */
    0x09,                           // Size of the descriptor, in bytes (bLength)
    USB_AUDIO_CS_INTERFACE,         // CS_INTERFACE Descriptor Type (bDescriptorType)
    USB_AUDIO_OUTPUT_TERMINAL,      // OUTPUT_TERMINAL descriptor subtype (bDescriptorSubtype)
    ID_OUTPUT_TERMINAL,             // ID of this Terminal. (bTerminalID)
    0x01,0x01,                      // USB Streaming. (wTerminalType
    0x00,                           // unused (bAssocTerminal)
    ID_INPUT_TERMINAL,              // From Input Terminal.(bSourceID)
    0x00,                           // unused  (iTerminal)

    /* USB Microphone Standard AS Interface Descriptor (Alt. Set. 0) */
    0x09,                           // Size of the descriptor, in bytes (bLength)
    USB_DSC_INTERFACE,       // INTERFACE descriptor type (bDescriptorType)
    AUDIO_STREAMING_INTERFACE_ID,   // Index of this interface. (bInterfaceNumber)
    0x00,                           // Index of this alternate setting. (bAlternateSetting)
    0x00,                           // 0 endpoints. (bNumEndpoints)
    USB_AUDIO_CLASS_CODE,           // AUDIO (bInterfaceClass)
    USB_AUDIO_AUDIOSTREAMING,       // AUDIO_STREAMING (bInterfaceSubclass)
    0x00,                           // Unused. (bInterfaceProtocol)
    0x00,                           // Unused. (iInterface)

    /* USB Microphone Standard AS Interface Descriptor (Alt. Set. 1) */
    0x09,                           // Size of the descriptor, in bytes (bLength)
    USB_DSC_INTERFACE,       // INTERFACE descriptor type (bDescriptorType)
    AUDIO_STREAMING_INTERFACE_ID,   // Index of this interface. (bInterfaceNumber)
    0x01,                           // Index of this alternate setting. (bAlternateSetting)
    0x01,                           // 1 endpoint (bNumEndpoints)
    USB_AUDIO_CLASS_CODE,           // AUDIO (bInterfaceClass)
    USB_AUDIO_AUDIOSTREAMING,       // AUDIO_STREAMING (bInterfaceSubclass)
    0x00,                           // Unused. (bInterfaceProtocol)
    0x00,                           // Unused. (iInterface)

    /*  USB Microphone Class-specific AS General Interface Descriptor */
    0x07,                           // Size of the descriptor, in bytes (bLength)
    USB_AUDIO_CS_INTERFACE,         // CS_INTERFACE Descriptor Type (bDescriptorType)
    USB_AUDIO_AS_GENERAL,           // GENERAL subtype (bDescriptorSubtype)
    ID_OUTPUT_TERMINAL,             // Unit ID of the Output Terminal.(bTerminalLink)
    0x01,                           // Interface delay. (bDelay)
    0x01, 0x00,                     // PCM (formats str29)

    /*  USB Microphone Type I Format Type Descriptor */
    0x0B,                           // Size of the descriptor, in bytes (bLength)
    USB_AUDIO_CS_INTERFACE,         // CS_INTERFACE Descriptor Type (bDescriptorType)
    USB_AUDIO_FORMAT_TYPE,          // FORMAT_TYPE subtype. (bDescriptorSubtype)
    0x01,                           // FORMAT_TYPE_I. (bFormatType)
    0x02,                           // two ch (bNrChannels)
    0x02,                           // Two bytes per audio subframe.(bSubFrameSize)
    0x10,                           // 16 bits per sample.(bBitResolution)
    0x01,                           // One frequency supported. (bSamFreqType)
    0x80,0xBB,0x00,                 // 48khz = BB80 (tSamFreq)

    /*  USB Microphone Standard Endpoint Descriptor */
    0x09,                           // Size of the descriptor, in bytes (bLength)
    USB_DSC_ENDPOINT,        // ENDPOINT descriptor (bDescriptorType)
    AUDIO_EP,                       // Endpoint number. (bEndpointAddress) | direction
    0x01,                           // Isochronous, not shared. (bmAttributes)
    0x80,0x01,//0xC0,0x00,                      // 48*4=192=0x00C0 bytes per packet (wMaxPacketSize)
    0x01,                           // One packet per frame.(bInterval)
    0x00,                           // Unused. (bRefresh)
    0x00,                           // Unused. (bSynchAddress)

    /* USB Microphone Class-specific Isoc. Audio Data Endpoint Descriptor*/
    0x07,                           // Size of the descriptor, in bytes (bLength)
    USB_AUDIO_CS_ENDPOINT,          // CS_ENDPOINT Descriptor Type (bDescriptorType)
    USB_AUDIO_AS_GENERAL,           // GENERAL subtype. (bDescriptorSubtype)
    0x00,                           // No sampling frequency control, no pitch control, no packet padding.(bmAttributes)
    0x00,                           // Unused. (bLockDelayUnits)
    0x00,0x00,                      // Unused. (wLockDelay)

    /* USB Standard VC Interface Descripto (Tuner control)*/
    0x09,//sizeof(USB_INTF_DSC),    // Size of this descriptor in bytes
    USB_DSC_INTERFACE,       // INTERFACE descriptor type
    TUNER_CONTROL_INTERFACE_ID,     // Interface Number
    0x00,                           // Alternate Setting Number
    0x02,                           // Number of endpoints in this intf
    0xff,                           // Class code - VENDOR
    0Xff,                           // Subclass code - VENDOR
    0x00,                           // Protocol code
    0x00,                           // no string descriptor

    /*  USB Standard Endpoint Descriptor (tuner control > host)*/
    0x09,                           // Size of the descriptor, in bytes (bLength)
    USB_DSC_ENDPOINT,        // ENDPOINT descriptor (bDescriptorType)
    TUNNEL_EP_IN,                    // Endpoint number. (bEndpointAddress) | direction
    0x02,                           // Bulk. (bmAttributes)
    0x20,0x00,                      // 32 bytes per packet (wMaxPacketSize)
    0x00,                           // (bInterval) Does not apply to bulk transfer
    0x00,                           // Unused. (bRefresh)
    0x00,                           // Unused. (bSynchAddress)

    /*  USB Standard Endpoint Descriptor (tuner control < host)*/
    0x09,                           // Size of the descriptor, in bytes (bLength)
    USB_DSC_ENDPOINT,        // ENDPOINT descriptor (bDescriptorType)
    TUNNEL_EP_OUT,                   // Endpoint number. (bEndpointAddress) | direction
    0x02,                           // Bulk. (bmAttributes)
    0x20,0x00,                      // 32 bytes per packet (wMaxPacketSize)
    0x00,                           // (bInterval) Does not apply to bulk transfer
    0x00,                           // Unused. (bRefresh)
    0x00,                           // Unused. (bSynchAddress)
};

// </editor-fold>


//<editor-fold defaultstate="collapsed" desc="WCID - descriptors for automatic win driver instalation.">

//https://github.com/pbatard/libwdi/wiki/WCID-Devices#What_is_WCID

const uint8_t wcid_string_desc[] = {
    0x12,                   //BYTE 	Descriptor length (18 bytes)
    USB_DSC_STRING,         //BYTE 	Descriptor type (3 = String)
    0x4D, 0x00, 0x53, 0x00,
    0x46, 0x00, 0x54, 0x00,
    0x31, 0x00, 0x30, 0x00,
    0x30, 0x00,             //7 WORDS Unicode String (LE) 	Signature: "MSFT100"
    0x06,                   //BYTE 	Vendor Code
    0x00,                   //BYTE 	Padding 
};

const uint8_t wcid_feature_desc[] = {
    0x28, 0x00, 0x00, 0x00, ///DWORD (LE) 	Descriptor length (40 bytes)
    0x00, 0x01,             //BCD WORD (LE) 	Version ('1.0')
    0x04, 0x00,             //WORD (LE) 	Compatibility ID Descriptor index (0x0004)
    0x01,                   //BYTE 	Number of sections (1)
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00,       //7 BYTES 	Reserved
    TUNNEL_INTERFACE_ID,    //BYTE 	Interface Number 
    0x01,                   //BYTE 	Reserved
    'L', 'I', 'B', 'U',     //8 BYTES (NUL-terminated?) ASCII String 	Compatible ID ("LIBUSBK\0")
    'S', 'B', 'K', 0x00, 
    0x00, 0x00, 0x00, 0x00, //8 BYTES (NUL-terminated?) ASCII String 	Sub-Compatible ID (unused)
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, //6 BYTES 	Reserved
    0x00, 0x00,                  
};
// </editor-fold>


Usb_config config =
{
  .configuration_desc[0] = (const void*)conf_desc,
  .device_desc           = &usb_desc_device,
  .wcid_feature_desc     = (const void*)wcid_feature_desc,
  .wcid_string_desc      = (const void*)wcid_string_desc,
  .string_descs          = {
                            (void*) &usb_desc_str000,
                            (void*) &usb_desc_str001,
                            (void*) &usb_desc_str002
                            },
};
