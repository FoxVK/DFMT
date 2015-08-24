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


typedef struct
{
    void **array;
    size_t size;
    int head, tail, count;
}Queue;


void  queue_init (Queue *queue, void **array, size_t size);
bool  queue_full (Queue *queue);
bool  queue_empty(Queue *queue);
int   queue_count(Queue *queue);
bool  queue_push (Queue *queue, void* data_ptr);
void* queue_pop  (Queue *queue);


#define debughalt() __asm__ volatile (" sdbbp 0")

#endif	/* UTILS_H */

