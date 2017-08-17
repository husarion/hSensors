@PORTS: stm32
@BOARDS: core2,core2mini
@NAME: mindsensors pressure
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
		hLED1.toggle();
		printf("Pressure: %f \r\n",pressure);
		sys.delay(100);
	}
}
