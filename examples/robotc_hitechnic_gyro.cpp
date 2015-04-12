#include <hFramework.h>
#include <stdio.h>

#include "hitechnic-gyro.h"

using namespace hFramework;

void hMain(void)
{
	sys.setLogDev(&Serial);
	
	tHitechnicSensor sensor1(hSens1);
	
	for (;;)
	{
		float r = HTGYROreadRot(sensor1);
		LED1.toggle();
		printf("%f\r\n", r);
		sys.delay_ms(10);
	}
}
