C DS1620 Library
===============

[![Build Status](https://img.shields.io/travis/bsail/dallas-ds1620-c/master.svg)](https://travis-ci.org/bsail/dallas-ds1620-c)
[![Coverage Status](https://img.shields.io/coveralls/github/bsail/dallas-ds1620-c/master.svg)](https://coveralls.io/github/bsail/dallas-ds1620-c?branch=master)
<!-- [![Coverity Scan Build Status](https://img.shields.io/coverity/scan/16209.svg)](https://scan.coverity.com/projects/bsail-dallas-ds1620-c) -->

Fork of original library by [jpmulligan](https://github.com/jpmulligan/Arduino-DS1620).

Copyright (C) 2010 John P. Mulligan. All rights reserved.

Forked by Nikolay Nerovny, BMSTU, 2018.

This is an C library for use with the Dallas Semiconductor DS1620 Digital
Thermometer and Thermostat.  Uses 3-wire serial communication.

Latest version of library:

  https://github.com/bsail/dallas-ds1620-c

# Development
For developers looking to extend, bug fix, build, and test this library with dependencies and test infrastructure included in the source tree.

Setup Environment - Ubuntu 16.04/18.04
---------------------------------
```bash
sudo apt install build-essential git ruby gcov lcov
sudo gem install ceedling
```

Get Code
-----------------
```bash
mkdir ds1620
git clone https://github.com/bsail/dallas-ds1620-c ds1620
cd ds1620
```

For a proper integration of this library one should describe the callbacks to access I/O ports for communication with device.
The example implementation of callbacks is given below:
```c
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
  /* In this example we assume that there are two devices with different reset lines;
   * ds1620_current_device is a local variable
   */
  if (ds1620_current_device == 1)
    bit_clear(PORTK, 4);
  else
    bit_clear(PORTK, 5);
}

static void reset_high_callback(void)
{
  /* In this example we assume that there are two devices with different reset lines;
   * ds1620_current_device is a local variable
   */
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
  bit_set(DDRK, 4); /* Reset line for ds1620 #1 */
  bit_set(DDRK, 5); /* Reset line for ds1620 #0 */
  bit_set(DDRK, 6); /* Data line */
  bit_set(DDRK, 7); /* Clock line */
}

static void delay_callback(unsigned long delay_ms)
{
  some_fancy_delay_function(delay_ms);
}
```

# Tests
## Unit Tests

Build & Run Unit Tests
```bash
ceedling test:all
```
Generate LCOV coverage report (`build/lcov/index.html`)
```bash
ceedling lcov
```
You may use and create additional tasks for Ceedling build system. Please refer to the documentation in the `vendor/ceedling/docs`.

# Project Structure
## Source Directories
* /src - library source directory
  * ds1620.h - main header
  * ds1620.c - main implementation
  * ds1620_send_command.h - header of command interface
  * ds1620_send_command.c - implementation of command interface
  * ds1620_receive_data.h - header for data receive subroutine
  * ds1620_receive_data.c - implementation of data receive subroutine
  * ds1620_send_data.h - header for data send subroutine
  * ds1620_send_data.c - implementation of data send subroutine
  * ds1620_reset.h - header for reset functions
  * ds1620_reset.c - implementation of reset functions

* /test
  * test_ds1620.c - Unity test file for ds1620.c module (use `ceedling test:ds1620` to run tests only in this source file)
  * test_ds1620_send_command.c - Unity test file for ds1620_send_command.c module (use `ceedling test:ds1620_send_command` to run tests only in this source file)
  * test_ds1620_receive_data.c - Unity test file for ds1620_receive_data.c module (use `ceedling test:ds1620_receive_data` to run tests only in this source file)
  * test_ds1620_send_data.c - Unity test file for ds1620_send_data.c module (use `ceedling test:ds1620_send_data` to run tests only in this source file)
  * test_ds1620_reset.c - Unity test file for ds1620_reset.c module (use `ceedling test:ds1620_reset` to run tests only in this source file)

* /
  * COPYING - GNU General Public License version 3
  * COPYING.LESSER - GNU Lesser General Public License version 3
  * README.md   - this file
  * project.yml - Ceedling project file including parameters of test compiler and linker
  * .gitignore  - definitions of files and directories to be ignored by git
  * .travis.yml - configuration file for Travis CI
  * Gemfile - list of required gems
  * rakefile.rb - additional configuration of build system


## Third Party Source Directories
* /vendor  - Ceedling source with documentation and plugins

## Build Directories
* /build - Ceedling library build directory
