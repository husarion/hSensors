#include <hFramework.h>

#include <Hitechnic_ColorV2.h>

using namespace hSensors;

void hMain(void)
{
	sys.setLogDev(&Serial);
	Hitechnic_ColorV2 sensor(hSens1);
	
	for (;;)
	{
		uint8_t r, g, b;
		sensor.readRGB(r, g, b);
		LED1.toggle();
		printf("r %4d g %4d b %4d\r\n", r, g, b);
		sys.delay_ms(10);
	}
}
