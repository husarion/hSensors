#include <hFramework.h>
#include <stdio.h>

#include "Hitechnic_Angle.h"

using namespace hFramework;
using namespace hSensors;

void hMain(void)
{
	sys.setLogDev(&Serial);
	hLegoSensor_i2c ls(hSens1);
	Hitechnic_Accel sensor(ls);
	sensor.resetAngle();

	for (;;)
	{
		Hitechnic_Angle::data val;
		sensor.read(val);
		LED1.toggle();
		printf("Angle: %d, Accumulated angle: %d, rpm: %d \r\n",val.Angle, val.AccumulatedAngle, val.rpm);
		sys.delay_ms(10);
	}
}
