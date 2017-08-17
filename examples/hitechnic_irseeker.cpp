@PORTS: stm32
@BOARDS: core2,core2mini
@NAME: hitechnic_irseeker
#include <hFramework.h>
#include <stdio.h>

#include "Hitechnic_IRSeeker.h"

using namespace hFramework;
using namespace hSensors;

void hMain(void)
{

    hLegoSensor_i2c s(hSens1);  // initialization of Hitechnic Compass sensor
    Hitechnic_IRSeeker sensor(s);

	for (;;)
	{
		Hitechnic_IRSeeker::data val;
		sensor.read(&val); // reading raw data from sensor
		hLED1.toggle();
		printf("Direction of the strongest DC signal: %d, AC signal: %d\r\n",val.dcDirection,val.acDirection);
		printf("AC signal value from all five sensors:");
		for(int i = 0; i<5; i++) 
		{
			printf("%d, ", val.acValues[i]); // print AC (modulated IR signals 1200 Hz) value from sensor on Serial console
		}
		printf("\r\n");
		printf("DC signal value from all five sensors:");
		for(int i = 0; i<5; i++)
		{
			printf("%d, ", val.dcValues[i]); // print DC (un-modulated IR signals) value from sensor on Serial console
		}
		printf("\r\n");
		printf("Average of DC signal value: %d, direction of the strongest signal: %d, signal strength: %d \r\n", val.dcAvg, val.enhDirection, val.enhStrength);
		sys.delay(100);
	}
}
