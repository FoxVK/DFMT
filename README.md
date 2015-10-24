# DFMT
USB Dual FM tuner radio based on PIC 32MX250F128B (or 32MX220F032B) and two LW/SW/FM receivers with I2S output SI4735-D60.

First version of device will alows you to receive sound from first tuner while second tuner can by used for seeking other stations, reciving RDS, obtaining signal metrics, etc...  Unlike SW and FW, hardware was desinged to be as usiversal as possible, so on pcb is interconnection of both audio outputs with MCU, simplified ISP connector and there are soldering pads for both FM and SW/MW/LW inputs.

#Goal
 Be able to receive FM radio with RDS informations.
 
#State of art:
##Firmware:
* Inicialization of tuners is done.
* USB core is done and working.
* USB sunspend is not implemented. Lower power consupmtion to USB spec. limit is not possible but is planned to make it low as possible.
* USB testmode is not implemented and porbably never be because is useful only for certificaion purposes.
* USB-I2C tunnel is done and tested.
* USB audio is done and tesed. (only a subset of audio 1.0 specification)
* USB VID and PID: Random ones are currently used but there seems to be no porblem to get one from Microchip.
* I2C is done and tested.
* I2S is working but there is a problem with discarding buffers due to USB and I2S clock inaccuracy.

##Software:

### Library libdfmt:
* low level interface: Done and tested exept ping.
* Middle level interface is done and tested.
* High level interface is under construction. Only tune cmd is available right now

### Gui:
* Under heavy development.

## Hardware:
* Schematic was sucessfully tested on breadborad.
* PCB design is done and was send to fab.
![PCB](/hardware/exports/dfmt-top.png)
