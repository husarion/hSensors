#include <hFramework.h>
#include <stdio.h>

#include "Mindsensors_IRDistance.h"

using namespace hFramework;
using namespace hSensors;

void hMain(void)
{
	sys.setLogDev(&Serial);

	Mindsensors_IRDistance sensor(hSens1);

	for (;;)
	{
		int16_t realvalue;
		int16_t voltage;
		sensor.readReal(realvalue);
		sensor.readVoltage(voltage);
		LED1.toggle();
		printf("Real value: %d, voltage value: %d \r\n",realvalue, voltage);
		sys.delay_ms(10);
	}
}
