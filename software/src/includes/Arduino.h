/*
  Arduino.h - Main include file for the Arduino SDK
              Minimum stand in for functionality
  Copyright (c) 2020 guruthree.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef Arduino_h
#define Arduino_h

// replace delay with sleep_ms
#define delay sleep_ms

// Treat reading from flash as reading a regular variable, this is just
// dereferencing the memory address, hopefully a safe hack...
#define pgm_read_byte *

#endif

#include "Print.h"

#define USBDevice TinyUSBDevice
