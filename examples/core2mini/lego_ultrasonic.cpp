#include <hFramework.h>

#include <Lego_Ultrasonic.h>

using namespace hSensors;

void hMain(void)
{
	sys.setLogDev(&Serial);
	hLegoSensor_i2c ls(hSens1);
	Lego_Ultrasonic sensor(ls);
	
	for (;;)
	{
		int dist = sensor.readDist();
		LED1.toggle();
		printf("dist %d\r\n", dist);
		sys.delay_ms(10);
	}
}
