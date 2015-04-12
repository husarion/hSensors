#include "Lego_Touch.h"

#include <hFramework.h>

#define SENSOR_ADDRESS 0x01

using namespace hSensors;

Lego_Touch::Lego_Touch(ISensor& sensor) : sens(sensor), initialized(false)
{
}
Lego_Touch::~Lego_Touch()
{
	deinit();
}

void Lego_Touch::init()
{
	if (initialized)
		return;
	sens.getPinIntAdc().disableADC();
	initialized = true;
}
void Lego_Touch::deinit()
{
	if (!initialized)
		return;
	initialized = false;
}

bool Lego_Touch::readState()
{
	init();
	return sens.getPinIntAdc().read();
}

