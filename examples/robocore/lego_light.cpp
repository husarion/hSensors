#include <hFramework.h>

#include <Lego_Light.h>

using namespace hSensors;

void hMain(void)
{
	sys.setLogDev(&Serial);
	Lego_Light sensor(hSens5);
	
	for (;;)
	{
		int16_t val;
		val = sensor.readRaw();
		LED1.toggle();
		printf("val %5d\r\n", val);
		sys.delay_ms(10);
	}
}
