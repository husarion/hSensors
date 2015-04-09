#include <hFramework.h>
#include <stdio.h>

#include "Hitechnic_Compass.h"

using namespace hFramework;
using namespace hSensors;

void hMain(void)
{
	sys.setLogDev(&Serial);
	
	Hitechnic_Compass compass(hSens5.getSoftwareI2C());
	
	for (;;)
	{
		uint16_t head;
		compass.readHeading(head);
		LED1.toggle();
		printf("%d\r\n", head);
		sys.delay_ms(10);
	}
}
