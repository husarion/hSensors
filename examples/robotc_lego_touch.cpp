#include <hFramework.h>
#include <stdio.h>

#include "lego-touch.h"

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
		int state1 = TSreadState(sensor1);
		int state2 = TSreadState(sensor2);
		int state3 = TSreadState(sensor3);
		int state4 = TSreadState(sensor4);
		int state5 = TSreadState(sensor5);
		LED1.toggle();
		printf("state %d %d %d %d %d\r\n", state1, state2, state3, state4, state5);
		sys.delay_ms(10);
	}
}
