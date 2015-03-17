#include "lego-touch.h"

void TSinit(ISensor& link)
{
	link.getPinIntAdc().disableADC();
}
void TSdeinit(ISensor& link)
{
}

bool TSreadState(ISensor& link)
{
	return link.getPinIntAdc().read();
}

