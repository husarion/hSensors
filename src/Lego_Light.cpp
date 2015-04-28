#include "Lego_Light.h"

#include <hFramework.h>

#define SENSOR_ADDRESS 0x01

#define REG_MEASUREMENT   0x42

using namespace hSensors;

Lego_Light::Lego_Light(ISensor& sensor) : sens(sensor), initialized(false)
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
	sens.selectGPIO();
	sens.getPinIntAdc().enableADC();
	sens.getPin1().setOut();
	initialized = true;
}
void Lego_Light::deinit()
{
	if (!initialized)
		return;
	sens.getPinIntAdc().disableADC();
	sens.getPin1().setIn();
	initialized = false;
}

int Lego_Light::readRaw()
{
	init();
	return 4095 - sens.getPinIntAdc().analogReadRaw();
}
void Lego_Light::setActive()
{
	init();
	sens.getPin1().write(1);
}
void Lego_Light::setInactive()
{
	init();
	sens.getPin1().write(0);
}
