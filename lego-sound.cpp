#include "lego-sound.h"

void SNDinit(tLegoSensor& link)
{
	link.sens.selectGPIO();
	link.sens.getPinIntAdc().enableADC();
	link.sens.getPin1().setOut();
	SNDsetDB(link);
}
void SNDdeinit(tLegoSensor& link)
{
	link.sens.getPinIntAdc().disableADC();
	link.sens.getPin1().setIn();
}

int SNDreadRaw(tLegoSensor& link)
{
	return 4095 - link.sens.getPinIntAdc().analogReadRaw();
}

int SNDreadNorm(tLegoSensor& link)
{
	return ((long)SNDreadRaw(link) * (long)100) / (long)4096;
}
void SNDsetDBA(tLegoSensor& link)
{
	link.sens.getPin1().write(1);
}
void SNDsetDB(tLegoSensor& link)
{
	link.sens.getPin1().write(0);
}

