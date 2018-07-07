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

*/
#ifndef ds1620_h
#define ds1620_h

#include <inttypes.h>

void ds1620_init(void);
int ds1620_read_temp(void);
void ds1620_write_th(int high_temp);
void ds1620_write_tl(int temp);
int ds1620_read_th(void);
int ds1620_read_tl(void);
int ds1620_read_counter(void);
int ds1620_read_slope(void);
void ds1620_start_conv(void);
void ds1620_stop_conv(void);
int ds1620_write_config(int config_register);
int ds1620_read_config(void);

void ds1620_clock_low_set_callback(void (*callback) (void));
void ds1620_clock_high_set_callback(void (*callback) (void));
void ds1620_reset_low_set_callback(void (*callback) (void));
void ds1620_reset_high_set_callback(void (*callback) (void));
void ds1620_dq_set_set_callback(void (*callback) (uint8_t bit));
void ds1620_dq_get_set_callback(uint8_t(*callback) (void));
void ds1620_dq_set_output_set_callback(void (*callback) (void));
void ds1620_dq_set_input_set_callback(void (*callback) (void));
void ds1620_setup_ports_set_callback(void (*callback) (void));
void ds1620_delay_set_callback(void (*callback) (unsigned long));

#endif
