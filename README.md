C DS1620 Library 0.2
===============

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
sudo apt install build-essential git ruby
sudo gem install ceedling
```


Get Code
-----------------
```bash
mkdir ds1620
git clone https://github.com/bsail/dallas-ds1620-c ds1620
cd ds1620
```

# Tests
## Unit Tests

Build & Run Unit Tests
```bash
ceedling test:all
```
You may use and create additional tasks for Ceedling build system. Please refer to the documentation in the `vendor/ceedling/docs`.


# Project Structure
## Source Directories
* /src - library source directory
  * ds1620.h - main header
  * ds1620.c - main implementation

* /test
  * test_ds1620.c - Unity test file for ds1620.c module (use `ceedling test:ds1620` to run tests only in this source file)

* /
  * COPYING - GNU General Public License version 3
  * COPYING.LESSER - GNU Lesser General Public License version 3
  * README.md   - this file
  * project.yml - Ceedling project file including parameters of test compiler and linker
  * .gitignore  - definitions of files and directories to be ignored by git


## Third Party Source Directories
* /vendor  - Ceedling source with documentation and plugins

## Build Directories
* /build - Ceedling library build directory
