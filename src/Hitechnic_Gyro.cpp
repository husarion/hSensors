#include "Hitechnic_Gyro.h"

using namespace hSensors;

Hitechnic_Gyro::Hitechnic_Gyro(hSensor& sensor) : sensor(sensor), initialized(false)
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
	sensor.pinIntAdc.enableADC();
	initialized = true;
}
void Hitechnic_Gyro::deinit()
{
	if (!initialized)
		return;
	sensor.pinIntAdc.disableADC();
	initialized = false;
}

uint16_t Hitechnic_Gyro::read()
{
	init();
	return sensor.pinIntAdc.analogReadRaw();
}
