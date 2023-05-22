// Copyright (c) Jonathan Petticrew 2018.
// Copyright (c) Pietro Tosato 2022
// Licensed under the MIT LICENSE;
// you may not use this file except in compliance with the License.

#include "MCP4716.h"
#include "mbed.h"


MCP4716::MCP4716(MCP4716Ax_ADDRESS_t addr, I2C *conn) {
  address = addr;
  connection = conn;
  Gain = 0;
  Vref = MCP4716_REF_VDD;
}

uint8_t MCP4716::lowByte(uint16_t x) { return ((uint8_t)(x % 256)); }

uint8_t MCP4716::highByte(uint16_t x) { return ((uint8_t)(x / 256)); }

void MCP4716::setVref(MCP4716_REF_t Vr) { Vref = Vr; }

uint8_t MCP4716::setValue(uint16_t value) {
  uint8_t command;
  command = MCP4716_REGISTER_MODE;
  command += Vref;
  command += Gain;

  value = value << 6;

  buffer[0] = command;
  buffer[1] = highByte(value);
  buffer[2] = lowByte(value);

  if (connection->write((address << 1), buffer, 3) != 0) {
    return 1;
  }

  return 0;

  // uint16_t set= Vout << 6;
  // byte set_upper= (byte) (set >> 8);
  // uint8_t set_l = (uint8_t) set;
  // byte set_lower= (byte) set_l;
}

uint16_t MCP4716::getValue() {
  // TBD
  return 0;
}
