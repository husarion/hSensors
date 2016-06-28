#include <hFramework.h>
#include <stdio.h>

#include "Mindsensors_NumericPad.h"

using namespace hFramework;
using namespace hSensors;

void hMain(void)
{
	sys.setLogDev(&Serial);

	Mindsensors_NumericPad sensor(hSens1);
	Pressed p;

	for (;;)
	{
		sensor.scanKeys(p);
		int16_t result = p.getNumber();
		printf("result: %d pressed: %d \r\n", result, p.pressed);
		p.whichOne();
		if(p.zero())
			printf("0 pressed");
		if(p.one())
			printf("1 pressed");
		if(p.two())
			printf("2 pressed");
		if(p.three())
			printf("3 pressed");
		if(p.four())
			printf("4 pressed");
		if(p.five())
			printf("5 pressed");
		if(p.six())
			printf("6 pressed");
		if(p.seven())
			printf("7 pressed");
		if(p.eight())
			printf("8 pressed");
		if(p.nine())
			printf("9 pressed");
		if(p.hash())
			printf("# pressed");
		if(p.star())
			printf("* pressed");

		LED1.toggle();
		sys.delay_ms(10);
	}
}
