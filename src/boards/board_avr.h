/* ########################################################################

   PICsimLab - PIC laboratory simulator

   ########################################################################

   Copyright (c) : 2010-2020  Luis Claudio Gambôa Lopes

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

   For e-mail suggestions :  lcgamboa@yahoo.com
   ######################################################################## */

#ifndef BOARD_AVR_H
#define	BOARD_AVR_H

#include "board.h"

#include <simavr/sim_avr.h>
#include <simavr/avr_ioport.h>
#include <simavr/sim_elf.h>
#include <simavr/sim_hex.h>
#include <simavr/sim_gdb.h>
#include <simavr/avr_adc.h>
#include <simavr/avr_uart.h>
#include <simavr/sim_hex.h>
#include <simavr/avr_twi.h>


class board_avr: virtual public board
{
  public:
      board_avr(void);//Called once on board creation
      int DebugInit(void); 
      void DebugLoop(void);
      int CpuInitialized(void);
      void MSetSerial(const char * port);
      int MInit(const char * processor, const char * fname, float freq);
      void MEnd(void);
      void MDumpMemory(const char * fname);
      void MEraseFlash(void);
      void MSetFreq(float freq);
      float MGetFreq(void);
      float MGetInstClock(void);
      int MGetPinCount(void);
      String MGetPinName(int pin);
      void MSetPin(int pin, unsigned char value);
      void MSetPinDOV(int pin, unsigned char ovalue);      
      void MSetAPin(int pin, float value);
      unsigned char MGetPin(int pin);  
      const picpin * MGetPinsValues(void); 
      void UpdateHardware(void);
      void MStep(void);
      void MStepResume(void);
      int MTestBP(unsigned short bp);
      void MReset(int flags);
      unsigned short * MGetProcID_p(void);
      unsigned short  MGetPC(void);
      void MSetPC(unsigned short pc);
      unsigned char * MGetRAM_p(void);
      unsigned char * MGetROM_p(void);
      unsigned char * MGetCONFIG_p(void);
      unsigned char * MGetID_p(void);
      unsigned char * MGetEEPROM_p(void);
      unsigned int MGetRAMSize(void);
      unsigned int MGetROMSize(void);
      unsigned int MGetCONFIGSize(void);
      unsigned int MGetIDSize(void);
      unsigned int MGetEEPROM_Size(void);
      
      static void out_hook( struct avr_irq_t* irq, uint32_t value, void* param )
      {      
         picpin * p  = (picpin *)param;
         p->value=value;
      }

      static void ddr_hook( struct avr_irq_t* irq, uint32_t value, void* param )
      {
         picpin * p = (picpin *)param;
         p->dir=!(value & (1<<p->pord));
      }
     
 protected:
      avr_t *  avr;
      avr_irq_t * serial_irq;
      picpin pins[256];
      avr_irq_t * Write_stat_irq[28];//FIXME only for atmega328!
      unsigned int serialbaud; 
      float serialexbaud;
      void pins_reset(void);
 private:
      int parse_hex(char *line,int bytes);
      unsigned char checksum(char* str);
      int read_ihx_avr(const char * fname, int leeprom);
      int write_ihx_avr(const char * fname);  
};


#ifdef _WIN_
HANDLE avr_serial_get_fd(void);
#else
int avr_serial_get_fd(void);
#endif

#endif	/* BOARD_AVR_H */

