#include "Mindsensors_IRDistance.h"

#include <hFramework.h>
#define I2C_ADDR   0x01

#define DIST       0x42
#define VOLT       0x44

using namespace hSensors;


Mindsensors_IRDistance::Mindsensors_IRDistance(ILegoSensor_i2c& sensor) : sens(sensor), initialized(false)
{
}
Mindsensors_IRDistance::~Mindsensors_IRDistance()
{
	deinit();
}

Mindsensors_IRDistance::EError Mindsensors_IRDistance::init()
{
	if (initialized)
		return ERROR_OK;
	sens.selectI2C();
	sens.getI2C().setDataRate(10000);
	initialized = true;

	return ERROR_OK;
}
void Mindsensors_IRDistance::deinit()
{
	if (!initialized)
		return;
	initialized = false;
}

Mindsensors_IRDistance::EError Mindsensors_IRDistance::readReal(int16_t &v)
{
	init();
	uint8_t tx[1];
	tx[0] = DIST;
	uint8_t t[2];
	if (!sens.getI2C().rw(I2C_ADDR, tx, 1, t, 2))
		return ERROR_PROTO;
	v = (0x00FF & t[0]) + ((0x00FF & t[1]) <<8);
	return ERROR_OK;

}

Mindsensors_IRDistance::EError Mindsensors_IRDistance::readVoltage(int16_t &v)
{
	init();
	uint8_t tx[1];
	tx[0] = VOLT;
	uint8_t t[2];
	if (!sens.getI2C().rw(I2C_ADDR, tx, 1, t, 2))
		return ERROR_PROTO;
	v = (0x00FF & t[0]) + ((0x00FF & t[1]) <<8);
	return ERROR_OK;

}
