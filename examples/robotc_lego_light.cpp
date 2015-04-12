#include <hFramework.h>
#include <stdio.h>

#include "lego-light.h"

using namespace hFramework;

void hMain(void)
{
	sys.setLogDev(&Serial);

	tLegoSensor sensor1(hSens1);
	tLegoSensor sensor2(hSens2);
	tLegoSensor sensor3(hSens3);
	tLegoSensor sensor4(hSens4);
	tLegoSensor sensor5(hSens5);
	
	for (;;)
	{
		int state1 = LSvalRaw(sensor1);
		int state2 = LSvalRaw(sensor2);
		int state3 = LSvalRaw(sensor3);
		int state4 = LSvalRaw(sensor4);
		int state5 = LSvalRaw(sensor5);
		LED1.toggle();
		printf("val %d %d %d %d %d\r\n", state1, state2, state3, state4, state5);
		sys.delay_ms(10);
	}
}
