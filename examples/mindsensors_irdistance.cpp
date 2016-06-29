#include <hFramework.h>
#include <stdio.h>

#include "Mindsensors_IRDistance.h"

using namespace hFramework;
using namespace hSensors;

void hMain(void)
{
    hLegoSensor_i2c s(hSens1);
    Mindsensors_IRDistance sensor(s);

	for (;;)
	{
		int16_t realvalue;
		int16_t voltage;
		sensor.readReal(realvalue);
		sensor.readVoltage(voltage);
		LED1.toggle();
		printf("Real value: %d, voltage value: %d \r\n",realvalue, voltage);
		sys.delay_ms(100);
	}
}
