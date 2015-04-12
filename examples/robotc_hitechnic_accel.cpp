#include <hFramework.h>
#include <stdio.h>

#include "hitechnic-accelerometer.h"

using namespace hFramework;

void hMain(void)
{
	sys.setLogDev(&Serial);
	
	tHitechnicSensor sensor1(hSens1);
	tHitechnicSensor sensor2(hSens2);
	
	for (;;)
	{
		int x, y, z;
		int x2, y2, z2;
		HTACreadAllAxes(sensor1, x, y, z);
		HTACreadAllAxes(sensor2, x2, y2, z2);
		LED1.toggle();
		printf("x %5d y %5d z %5d | x %5d y %5d z %5d\r\n", x, y, z, x2, y2, z2);
		sys.delay_ms(10);
	}
}
