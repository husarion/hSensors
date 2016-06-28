#include <hFramework.h>
#include <stdio.h>

#include "Mindsensors_SumoEyes.h"

using namespace hFramework;
using namespace hSensors;

void hMain(void)
{
	sys.setLogDev(&Serial);

	Mindsensors_SumoEyes sensor(hSens1);
	sensor.setLongRange();

	for (;;)
	{
		Mindsensors_SumoEyes::Zone zone;
		zone = sensor.readZone();
		LED1.toggle();
		if(zone == 0)
			printf("obstacle not detected");
		if(zone == 1)
			printf("obstacle in front of robot");
		if(zone == 2)
			printf("obstacle on the left");
		if(zone == 3)
			printf("obstacle on the right");
		sys.delay_ms(10);
	}
}
