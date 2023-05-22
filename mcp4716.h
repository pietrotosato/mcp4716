// Copyright (c) Jonathan Petticrew 2018
// Copyright (c) Pietro Tosato 2022
// Licensed under the MIT LICENSE;
// you may not use this file except in compliance with the License.

#ifndef __MCP4716_H_
#define __MCP4716_H_

#include "mbed.h"
#include <stdint.h>

class MCP4716 {
public:

  typedef enum {
    MCP4716A0_ADDR = 0x60,
    MCP4716A1_ADDR = 0x61,
    MCP4716A2_ADDR = 0x62,
    MCP4716A3_ADDR = 0x63,
    MCP4716A4_ADDR = 0x64,
    MCP4716A5_ADDR = 0x65,
    MCP4716A6_ADDR = 0x66,
    MCP4716A7_ADDR = 0x67
  } MCP4716Ax_ADDRESS_t;

  typedef enum {
    MCP4716_FAST_MODE = 0x00, // writes data to DAC register
    MCP4716_REGISTER_MODE =
        0x40, // writes data & configuration bits to DAC register
    MCP4716_EEPROM_MODE =
        0x60 // writes data & configuration bits to DAC register & EEPROM
  } MCP4716_COMMAND_t;

  /* dac register, power down bits */
  typedef enum {
    MCP4716_POWER_DOWN_OFF = 0x00,     // power down off
    MCP4716_POWER_DOWN_1KOHM = 0x01,   // power down on, with 1.0 kOhm to ground
    MCP4716_POWER_DOWN_125KOHM = 0x02, // power down on, with 125 kOhm to ground
    MCP4716_POWER_DOWN_640KOHM = 0x03  // power down on, with 640 kOhm to ground
  } MCP4716_POWER_DOWN_t;

  typedef enum {
    MCP4716_REF_VDD = 0x00,
    MCP4716_REF_VREF = 0x10,
    MCP4716_REF_VREF_BUFF = 0x18,
  } MCP4716_REF_t;

  MCP4716(MCP4716Ax_ADDRESS_t addr, I2C *conn);
  void init(MCP4716Ax_ADDRESS_t addr, I2C *conn);
  // void setGain(int G); // 1=x1, 2=x2
  uint8_t setValue(uint16_t value);
  void setVref(MCP4716_REF_t Vr);
  int getValue();

private:
  I2C *connection;
  MCP4716Ax_ADDRESS_t address;
  MCP4716_REF_t Vref;
  int Gain;

  uint8_t lowByte(uint16_t x);
  uint8_t highByte(uint16_t x);

  
};

#endif
