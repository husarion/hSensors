#include <hFramework.h>
#include <stdio.h>

#include "lego-ultrasonic.h"

using namespace hFramework;

void hMain(void)
{
	sys.setLogDev(&Serial);

	tLegoSensor_i2c sensor(hSens1);
	
	for (;;)
	{
		int dist = USreadDist(sensor);
		LED1.toggle();
		printf("dist %d\r\n", dist);
		sys.delay_ms(10);
	}
}
