#include "Hitechnic_Gyro.h"

using namespace hSensors;

Hitechnic_Gyro::Hitechnic_Gyro(ILegoSensor& sensor) : sensor(sensor), initialized(false)
{
}
Hitechnic_Gyro::~Hitechnic_Gyro()
{
	deinit();
}

void Hitechnic_Gyro::init()
{
	if (initialized)
		return;
	sensor.getPinIntAdc().enableADC();
	initialized = true;
}
void Hitechnic_Gyro::deinit()
{
	if (!initialized)
		return;
	sensor.getPinIntAdc().disableADC();
	initialized = false;
}

uint16_t Hitechnic_Gyro::read()
{
	init();
	return sensor.getPinIntAdc().analogReadRaw();
}
