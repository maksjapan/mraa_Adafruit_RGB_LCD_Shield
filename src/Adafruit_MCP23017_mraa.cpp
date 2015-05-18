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

#include <iostream>
#include "mraa.hpp"
#include "Adafruit_MCP23017_mraa.hpp"

#define HIGH 0x1
#define LOW  0x0
#define INPUT 0x0
#define OUTPUT 0x1

////////////////////////////////////////////////////////////////////////////////

Adafruit_MCP23017_mraa::Adafruit_MCP23017_mraa()
{
	// select I2C configuration based on the platform type
	mraa_platform_t platform = mraa_get_platform_type();
	switch (platform)
	{
	case MRAA_INTEL_GALILEO_GEN1:
		i2c = new mraa::I2c(0);
		break;
	case MRAA_INTEL_GALILEO_GEN2:
		i2c = new mraa::I2c(0);
		break;
	case MRAA_INTEL_EDISON_FAB_C:
		i2c = new mraa::I2c(6); //for Edison Arduino board this is 6
		break;
	default:
		std::cerr << "Unsupported platform, probably won't work" << std::endl;
	}
}

Adafruit_MCP23017_mraa::Adafruit_MCP23017_mraa(const unsigned int _busnumber)
{
	//for those that know which I2C bus to select probably knows if the platform is supported or not
	i2c = new mraa::I2c(_busnumber);
}

Adafruit_MCP23017_mraa::~Adafruit_MCP23017_mraa()
{
	delete i2c;
}

void Adafruit_MCP23017_mraa::begin()
{
	// set defaults!
	i2c->address(MCP23017_ADDRESS);
	i2c->writeReg(MCP23017_IODIRA, 0xFF); // all inputs on port A

	i2c->address(MCP23017_ADDRESS);
	i2c->writeReg(MCP23017_IODIRB, 0xFF); // all inputs on port B
}

void Adafruit_MCP23017_mraa::pinMode(uint8_t p, uint8_t d)
{
	uint8_t iodir;
	uint8_t iodiraddr;

	// only 16 bits!
	if (p > 15)
		return;

	if (p < 8)
		iodiraddr = MCP23017_IODIRA;
	else
	{
		iodiraddr = MCP23017_IODIRB;
		p -= 8;
	}

	// read the current IODIR
	i2c->address(MCP23017_ADDRESS);
	iodir = i2c->readReg(iodiraddr);

	// set the pin and direction
	if (d == INPUT)
	{
		iodir |= 1 << p;
	}
	else
	{
		iodir &= ~(1 << p);
	}

	// write the new IODIR
	i2c->address(MCP23017_ADDRESS);
	i2c->writeReg(iodiraddr, iodir);

}

uint16_t Adafruit_MCP23017_mraa::readGPIOAB()
{
	i2c->address(MCP23017_ADDRESS);
	return i2c->readWordReg(MCP23017_GPIOA);;
}

void Adafruit_MCP23017_mraa::writeGPIOAB(uint16_t ba)
{
	i2c->address(MCP23017_ADDRESS);
	i2c->writeWordReg(MCP23017_GPIOA, ba);
}

void Adafruit_MCP23017_mraa::digitalWrite(uint8_t p, uint8_t d)
{
	uint8_t gpio;
	uint8_t gpioaddr, olataddr;

	// only 16 bits!
	if (p > 15)
		return;

	if (p < 8)
	{
		olataddr = MCP23017_OLATA;
		gpioaddr = MCP23017_GPIOA;
	}
	else
	{
		olataddr = MCP23017_OLATB;
		gpioaddr = MCP23017_GPIOB;
		p -= 8;
	}

	// read the current GPIO output latches
	i2c->address(MCP23017_ADDRESS);
	gpio = i2c->readReg(olataddr);

	// set the pin and direction
	if (d == HIGH)
	{
		gpio |= 1 << p;
	}
	else
	{
		gpio &= ~(1 << p);
	}

	// write the new GPIO
	i2c->address(MCP23017_ADDRESS);
	i2c->writeReg(gpioaddr, gpio);

}

void Adafruit_MCP23017_mraa::pullUp(uint8_t p, uint8_t d)
{
	uint8_t gppu;
	uint8_t gppuaddr;

	// only 16 bits!
	if (p > 15)
		return;

	if (p < 8)
		gppuaddr = MCP23017_GPPUA;
	else
	{
		gppuaddr = MCP23017_GPPUB;
		p -= 8;
	}

	// read the current pullup resistor set
	i2c->address(MCP23017_ADDRESS);
	gppu = i2c->readReg(gppuaddr);

	// set the pin and direction
	if (d == 1)
	{
		gppu |= 1 << p;
	}
	else
	{
		gppu &= ~(1 << p);
	}

	// write the new GPIO
	i2c->address(MCP23017_ADDRESS);
	i2c->writeReg(gppuaddr, gppu);
}

uint8_t Adafruit_MCP23017_mraa::digitalRead(uint8_t p)
{
	uint8_t gpioaddr;

	// only 16 bits!
	if (p > 15)
		return 0;

	if (p < 8)
		gpioaddr = MCP23017_GPIOA;
	else
	{
		gpioaddr = MCP23017_GPIOB;
		p -= 8;
	}

	// read the current GPIO
	i2c->address(MCP23017_ADDRESS);
	return (i2c->readReg(gpioaddr) >> p) & 1;
}

