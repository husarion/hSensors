#include "lego-touch.h"

static void _init(tLegoSensor& link)
{
	link.sens.getPinIntAdc().disableADC();
	link.initialized = true;
}

bool TSreadState(tLegoSensor& link)
{
	if (!link.initialized) _init(link);
	return link.sens.getPinIntAdc().read();
}

