#include <hFramework.h>
#include <stdio.h>

#include "Hitechnic_Gyro.h"

using namespace hFramework;
using namespace hSensors;

void hMain(void)
{
	sys.setLogDev(&Serial);
	
	Hitechnic_Gyro sensor(hSens1);
	
	for (;;)
	{
		int16_t rot;
		rot = sensor.read();
		LED1.toggle();
		printf("rot %d\r\n", rot);
		sys.delay_ms(10);
	}
}
