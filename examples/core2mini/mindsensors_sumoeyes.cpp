#include <hFramework.h>
#include <stdio.h>

#include "Mindsensors_SumoEyes.h"

using namespace hFramework;
using namespace hSensors;

void hMain(void)
{
    hLegoSensor_i2c ls(hSens1);
    Mindsensors_SumoEyes sensor(ls);
	sensor.setLongRange();

	for (;;)
	{
		Mindsensors_SumoEyes::Zone zone;
		zone = sensor.readZone();
		LED1.toggle();
		if(zone == 0)
			printf("obstacle not detected \r\n");
		if(zone == 1)
			printf("obstacle in front of robot \r\n");
		if(zone == 2)
			printf("obstacle on the left \r\n");
		if(zone == 3)
			printf("obstacle on the right \r\n");
		sys.delay_ms(100);
	}
}
