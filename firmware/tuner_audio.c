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

static void i2s_a_init()
{
    SPI1CONbits.ON = 0;
    Nop();
    SPI1CONbits.DISSDO = 1;     //disable output bit
    //SPI1CONbits.ENHBUF = 1;     //enchanced buffer enable
    SPI1CONbits.MSTEN = 1;      //enable master - we will generate clock
    SPI1CON2bits.AUDEN = 1;     //enable audio
    //SPI1CONbits.SRXISEL = 2;    //interrupt is generated when buffer is half full
    SPI1CONbits.CKP = 1;        //clock idle in low

    while(!SPI1STATbits.SPIRBE)
    {
        int flush = SPI1BUF;
    }
    SPI1STATbits.SPIROV = 0;    //no overflow
    
    SPI1BRG = 12;       //clock,  32bit frame X 48khz sampling = 1536kHz - now we have 1?538?461,538461538

    IPC7bits.SPI1IP = 5; //prioriy 1-7 0=disabled
    IPC7bits.SPI1IS = 0; //subprio 0-3
    
    //IEC1bits.SPI1RXIE = 1; //enable Rx interrupt

    //DMA
    /*DCH0CONbits.CHAEN = 1;      //auto enable
    DCH0ECONbits.CHSIRQ = 37;   //cell start interrupt number 
    DCH0ECONbits.SIRQEN = 1;    //start cell transfer when chsirq match

    DCH0DSA =  VirtToPhy(i2s_buf[0]);
    DCH0DSIZ = I2S_FRAMES * I2S_CHANNELS * I2S_FRAME_SIZE * I2S_SAMPLE_SIZE;

    DCH0SSA = VirtToPhy((void*)&SPI1BUF);
    DCH0SSIZ = I2S_SAMPLE_SIZE;
    DCH0CSIZ = I2S_SAMPLE_SIZE; //bytes per event

    DCH0CONbits.CHEN = 1;       //channel is enabled
     * */
}

static void i2s_b_init()
{
    //TODO make it slave
#warning "make a slave from I2S2"
    SPI2CONbits.ON = 0;
    _nop();
    SPI2CONbits.DISSDO = 1;     //disable output bit
    SPI2CONbits.ENHBUF = 1;     //enchanced buffer enable
    SPI2CONbits.MSTEN = 1;      //enable master - we will generate clock
    SPI2CON2bits.AUDEN = 1;     //enable audio
    SPI2CONbits.SRXISEL = 2;    //interrupt is generated whe buffer is half full
    SPI2CONbits.CKP = 1;        //clock idle in low

    while(!SPI2STATbits.SPIRBE)
    {
        int flush = SPI2BUF;
    }
    SPI2STATbits.SPIROV = 0;    //no overflow

    SPI2BRG = 12;       //clock,  32bit frame X 48khz sampling = 1536kHz - now we have 1?538?461,538461538

    IPC9bits.SPI2IP = 4; //prioriy 1-7 0=disabled
    IPC9bits.SPI2IS = 0; //subprio 0-3

    IEC1bits.SPI2RXIE = 1; //enable Rx interrupt
}

//Start or stop capturing I2S audio
void tuner_audio_run(int tuner_id, int state)
{


    if(tuner_id == 0)
    {
        IFS1CLR = 0b111 << 4;
        SPI1CONbits.ON = 1; //state;
    }
    else
    {
        IFS1CLR = 0b111 << 18;
        SPI2CONbits.ON = 1;
    }        
}



int16_t* tuner_audio_get(const int tuner_id)
{
    const unsigned frame_bytes = I2S_CHANNELS*I2S_FRAME_SIZE*I2S_SAMPLE_SIZE;
    unsigned int dmaptr = (tuner_id == 0) ? DCH0DPTR : DCH1DPTR;
    int buf_part=-1; 
    for(;dmaptr > frame_bytes; dmaptr -= frame_bytes)
        buf_part++;
    
    if(buf_part<0)
        buf_part = I2S_FRAMES - 1;

    return (int16_t*) i2s_buf[tuner_id][buf_part];
}


void tuner_audio_init()
{
    DMACONbits.ON = 1;
    i2s_a_init();
    i2s_b_init();
}