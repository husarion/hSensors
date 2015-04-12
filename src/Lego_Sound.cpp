#include "Lego_Sound.h"

#include <hFramework.h>

#define SENSOR_ADDRESS 0x01

using namespace hSensors;

Lego_Sound::Lego_Sound(ISensor& sensor) : sens(sensor), initialized(false)
{
}
Lego_Sound::~Lego_Sound()
{
	deinit();
}

void Lego_Sound::init()
{
	if (initialized)
		return;
	sens.selectGPIO();
	sens.getPinIntAdc().enableADC();
	sens.getPin1().setOut();
	initialized = true;
}
void Lego_Sound::deinit()
{
	if (!initialized)
		return;
	sens.getPinIntAdc().disableADC();
	sens.getPin1().setIn();
	initialized = false;
}

int Lego_Sound::readRaw()
{
	init();
	return 4095 - sens.getPinIntAdc().analogReadRaw();
}
int Lego_Sound::readNorm()
{
	init();
	return ((long)readRaw() * (long)100) / (long)4096;
}
void Lego_Sound::setDBA()
{
	init();
	sens.getPin1().write(1);
}
void Lego_Sound::setDB()
{
	init();
	sens.getPin1().write(0);
}

