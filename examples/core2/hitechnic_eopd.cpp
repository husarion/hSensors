#include <hFramework.h>
#include <stdio.h>

#include "Hitechnic_EOPD.h"

using namespace hFramework;
using namespace hSensors;

void hMain(void)
{
    hLegoSensor_i2c ls(hSens1);
    Hitechnic_EOPD sensor(ls);
    sensor.setModeLong();

	for (;;)
	{
		Hitechnic_EOPD::data val;
		sensor.read(&val);
		LED1.toggle();
		printf("Raw value: %d, processed value: %d \r\n",val.raw, val.processed);
		sys.delay_ms(100);
	}
}
