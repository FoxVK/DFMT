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

//For backward compatibility with XC<1.33
#ifndef WINSZ_25
#define WINSZ_25 WISZ_25
#endif

/*** DEVCFG0 ***/

#pragma config DEBUG =      ON
#pragma config JTAGEN =     OFF
#pragma config ICESEL =     ICS_PGx1
#pragma config PWP =        0x3f
#pragma config BWP =        OFF
#pragma config CP =         OFF

/*** DEVCFG1 ***/

#pragma config FNOSC =      PRIPLL
#pragma config FSOSCEN =    OFF
#pragma config IESO =       OFF
#pragma config POSCMOD =    HS
#pragma config OSCIOFNC =   OFF
#pragma config FPBDIV =     DIV_1
#pragma config FCKSM =      CSDCMD
#pragma config WDTPS =      PS1048576
#pragma config FWDTEN =     OFF
#pragma config WINDIS =     OFF
#pragma config FWDTWINSZ =  WINSZ_25

/*** DEVCFG2 ***/

#pragma config FPLLIDIV =   DIV_2
#pragma config FPLLMUL =    MUL_20
#pragma config FPLLODIV =   DIV_2
#pragma config UPLLIDIV =   DIV_2
#pragma config UPLLEN =     ON

/*** DEVCFG3 ***/

#pragma config USERID =     0xcdef
#pragma config PMDL1WAY =   OFF
#pragma config IOL1WAY =    OFF
#pragma config FUSBIDIO =   OFF
#pragma config FVBUSONIO =  OFF

void app_config()
{
    RCON = 0; //FIXME will we need it ?

    //We do not need any analog pin
    ANSELA = 0;
    ANSELB = 0;
    
    TRISBbits.TRISB8 = 1;  //SCL1
    TRISBbits.TRISB9 = 1;  //SDA1

    LATBbits.LATB2 = 0;
    TRISBbits.TRISB2 = 0;

    TRISBbits.TRISB5 = 1;   //SDI1
    TRISBbits.TRISB3 = 0;   //SS 1
    TRISBbits.TRISB14 = 0;  //SCK1

    //Seceond i2s will be driven by first one (must be interconected on board)
    TRISAbits.TRISA4 = 1;   //SDI2
    TRISBbits.TRISB0 = 1;   //SS 2
    TRISBbits.TRISB15 = 1;  //SCK2

    SYSKEY = 0x33333333; //write invalid key to force lock
    SYSKEY = 0xAA996655; //write key1 to SYSKEY
    SYSKEY = 0x556699AA; //write key2 to SYSKEY

    SDI1Rbits.SDI1R = 0b0001;    //SDI1 on RB5
    RPB3Rbits.RPB3R = 0b0011;    //SS 1 on RB3

    SDI2Rbits.SDI2R = 0b0010;    //SDI2 on RA4
    SS2Rbits.SS2R   = 0b0010;    //SS 2 on RB0

    RPB4Rbits.RPB4R = 0b0001;    //uart tx on RB4;

    SYSKEY = 0x33333333; //write invalid key to force lock
}