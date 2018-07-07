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
#include "ds1620_reset.h"

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
  io_bit_clear(P_K, 7, io_port);
}

static void clock_high_callback(void)
{
  io_bit_set(P_K, 7, io_port);
}

static void reset_low_callback(void)
{
  if (ds1620_current_device == 1)
    io_bit_clear(P_K, 4, io_port);
  else
    io_bit_clear(P_K, 5, io_port);
}

static void reset_high_callback(void)
{
  if (ds1620_current_device == 1)
    io_bit_set(P_K, 4, io_port);
  else
    io_bit_set(P_K, 5, io_port);
}

static void dq_set_callback(uint8_t bit)
{
  if (bit)
    io_bit_set(P_K, 6, io_port);
  else
    io_bit_clear(P_K, 6, io_port);
}

static uint8_t dq_get_callback(void)
{
  return io_bit_check(P_K, 6);
}

static void dq_set_output_callback(void)
{
  io_bit_set(P_K, 6, io_ddr);
}

static void dq_set_input_callback(void)
{
  io_bit_clear(P_K, 6, io_ddr);
}

static void setup_ports_callback(void)
{
  io_bit_set(P_K, 4, io_ddr);   // pinMode(RST1, OUTPUT);
  io_bit_set(P_K, 5, io_ddr);   // pinMode(RST2, OUTPUT);
  io_bit_set(P_K, 6, io_ddr);   // pinMode(DQ, OUTPUT);
  io_bit_set(P_K, 7, io_ddr);   // pinMode(CLK, OUTPUT);
}

#endif

void ds1620_init(void)
{
  callbacks.setup_ports_callback();
}

int ds1620_read_temp(void)
{
  short t;

  ds1620_rst_start(callbacks);
  ds1620_send_command(READ_TEMP,callbacks); // Next 9 clock cycles, last temp conv result
  t = (short)ds1620_receive_data(callbacks);
  ds1620_rst_stop(callbacks);

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
  int bit;

  high_temp = high_temp * 2;
  ds1620_rst_start(callbacks);
  ds1620_send_command(WRITE_TH,callbacks); // Next 9 clock cycles, value of the high temp limit
  for (int n = 0; n < 9; n++) { // Send all nine bits of temperature
    bit = (high_temp >> n) & 0x01;
    callbacks.dq_set_callback(bit);       //digitalWrite(_DQ, bit); // DQ HIGH or LOW based on bit
    callbacks.clock_low_callback();       ///digitalWrite(_CLK, LOW);  // CLK LOW then HIGH to make one cycle
    callbacks.clock_high_callback();      //digitalWrite(_CLK, HIGH);  
  }
  callbacks.delay_callback(WRITE_DELAY);  // Write can take up to 10ms
  ds1620_rst_stop(callbacks);
}

void ds1620_write_tl(int temp)
{
  int bit;

  temp = temp * 2;
  ds1620_rst_start(callbacks);
  ds1620_send_command(WRITE_TL,callbacks); // Next 9 clock cycles, value of the high temp limit
  for (int n = 0; n < 9; n++) { // Send all nine bits of temperature
    bit = (temp >> n) & 0x01;
    callbacks.dq_set_callback(bit);       //digitalWrite(_DQ, bit); // DQ HIGH or LOW based on bit
    callbacks.clock_low_callback();       //digitalWrite(_CLK, LOW);  // CLK LOW then HIGH to make one cycle
    callbacks.clock_high_callback();      //digitalWrite(_CLK, HIGH);  
  }
  callbacks.delay_callback(WRITE_DELAY);  // Write can take up to 10ms
  ds1620_rst_stop(callbacks);
}

int ds1620_read_th(void)
{
  int temp = 0;

  ds1620_rst_start(callbacks);
  ds1620_send_command(READ_TH,callbacks); // Next 8 clock cycles output value of config register
  temp = ds1620_receive_data(callbacks) / 2;
  ds1620_rst_stop(callbacks);
  return (temp);
}

int ds1620_read_tl(void)
{
  int temp = 0;

  ds1620_rst_start(callbacks);
  ds1620_send_command(READ_TL,callbacks); // Next 8 clock cycles output value of config register
  temp = ds1620_receive_data(callbacks) / 2;
  ds1620_rst_stop(callbacks);
  return (temp);
}

int ds1620_read_counter(void)
{
  int counter = 0;

  ds1620_rst_start(callbacks);
  ds1620_send_command(READ_CNTR,callbacks); // Next 9 clock cycles output value of counter
  counter = ds1620_receive_data(callbacks);
  ds1620_rst_stop(callbacks);
  return (counter);
}

int ds1620_read_slope(void)
{
  int slope = 0;

  ds1620_rst_start(callbacks);
  ds1620_send_command(READ_SLOPE,callbacks); // Next 9 clock cycles output value of counter
  slope = ds1620_receive_data(callbacks);
  ds1620_rst_stop(callbacks);
  return (slope);
}

void ds1620_start_conv(void)
{
  ds1620_rst_start(callbacks);
  ds1620_send_command(START_CNV,callbacks); // Begins temp conv, depends on 1-shot mode   
  ds1620_rst_stop(callbacks);
}

void ds1620_stop_conv(void)
{
  ds1620_rst_start(callbacks);
  ds1620_send_command(STOP_CNV,callbacks); // Stops temperature conversion 
  ds1620_rst_stop(callbacks);
}

int ds1620_write_config(int config_register)
{
  /*
     Return codes:  0 = Write successful
     1 = Write verification failed
     2 = Bad config register
   */
  if (config_register > 0) {
    ds1620_rst_start(callbacks);
    ds1620_send_command(WRITE_CFG,callbacks); // Next 8 clock cycles, value of config register;
    ds1620_send_command(config_register,callbacks);
    callbacks.delay_callback(WRITE_DELAY); // Write can take up to 10ms
    ds1620_rst_stop(callbacks);
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
  int config_register = 0;

  ds1620_rst_start(callbacks);
  ds1620_send_command(READ_CFG,callbacks); // Next 8 clock cycles output value of config register
  config_register = ds1620_receive_data(callbacks);
  ds1620_rst_stop(callbacks);
  return (config_register);
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
