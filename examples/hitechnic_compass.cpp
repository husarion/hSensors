#include <hFramework.h>
#include <stdio.h>

#include "Hitechnic_Compass.h"

using namespace hFramework;
using namespace hSensors;

void hMain(void)
{
	sys.setLogDev(&Serial);

	Hitechnic_Compass sensor(hSens1);

	for (;;)
	{
		uint16_t heading;
		sensor.readHeading(heading);
		LED1.toggle();
		printf("head %d\r\n", heading);
		sys.delay_ms(10);
	}
}
