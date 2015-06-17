#include <xc.h>
#include <sys/attribs.h>
#include <inttypes.h>
#include "tuner_com.h"

#define TUNER_A_W 0b00100010 //SEN pin = 0
#define TUNER_B_W 0b11000110 //SEN pin = 1
#define TUNER_A_R 0b00100011 //SEN pin = 0
#define TUNER_B_R 0b11000111 //SEN pin = 1

#define I2S_FRAME_SIZE  (48*2)
#define I2S_CHANNELS    2
#define I2S_FRAMES      3
#define I2S_SAMPLE_SIZE 2

 #define debughalt() __asm__ volatile (" sdbbp 0")

static volatile enum  {
    COM_IDLE,
    COM_START, COM_ADDR_SEND,
    COM_WRITE,
    COM_READ, COM_READ_ACK, COM_READ_NACK,
    COM_STOP,
}com_state;

static volatile enum  {
    COM_DIR_NONE, COM_DIR_READING, COM_DIR_WRITING
}com_dir;

static volatile int com_dir_write = 1;

static volatile Tuner_com_state last_err = TUNER_COM_IDLE;

static volatile uint8_t  *data_buf;
static volatile int      ptr = 0;
static volatile size_t   max_len;

static uint8_t addr = 0;

static volatile int16_t i2s_buf[2][I2S_FRAMES][I2S_FRAME_SIZE*I2S_CHANNELS];

static void i2c_task();

void __ISR (_I2C_1_VECTOR, IPL7AUTO) I2C1Handler (void)
{

    if(IFS1bits.I2C1BIF)
    {
        Nop();
        IFS1bits.I2C1BIF=0;
        debughalt();
    }

    i2c_task();

    IFS1bits.I2C1MIF = 0;
}
void __ISR (_SPI_2_VECTOR, IPL4AUTO) I2SbHandler (void)
{
    static volatile int16_t s = 0 ;
    
    while(!SPI2STATbits.SPIRBE)
        s = SPI2BUF;

    IFS1bits.SPI2RXIF = 0;
}

static void i2c_task()
{
    IEC1bits.I2C1MIE = 0;

    switch(com_state)
    {
        case COM_START:
            if(I2C1CONbits.SEN == 0)
            {
                com_state = COM_ADDR_SEND;
                I2C1TRN = addr;
            }
            break;

        case COM_ADDR_SEND:
            if(I2C1STATbits.TRSTAT == 0)
            {

                if(I2C1STATbits.ACKSTAT == 1)
                {
                    last_err = TUNER_COM_WRONG_ADDR;
                    com_state = COM_STOP;
                    I2C1CONbits.PEN = 1;
                }
                else
                {
                    if(ptr>=max_len)
                    {
                        com_state = COM_STOP;
                        I2C1CONbits.PEN = 1;
                    }
                    else if(com_dir_write)
                    {
                        com_state = COM_WRITE;
                        I2C1TRN = data_buf[ptr];
                    }
                    else
                    {
                        com_state = COM_READ;
                        I2C1CONbits.RCEN = 1;
                    }
                }
            }
            break;

        case COM_WRITE:
            if(I2C1STATbits.TRSTAT == 0)
            {
                ptr++;
                if(ptr>=max_len)
                {
                    com_state = COM_STOP;
                    I2C1CONbits.PEN = 1;
                }
                else
                {
                    I2C1TRN = data_buf[ptr];
                }

            }
            break;

        case COM_READ:
            if(I2C1CONbits.RCEN == 0)
            {
                data_buf[ptr] = I2C1RCV;
                ptr++;
                if(ptr == 1)
                {
                    if((data_buf[0] & 0x80) == 0)
                    {
                        com_state = COM_READ_NACK;
                        I2C1CONbits.ACKDT = 1;
                        I2C1CONbits.ACKEN = 1;
                        
                        last_err = TUNER_COM_DEV_BUSY;
                    }
                }
                if(ptr>=max_len)
                {
                    com_state = COM_READ_NACK;
                    I2C1CONbits.ACKDT = 1;
                    I2C1CONbits.ACKEN = 1;

                }
                else
                {
                    com_state = COM_READ_ACK;
                    I2C1CONbits.ACKDT = 0;
                    I2C1CONbits.ACKEN = 1;
                }
            }
            break;

        case COM_READ_ACK:
            if(I2C1CONbits.ACKEN == 0)
            {
                com_state = COM_READ;
                I2C1CONbits.RCEN = 1;
            }
            break;

        case COM_READ_NACK:
            if(I2C1CONbits.ACKEN == 0)
            {
                com_state = COM_STOP;
                I2C1CONbits.PEN = 1;
            }
            break;

        case COM_STOP:
            if(I2C1CONbits.PEN == 0)
            {
                I2C1CONbits.ON = 0;
                if(last_err == TUNER_COM_BUSY)
                    last_err = TUNER_COM_IDLE;
                com_state = COM_IDLE;
            }
            break;

        default:
            break;
    }

    IEC1bits.I2C1MIE = 1;
}

void tuner_rw_start(void* data, size_t len)
{
    data_buf = (uint8_t*)data;
    max_len = len;
    ptr = 0;
    last_err = TUNER_COM_BUSY;

    I2C1CONbits.ON = 0;

    IFS1bits.I2C1MIF = 0;
    IEC1bits.I2C1MIE = 1;
    I2C1CONbits.ON = 1;
    Nop(); Nop();
}

void tuner_write(int tuner_id, void* data, size_t len)
{
    tuner_rw_start(data, len);
    addr = tuner_id == 1 ? TUNER_B_W : TUNER_A_W;
    com_dir_write = 1;
    com_state = COM_START;
    I2C1CONbits.SEN = 1; //start condition, wait for interrupt

}

void tuner_read(int tuner_id, void* data, size_t len)
{
    tuner_rw_start(data, len);
    addr = tuner_id == 1 ? TUNER_B_R : TUNER_A_R;
    com_dir_write = 0;
    com_state = COM_START;
    I2C1CONbits.SEN = 1; //start condition, wait for interrupt
}

int tuner_bytes_received()
{
    if(com_state == COM_IDLE)
        return ptr;
    else
        return -1;
}

static void i2c_init()
{
    //I2C init
    TRISBbits.TRISB8 = 1;
    TRISBbits.TRISB9 = 1;
    I2C1BRG = /*0x88B;*/0x0C2; //DS 24 str 19: PBclk = 40MHz clk = 100kHz
    I2C1CONbits.DISSLW = 0; //because errata

    IPC8bits.I2C1IP = 7; //prioriy 1-7 0=disabled

    IFS1bits.I2C1MIF = 0;
    IEC1bits.I2C1MIE = 1;

    IFS1bits.I2C1BIF = 0;
    IEC1bits.I2C1BIE = 0;

    com_dir = COM_DIR_NONE;
    com_state = COM_IDLE;
}

void tuner_hold_in_rst(int state)
{
    LATBbits.LATB2 = state ? 0 : 1;
}

void tuner_init()
{
    i2c_init();
}

Tuner_com_state tuner_com_state()
{
    i2c_task();
    return last_err;
}

size_t tuner_rwed_bytes()
{
    return ptr;
}
