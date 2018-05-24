#include <hFramework.h>

#include <Lego_Touch.h>

using namespace hSensors;

void hMain(void)
{
	sys.setLogDev(&Serial);
	hLegoSensor_serial ls(hSens3);
	Lego_Touch sensor(ls);
	
	for (;;)
	{
		bool pressed = sensor.isPressed();
		LED1.toggle();
		printf("state %d\r\n", pressed);
		sys.delay_ms(10);
	}
}
