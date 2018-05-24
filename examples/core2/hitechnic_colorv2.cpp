#include <hFramework.h>

#include <Hitechnic_ColorV2.h>

using namespace hSensors;

void hMain(void)
{
	sys.setLogDev(&Serial);
	hLegoSensor_i2c ls(hSens1);
	Hitechnic_ColorV2 sensor(ls);
	
	for (;;)
	{
		uint8_t r, g, b;
		sensor.readRGB(r, g, b);
		LED1.toggle();
		printf("r %4d g %4d b %4d\r\n", r, g, b);
		sys.delay_ms(10);
	}
}
