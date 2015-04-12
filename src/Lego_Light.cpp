#include "Lego_Light.h"

#include <hFramework.h>

#define SENSOR_ADDRESS 0x01

#define REG_MEASUREMENT   0x42

using namespace hSensors;

Lego_Light::Lego_Light(ISensor_i2c& sensor) : sens(sensor), initialized(false)
{
}
Lego_Light::~Lego_Light()
{
	deinit();
}

void Lego_Light::init()
{
	if (initialized)
		return;
	sens.getI2C().setDataRate(10000);
	initialized = true;
}
void Lego_Light::deinit()
{
	if (!initialized)
		return;
	initialized = false;
}

Lego_Light::EError Lego_Light::readRaw(int16_t& x, int16_t& y, int16_t& z)
{
	init();
	uint8_t tx[1], rx[6];
	tx[0] = REG_MEASUREMENT;
	if (!sens.getI2C().read(SENSOR_ADDRESS, tx, 1, rx, 6))
		return ERROR_PROTO;
		
	x = ((int16_t)(rx[0] << 8) >> 6) | (rx[3] & 0x03);
	y = ((int16_t)(rx[1] << 8) >> 6) | (rx[4] & 0x03);
	z = ((int16_t)(rx[2] << 8) >> 6) | (rx[5] & 0x03);
	
	return ERROR_OK;
}
Lego_Light::EError Lego_Light::read(float& x, float& y, float& z)
{
	init();
	int16_t tx, ty, tz;
	
	Lego_Light::EError res = readRaw(tx, ty, tz);
	if (res != ERROR_OK)
		return res;
		
	x = (float)tx / 200.0f;
	y = (float)ty / 200.0f;
	z = (float)tz / 200.0f;
	
	return ERROR_OK;
}
