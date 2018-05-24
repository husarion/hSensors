#include <hFramework.h>

#include <Lego_Light.h>

using namespace hSensors;

void hMain(void)
{
	sys.setLogDev(&Serial);
	hLegoSensor_simple ls(hSens5);
	Lego_Light sensor(ls);
	
	for (;;)
	{
		int16_t val;
		val = sensor.readRaw();
		LED1.toggle();
		printf("val %5d\r\n", val);
		sys.delay_ms(10);
	}
}
