#include "lego-sound.h"

void SNDinit(ISensor& link)
{
	link.selectGPIO();
	link.getPinIntAdc().enableADC();
}
void SNDdeinit(ISensor& link)
{
	link.getPinIntAdc().disableADC();
}

int SNDreadRaw(ISensor& link)
{
	return 4095 - link.getPinIntAdc().analogReadRaw();
}

int SNDreadNorm(ISensor& link)
{
	int _val = ((long)SNDreadRaw(link) * (long)100) / (long)4096;
	return _val;
}
void SNDsetDBA(ISensor& link)
{
	link.getPin1().setOut();
	link.getPin1().write(1);
}
void SNDsetDB(ISensor& link)
{
	link.getPin1().setOut();
	link.getPin1().write(0);
}

