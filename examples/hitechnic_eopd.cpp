@PORTS: stm32
@BOARDS: core2,core2mini
@NAME: hitechnic_eopd
#include <hFramework.h>
#include <stdio.h>

#include "Hitechnic_EOPD.h"

using namespace hFramework;
using namespace hSensors;

void hMain(void)
{
    hLegoSensor_i2c s(hSens1); // initialization of Hitechnic eopd sensor
    Hitechnic_EOPD sensor(s);
    sensor.setModeLong();

	for (;;)
	{
		Hitechnic_EOPD::data val;
		sensor.read(&val); // reading raw data from sensor
		hLED1.toggle();
		printf("Raw value: %d, processed value: %d \r\n",val.raw, val.processed); // print data from sensor on Serial console
		sys.delay(100);
	}
}
