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

#include <xc.h>
#include "drv/utils.h"
#include "tuner_audio.h"
#include "drv/debug_uart.h"


static struct{
    Queue free, filled;
    void *qbuf_free[AUDIO_PACKET_BUFS], *qbuf_filled[AUDIO_PACKET_BUFS];
    AudioFrame  frame_buf[AUDIO_PACKET_BUFS];
}aud_data[2];

static volatile unsigned int *DCHxDSA[] = {&DCH0DSA, &DCH1DSA, &DCH2DSA, &DCH3DSA};
static volatile unsigned int *DCHxDSIZ[] = {&DCH0DSIZ, &DCH1DSIZ, &DCH2DSIZ, &DCH3DSIZ};    
static volatile __DCH0CONbits_t *DCHxCONbits[] = {&DCH0CONbits, 
                                    (__DCH0CONbits_t*)&DCH1CONbits, 
                                    (__DCH0CONbits_t*)&DCH2CONbits, 
                                    (__DCH0CONbits_t*)&DCH3CONbits};
static volatile __DCH0INTbits_t *DCHxINTbits[] = {&DCH0INTbits, 
                                    (__DCH0INTbits_t*)&DCH1INTbits, 
                                    (__DCH0INTbits_t*)&DCH2INTbits, 
                                    (__DCH0INTbits_t*)&DCH3INTbits};

static void arm_dma(int dma)
{
    static char *title[] = {"AD0\r\n","AD1\r\n","AD2\r\n","AD3\r\n"};
    static char *num[] = {"0 ","1 ","2 ","3 ","4 ", "5 ", "6 ", "7 ", "8 ", "9 ", "10 "};
    
    
    int tuner = (dma>1) ? 1 : 0 ;
    
    void *buf = queue_pop(&aud_data[tuner].free);
    if(!buf)
    {
        buf = queue_pop(&aud_data[tuner].filled);
    }
        
    *DCHxDSA[dma]  = virt2phy(buf);
    *DCHxDSIZ[dma] = sizeof(AudioFrame);
}

static void dma_init()
{
    DCH0SSA = DCH1SSA = virt2phy((void*)&SPI1BUF);
    DCH2SSA = DCH3SSA = virt2phy((void*)&SPI2BUF);
    
    DCH0SSIZ = DCH1SSIZ = DCH2SSIZ = DCH3SSIZ = AUDIO_SAMPLE_CHAN_BYTES;
    DCH0CSIZ = DCH1CSIZ = DCH2CSIZ = DCH3CSIZ = AUDIO_SAMPLE_CHAN_BYTES; //bytes per event
    
    DCH0DSIZ = DCH1DSIZ = DCH2DSIZ = DCH3DSIZ = sizeof(AudioFrame);
    
    DCH0CONbits.CHCHN = DCH1CONbits.CHCHN = 1;
    DCH2CONbits.CHCHN = DCH3CONbits.CHCHN = 1;
    //CHCHNS=1 Chain to channel lower in natural priority (CH1 will be enabled by CH2 transfer complete)
    DCH0CONbits.CHCHNS = DCH2CONbits.CHCHNS = 1;
    
    DCH0ECONbits.CHSIRQ = DCH1ECONbits.CHSIRQ = 37;   //cell start interrupt number 
    DCH0ECONbits.SIRQEN = DCH1ECONbits.SIRQEN = 1;    //start cell transfer when chsirq match
    
    DCH2ECONbits.CHSIRQ = DCH3ECONbits.CHSIRQ = 51;   //cell start interrupt number 
    DCH2ECONbits.SIRQEN = DCH3ECONbits.SIRQEN = 1;    //start cell transfer when chsirq match
    
    
    DCH0INT = DCH1INT = DCH2INT = DCH3INT = 0;
    
    
    int i;
    for(i=0; i<4; i++)
        arm_dma(i);    
    
    DCH0INTbits.CHDDIF = DCH1INTbits.CHDDIF = 0;
    DCH2INTbits.CHDDIF = DCH3INTbits.CHDDIF = 0;
    DCH0CONbits.CHEN = 1;
    DCH2CONbits.CHEN = 1;
}

