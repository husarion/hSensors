#include <hFramework.h>

#include <Lego_Ultrasonic.h>

using namespace hSensors;

void hMain(void)
{
	sys.setLogDev(&Serial);
	Lego_Ultrasonic sensor(hSens1);
	
	for (;;)
	{
		int dist = sensor.readDist();
		LED1.toggle();
		printf("dist %d\r\n", dist);
		sys.delay_ms(10);
	}
}
