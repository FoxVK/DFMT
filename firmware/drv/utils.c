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

#include "utils.h"

void uint2hex(unsigned number, char* buf, size_t length)
{
    int i;
    const int digits = sizeof(unsigned);

    buf += length-1;

    for(i=0;i<length; i++)
    {
        const int remain = digits - i;
        if(remain>0)
        {
            char digit = number & 0xf;
            *buf = (digit > 9) ? digit+'A'-10 : digit+'0';
            number >>= 4;
        }
        else if (remain == 0)
            *buf = 'x';
        else if (remain == -1)
            *buf = '0';
        else
            *buf = ' ';
        buf--;
    }
}


unsigned virt2phy(void* virt_addr)
{
    return ((unsigned)virt_addr) & 0x1FFFFFFF;
}

void* phy2virt(unsigned phy_addr)
{
    phy_addr |= 0xA0000000;

    union{
        unsigned phy;
        void * virt;
    }addr;

    addr.phy = phy_addr;

    return addr.virt;
}
