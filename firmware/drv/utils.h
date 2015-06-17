
#ifndef UTILS_H
#define	UTILS_H

#include <xc.h>

typedef enum{
    false=0,
    true=1
} bool;

void uint2hex(unsigned number, char* buf, size_t length);
unsigned virt2phy(void* virt_addr);
void* phy2virt(unsigned phy_addr);

#define debughalt() __asm__ volatile (" sdbbp 0")

#endif	/* UTILS_H */

