#include "Hitechnic_Accel.h"

#include <hFramework.h>

#define SENSOR_ADDRESS 0x01

#define REG_MEASUREMENT   0x42

using namespace hSensors;

Hitechnic_Accel::Hitechnic_Accel(hI2C& i2c) : i2c(i2c)
{
}
Hitechnic_Accel::Hitechnic_Accel(hSensor_i2c& sensor) : i2c(sensor.i2c)
{
}
Hitechnic_Accel::~Hitechnic_Accel()
{
}

void Hitechnic_Accel::init()
{
	i2c.setDataRate(10000);
}

Hitechnic_Accel::EError Hitechnic_Accel::readRaw(int16_t& x, int16_t& y, int16_t& z)
{
	uint8_t tx[1], rx[6];
	tx[0] = REG_MEASUREMENT;
	if (!i2c.read(SENSOR_ADDRESS, tx, 1, rx, 6))
		return ERROR_PROTO;
		
	x = ((int16_t)(rx[0] << 8) >> 6) | (rx[3] & 0x03);
	y = ((int16_t)(rx[1] << 8) >> 6) | (rx[4] & 0x03);
	z = ((int16_t)(rx[2] << 8) >> 6) | (rx[5] & 0x03);
	
	return ERROR_OK;
}
Hitechnic_Accel::EError Hitechnic_Accel::read(float& x, float& y, float& z)
{
	int16_t tx, ty, tz;
	
	Hitechnic_Accel::EError res = readRaw(tx, ty, tz);
	if (res != ERROR_OK)
		return res;
		
	x = (float)tx / 200.0f;
	y = (float)ty / 200.0f;
	z = (float)tz / 200.0f;
	
	return ERROR_OK;
}