static void i2s_init()
{
    SPI1CONbits.ON = SPI2CONbits.ON = 0;
    Nop();
    SPI1CONbits.DISSDO = SPI2CONbits.DISSDO = 1;     //disable output bit
    //SPI1CONbits.ENHBUF = 1;     //enchanced buffer enable
    SPI1CONbits.MSTEN = 1;      //enable master - we will generate clock on I2S1 not on I2S2!
    SPI1CON2bits.AUDEN = SPI2CON2bits.AUDEN = 1;     //enable audio

    SPI1CONbits.CKP = SPI2CONbits.CKP = 1;        //clock idle in low

    SPI1STATbits.SPIROV = SPI2STATbits.SPIROV = 0;    //no overflow
    
    SPI1BRG = 12;       //clock,  32bit frame X 48khz sampling = 1536kHz - now we have 1?538?461,538461538
    
    IFS1bits.SPI1RXIF = 0;
    IFS1bits.SPI2RXIF = 0;
}

static void i2s_b_init() 
{
    SPI2CONbits.ON = 0;
    _nop();
    SPI2CONbits.DISSDO = 1;     //disable output bit
    //SPI2CONbits.ENHBUF = 1;     //enchanced buffer enable
    SPI2CONbits.MSTEN = 1;      //enable master - we will generate clock
    SPI2CON2bits.AUDEN = 1;     //enable audio
    SPI2CONbits.SRXISEL = 2;    //interrupt is generated whe buffer is half full
    SPI2CONbits.CKP = 1;        //clock idle in low

    while(!SPI2STATbits.SPIRBE)
    {
        int flush = SPI2BUF;
    }
    SPI2STATbits.SPIROV = 0;    //no overflow

    SPI2BRG = 12;       //clock,  32bit frame X 48khz sampling = 1536kHz - now we have 1 538 461,538461538

    IPC9bits.SPI2IP = 4; //prioriy 1-7 0=disabled
    IPC9bits.SPI2IS = 0; //subprio 0-3

    IEC1bits.SPI2RXIE = 1; //enable Rx interrupt
}

void* tuner_audio_get_buf(int tuner)
{
    if (queue_count(&aud_data[tuner].filled) <= 1)
    {
        return NULL;
    }
    else
        return queue_pop(&aud_data[tuner].filled);
}

bool  tuner_audio_put_buf(int tuner, void* buf)
{
    if (queue_full(&aud_data[tuner].free))
        return false;
    else
    {
        queue_push(&aud_data[tuner].free, buf);
        return true;
    }
}



void tuner_audio_init()
{
    int i,j;
    for(i=0; i<2; i++)
    {
        queue_init(&aud_data[i].filled, aud_data[i].qbuf_filled, AUDIO_PACKET_BUFS);
        queue_init(&aud_data[i].free,   aud_data[i].qbuf_free,   AUDIO_PACKET_BUFS);
        
        for (j=0; j<AUDIO_PACKET_BUFS; j++)
            queue_push(&aud_data[i].free, &aud_data[i].frame_buf[j]);
    }
    
    dma_init();
    i2s_init();
    DMACONbits.ON = 1;
    SPI2CONbits.ON = 1;
    SPI1CONbits.ON = 1;
    //TODO i2s_b_init(); nevolat !!
}

void tuner_audio_task()
{
    int i = 0;
    for (;i<4;i++)
    {
        if(DCHxINTbits[i]->CHDDIF)
        {
            DCHxINTbits[i]->CHDDIF = 0;
            if(!queue_push(&aud_data[(i>1)?1:0].filled, phy2virt(*DCHxDSA[i])))
                debughalt(); //TODO vyhodit
            arm_dma(i);
        }
    }
}