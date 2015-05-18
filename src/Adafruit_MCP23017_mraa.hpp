/***************************************************
  This is a library for the MCP23017 i2c port expander

  These displays use I2C to communicate, 2 pins are required to
  interface
  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.
  BSD license, all text above must be included in any redistribution

  Modified on 2015/05/10 by Makoto Inoue
 ****************************************************/

#ifndef ADAFRUIT_MCP23017_MRAA_HPP_
#define ADAFRUIT_MCP23017_MRAA_HPP_

#include "mraa.hpp"

class Adafruit_MCP23017_mraa
{
public:
	Adafruit_MCP23017_mraa();
	Adafruit_MCP23017_mraa(const unsigned int _busnumber);
	~Adafruit_MCP23017_mraa();
	void begin();

	void pinMode(uint8_t p, uint8_t d);
	void digitalWrite(uint8_t p, uint8_t d);
	void pullUp(uint8_t p, uint8_t d);
	uint8_t digitalRead(uint8_t p);

	void writeGPIOAB(uint16_t);
	uint16_t readGPIOAB();

private:
	mraa::I2c* i2c;
};

#define MCP23017_ADDRESS 0x20

// registers
#define MCP23017_IODIRA 0x00
#define MCP23017_IPOLA 0x02
#define MCP23017_GPINTENA 0x04
#define MCP23017_DEFVALA 0x06
#define MCP23017_INTCONA 0x08
#define MCP23017_IOCONA 0x0A
#define MCP23017_GPPUA 0x0C
#define MCP23017_INTFA 0x0E
#define MCP23017_INTCAPA 0x10
#define MCP23017_GPIOA 0x12
#define MCP23017_OLATA 0x14

#define MCP23017_IODIRB 0x01
#define MCP23017_IPOLB 0x03
#define MCP23017_GPINTENB 0x05
#define MCP23017_DEFVALB 0x07
#define MCP23017_INTCONB 0x09
#define MCP23017_IOCONB 0x0B
#define MCP23017_GPPUB 0x0D
#define MCP23017_INTFB 0x0F
#define MCP23017_INTCAPB 0x11
#define MCP23017_GPIOB 0x13
#define MCP23017_OLATB 0x15

#endif /* ADAFRUIT_MCP23017_MRAA_HPP_ */
