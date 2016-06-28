#include <hFramework.h>
#include <stdio.h>

#include "Mindsensors_Pressure.h"

using namespace hFramework;
using namespace hSensors;

void hMain(void)
{
	sys.setLogDev(&Serial);

	Mindsensors_Pressure sensor(hSens1);

	for (;;)
	{
		float pressure;
		sensor.read(pressure);
		LED1.toggle();
		printf("Pressure: %d \r\n",pressure);
		sys.delay_ms(10);
	}
}
