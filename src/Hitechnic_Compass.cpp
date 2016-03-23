#include "Hitechnic_Compass.h"

#include <hFramework.h>

#define SENSOR_ADDRESS 0x01

#define REG_MEASUREMENT_MODE   0x00
#define REG_MODE_CONTROL       0x41
#define REG_HEADING_TWO_DEGREE 0x42
#define REG_CALIBRATION_MODE   0x43
#define REG_HEADING_ONE_DEGREE 0x43 // same as above
#define REG_HEADING            0x44 // two bytes

using namespace hSensors;

Hitechnic_Compass::Hitechnic_Compass(ILegoSensor_i2c& sensor) : sens(sensor), initialized(false)
{
}
Hitechnic_Compass::~Hitechnic_Compass()
{
	deinit();
}

void Hitechnic_Compass::init()
{
	if (initialized)
		return;
	sens.selectI2C();
	sens.getI2C().setDataRate(10000);
	initialized = true;
}
void Hitechnic_Compass::deinit()
{
	if (!initialized)
		return;
	initialized = false;
}

Hitechnic_Compass::EError Hitechnic_Compass::startCalibration()
{
	init();
	uint8_t tx[2];
	tx[0] = REG_MODE_CONTROL;
	tx[1] = MODE_CALIBRATION;
	sens.getI2C().write(SENSOR_ADDRESS, tx, 2);
	return ERROR_OK;
}
Hitechnic_Compass::EError Hitechnic_Compass::stopCalibration()
{
	init();
	uint8_t tx[2];
	tx[0] = REG_MODE_CONTROL;
	tx[1] = MODE_MEASURING;
	sens.getI2C().write(SENSOR_ADDRESS, tx, 2);
	return ERROR_OK;
}
Hitechnic_Compass::EError Hitechnic_Compass::getControlMode(uint8_t& mode)
{
	init();
	uint8_t tx[2];
	tx[0] = REG_MODE_CONTROL;
	sens.getI2C().read(SENSOR_ADDRESS, tx, 1, (uint8_t*)&mode, 1);
	return ERROR_OK;
}

Hitechnic_Compass::EError Hitechnic_Compass::readHeading(uint16_t& heading)
{
	init();
	uint8_t tx[1];
	tx[0] = REG_HEADING;
	sens.getI2C().read(SENSOR_ADDRESS, tx, 1, (uint8_t*)&heading, 2);
	
	return ERROR_OK;
}
