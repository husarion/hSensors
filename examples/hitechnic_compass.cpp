@PORTS: stm32
@BOARDS: core2, core2mini
@NAME: hitechnic_compass
#include <hFramework.h>
#include <Hitechnic_Compass.h>

using namespace hSensors;

void hMain(void)
{
	sys.setLogDev(&Serial);
	hLegoSensor_i2c ls(hSens1); // initialization of Hitechnic Compass sensor
	Hitechnic_Compass sensor(ls);

	for (;;) 
	{
		uint16_t heading;
		sensor.readHeading(heading); // reading raw data from sensor
		hLED1.toggle();
		printf("head %d\r\n", heading); // printing on Serial console value of heading variable
		sys.delay(10);
	}
}
