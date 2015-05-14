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
