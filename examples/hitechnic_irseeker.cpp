#include <hFramework.h>
#include <stdio.h>

#include "Hitechnic_IRSeeker.h"

using namespace hFramework;
using namespace hSensors;

void hMain(void)
{

    hLegoSensor_i2c s(hSens1);
    Hitechnic_IRSeeker sensor(s);

	for (;;)
	{
		Hitechnic_IRSeeker::data val;
		sensor.read(&val);
		LED1.toggle();
		printf("Direction of the strongest DC signal: %d, AC signal: %d\r\n",val.dcDirection,val.acDirection);
		printf("AC signal value from all five sensors:");
		for(int i = 0; i<5; i++)
		{
			printf("%d, ", val.acValues[i]);
		}
		printf("\r\n");
		printf("DC signal value from all five sensors:");
		for(int i = 0; i<5; i++)
		{
			printf("%d, ", val.dcValues[i]);
		}
		printf("\r\n");
		printf("Average of DC signal value: %d, direction of the strongest signal: %d, signal strength: %d \r\n", val.dcAvg, val.enhDirection, val.enhStrength);
		sys.delay_ms(100);
	}
}
