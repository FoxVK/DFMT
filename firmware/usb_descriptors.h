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

#ifndef USB_DESCRIPTORS_H
#define	USB_DESCRIPTORS_H

#include <inttypes.h>
#include "drv/usb.h"

extern const Usb_descriptor_device usb_desc_device;
extern const void* usb_desc_conf1;
extern const void* usb_desc_str[];

#endif	/* USB_DESCRIPTORS_H */

