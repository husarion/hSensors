#include <hFramework.h>
#include <stdio.h>

#include "Hitechnic_EOPD.h"

using namespace hFramework;
using namespace hSensors;

void hMain(void)
{
	sys.setLogDev(&Serial);

	Hitechnic_EOPD sensor(hSens1);
	sensor.setModeLong();

	for (;;)
	{
		Hitechnic_EOPD::data val;
		sensor.read(val);
		LED1.toggle();
		printf("Raw value: %d, processed value: %d \r\n",val.raw, val.processed);
		sys.delay_ms(10);
	}
}
