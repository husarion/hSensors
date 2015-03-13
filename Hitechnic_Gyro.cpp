#include "Hitechnic_Gyro.h"

using namespace hSensors;

Hitechnic_Gyro::Hitechnic_Gyro(hSensor& sensor) : sensor(sensor)
{
}
Hitechnic_Gyro::~Hitechnic_Gyro()
{
}

void Hitechnic_Gyro::init()
{
	sensor.pinIntAdc.ADC_on();
}
void Hitechnic_Gyro::deinit()
{
	sensor.pinIntAdc.ADC_off();
}

uint16_t Hitechnic_Gyro::read()
{
	return sensor.pinIntAdc.analogRead_d();
}
