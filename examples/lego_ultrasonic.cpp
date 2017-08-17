@PORTS: stm32
@BOARDS: core2,core2mini
@NAME: lego_ultrasonic

#include <hFramework.h>
#include <Lego_Ultrasonic.h>

using namespace hSensors;

void hMain(void)
{
	sys.setLogDev(&Serial);
	hLegoSensor_i2c ls(hSens1); // initialization of Lego Ultrasonic sensor
	Lego_Ultrasonic sensor(ls);

	for (;;)
	{
		int dist = sensor.readDist(); // reading raw data from sensor
		hLED1.toggle();
		printf("dist %d\r\n", dist); // printing on Serial "dist (value of dist variable)"
		sys.delay(10);
	}
