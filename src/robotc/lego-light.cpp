#include "lego-light.h"

static void _init(tLegoSensor& link)
{
	link.sens.selectGPIO();
	link.sens.getPinIntAdc().enableADC();
	link.sens.getPin1().setOut();
	link.initialized = true;
	LSsetInactive(link);
}

int LSvalRaw(tLegoSensor& link)
{
	if (!link.initialized) _init(link);
	return 4095 - link.sens.getPinIntAdc().analogReadRaw();
}
void LSsetActive(tLegoSensor& link)
{
	if (!link.initialized) _init(link);
	link.sens.getPin1().write(1);
}
void LSsetInactive(tLegoSensor& link)
{
	if (!link.initialized) _init(link);
	link.sens.getPin1().write(0);
}
