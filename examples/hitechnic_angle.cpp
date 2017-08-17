@PORTS: stm32
@BOARDS: core2,core2mini
@NAME: hitechnic_angle
#include <hFramework.h>
#include <stdio.h>

#include "Hitechnic_Angle.h"

using namespace hFramework;
using namespace hSensors;

void hMain(void)
{
	sys.setLogDev(&Serial);

	hLegoSensor_i2c ls(hSens1); // initialization of acceleration sensor
	Hitechnic_Angle sensor(ls);
	sensor.resetAngle();

	for (;;)
	{
		Hitechnic_Angle::data val;
		sensor.read(&val); // reading data from sensor
		hLED1.toggle();
		printf("Angle: %u, Accumulated angle: %d, rpm: %d \r\n", val.Angle, val.AccumulatedAngle, val.rpm); // print data from sensor on Serial console
		sys.delay(10);
	}
}
