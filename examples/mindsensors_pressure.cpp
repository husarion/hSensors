#include <hFramework.h>
#include <stdio.h>

#include "Mindsensors_Pressure.h"

using namespace hFramework;
using namespace hSensors;

void hMain(void)
{
    hLegoSensor_i2c s(hSens1);
    Mindsensors_Pressure sensor(s);

	for (;;)
	{
		float pressure;
		sensor.read(pressure);
		LED1.toggle();
		printf("Pressure: %f \r\n",pressure);
		sys.delay_ms(100);
	}
}
