#include <hFramework.h>
#include <stdio.h>

#include "Lego_Touch.h"

using namespace hFramework;
using namespace hSensors;

void hMain(void)
{
	sys.setLogDev(&Serial);
	
	Lego_Touch sensor(hSens1);
	
	for (;;)
	{
		bool state = sensor.readState();
		LED1.toggle();
		printf("state %d\r\n", state);
		sys.delay_ms(10);
	}
}
