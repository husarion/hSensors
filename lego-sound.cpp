#include "lego-sound.h"

static void _init(tLegoSensor& link)
{
	link.sens.selectGPIO();
	link.sens.getPinIntAdc().enableADC();
	link.sens.getPin1().setOut();
	link.initialized = true;
	SNDsetDB(link);
}

int SNDreadRaw(tLegoSensor& link)
{
	if (!link.initialized) _init(link);
	return 4095 - link.sens.getPinIntAdc().analogReadRaw();
}

int SNDreadNorm(tLegoSensor& link)
{
	if (!link.initialized) _init(link);
	return ((long)SNDreadRaw(link) * (long)100) / (long)4096;
}
void SNDsetDBA(tLegoSensor& link)
{
	if (!link.initialized) _init(link);
	link.sens.getPin1().write(1);
}
void SNDsetDB(tLegoSensor& link)
{
	if (!link.initialized) _init(link);
	link.sens.getPin1().write(0);
}

