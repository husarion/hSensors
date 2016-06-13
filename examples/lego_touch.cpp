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
		bool pressed = sensor.isPressed();
		LED1.toggle();
		printf("state %d\r\n", pressed);
		sys.delay_ms(10);
	}
}
