/*
  Arduino ds1620 Library 0.1
  Copyright (C) 2009 John P. Mulligan. All rights reserved.

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU Lesser General Public License as
  published by the Free Software Foundation, either version 3 of the
  License, or (at your option) any later version.
    
  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.

  Datasheet URL: http://www.maxim-ic.com/quick_view2.cfm/qv_pk/2735

  ds1620 8-Pin DIP Pin Assignment:
  
    1 - DQ         8 - VDD (2.7V - 5.5V)
    2 - CLK/CONV   7 - T HIGH
    3 - RST        6 - T LOW
    4 - GND        5 - T COM

  Serial Communications (3-Wire):

    (1) Set RST high
    (2) Send command, least significant bit first
    (3) Read or write 8-bit config or 9-bit temperature
    (5) Set RST low

*/

#include "ds1620.h"
#include "ds1620_send_command.h"
#include "ds1620_receive_data.h"
#include "ds1620_send_data.h"
#include "ds1620_reset.h"
#include "ds1620_read.h"

// ds1620 Commands

#define READ_TEMP  0xAA         // Read temperature register
#define WRITE_TH   0x01         // Write to the TH (High Temp) register
#define WRITE_TL   0x02         // Write to the TL (Low Temp) register
#define READ_TH    0xA1         // Read the TH (High Temp) register
#define READ_TL    0xA2         // Read the TL (Low Temp) register
#define READ_CNTR  0xA0         // Read the value of the counter byte
#define READ_SLOPE 0xA9         // Read the slope counter byte
#define START_CNV  0xEE         // Begin temperature conversion
#define STOP_CNV   0x22         // Stop temperature conversion
#define WRITE_CFG  0x0C         // Write configuration register
#define READ_CFG   0xAC         // Read the value in the config register

#define WRITE_DELAY 20          // Time to wait (ms) after a EEPROM write

struct ds1620_callbacks callbacks;

#if 0

/* Example implementation of callbacks */

static void clock_low_callback(void)
{
  bit_clear(PORTK, 7);
}

static void clock_high_callback(void)
{
  bit_set(PORTK, 7);
}

static void reset_low_callback(void)
{
  if (ds1620_current_device == 1)
    bit_clear(PORTK, 4);
  else
    bit_clear(PORTK, 5);
}

static void reset_high_callback(void)
{
  if (ds1620_current_device == 1)
    bit_set(PORTK, 4);
  else
    bit_set(PORTK, 5);
}

static void dq_set_callback(uint8_t bit)
{
  if (bit)
    bit_set(PORTK, 6);
  else
    bit_clear(PORTK, 6);
}

static uint8_t dq_get_callback(void)
{
  return bit_check(PORTK, 6);
}

static void dq_set_output_callback(void)
{
  bit_set(DDRK, 6);
}

static void dq_set_input_callback(void)
{
  bit_clear(DDRK, 6);
}

static void setup_ports_callback(void)
{
  bit_set(DDRK, 4);
  bit_set(DDRK, 5);
  bit_set(DDRK, 6);
  bit_set(DDRK, 7);
}

#endif

void ds1620_init(void)
{
  callbacks.setup_ports_callback();
}

int ds1620_read_temp(void)
{
  short t = (short)ds1620_read(READ_TEMP,&callbacks);

  // Check sign bit from Temp
  if (t & 0x0100) {
    // Temperature is negative
    // According to specification: [256 (0x0100) - Temp]
    t &= 0x00FF;                // Remove the sign bit
    t = 0x0100 - t;
    t *= (short)-1;
  }

  t /= 2;

  return (t);
}

void ds1620_write_th(int high_temp)
{
  high_temp = high_temp * 2;
  ds1620_rst_start(&callbacks);
  ds1620_send_command(WRITE_TH,&callbacks); // Next 9 clock cycles, value of the high temp limit
  ds1620_send_data(high_temp,&callbacks);
  callbacks.delay_callback(WRITE_DELAY);  // Write can take up to 10ms
  ds1620_rst_stop(&callbacks);
}

void ds1620_write_tl(int temp)
{
  temp = temp * 2;
  ds1620_rst_start(&callbacks);
  ds1620_send_command(WRITE_TL,&callbacks); // Next 9 clock cycles, value of the high temp limit
  ds1620_send_data(temp,&callbacks);
  callbacks.delay_callback(WRITE_DELAY);  // Write can take up to 10ms
  ds1620_rst_stop(&callbacks);
}

int ds1620_read_th(void)
{
  return ds1620_read(READ_TH,&callbacks)/2;
}

int ds1620_read_tl(void)
{
  return ds1620_read(READ_TL,&callbacks)/2;
}

int ds1620_read_counter(void)
{
  return ds1620_read(READ_CNTR,&callbacks);
}

int ds1620_read_slope(void)
{
  return ds1620_read(READ_SLOPE,&callbacks);
}

void ds1620_start_conv(void)
{
  ds1620_rst_start(&callbacks);
  ds1620_send_command(START_CNV,&callbacks); // Begins temp conv, depends on 1-shot mode   
  ds1620_rst_stop(&callbacks);
}

void ds1620_stop_conv(void)
{
  ds1620_rst_start(&callbacks);
  ds1620_send_command(STOP_CNV,&callbacks); // Stops temperature conversion 
  ds1620_rst_stop(&callbacks);
}

int ds1620_write_config(int config_register)
{
  /*
     Return codes:  0 = Write successful
     1 = Write verification failed
     2 = Bad config register
   */
  if (config_register > 0) {
    ds1620_rst_start(&callbacks);
    ds1620_send_command(WRITE_CFG,&callbacks); // Next 8 clock cycles, value of config register;
    ds1620_send_command(config_register,&callbacks);
    callbacks.delay_callback(WRITE_DELAY); // Write can take up to 10ms
    ds1620_rst_stop(&callbacks);
    // Confirm that config was properly written
    if (ds1620_read_config() == config_register) {
      return 0;
    } else {
      return 1;
    }
  }
  return 2;
}

int ds1620_read_config(void)
{
  return ds1620_read(READ_CFG,&callbacks);
}

void ds1620_clock_low_set_callback(void (*callback) (void))
{
  callbacks.clock_low_callback = callback;
}

void ds1620_clock_high_set_callback(void (*callback) (void))
{
  callbacks.clock_high_callback = callback;
}

void ds1620_reset_low_set_callback(void (*callback) (void))
{
  callbacks.reset_low_callback = callback;
}

void ds1620_reset_high_set_callback(void (*callback) (void))
{
  callbacks.reset_high_callback = callback;
}

void ds1620_dq_set_set_callback(void (*callback) (uint8_t bit))
{
  callbacks.dq_set_callback = callback;
}

void ds1620_dq_get_set_callback(uint8_t(*callback) (void))
{
  callbacks.dq_get_callback = callback;
}

void ds1620_dq_set_output_set_callback(void (*callback) (void))
{
  callbacks.dq_set_output_callback = callback;
}

void ds1620_dq_set_input_set_callback(void (*callback) (void))
{
  callbacks.dq_set_input_callback = callback;
}

void ds1620_setup_ports_set_callback(void (*callback) (void))
{
  callbacks.setup_ports_callback = callback;
}

void ds1620_delay_set_callback(void (*callback) (unsigned long))
{
  callbacks.delay_callback = callback;
}
