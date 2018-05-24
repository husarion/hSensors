#include <hFramework.h>
#include <stdio.h>

#include "Mindsensors_Pressure.h"

using namespace hFramework;
using namespace hSensors;

void hMain(void)
{
    Mindsensors_Pressure sensor(hSens1);

	for (;;)
	{
		float pressure;
		sensor.read(pressure);
		LED1.toggle();
		printf("Pressure: %f \r\n",pressure);
		sys.delay_ms(100);
	}
}
