#include <hFramework.h>
#include <stdio.h>

#include "Hitechnic_IRSeeker.h"

using namespace hFramework;
using namespace hSensors;

void hMain(void)
{
	sys.setLogDev(&Serial);

	Hitechnic_IRSeeker sensor(hSens1);
	sensor.setModeLong();

	for (;;)
	{/*uint32_t dcDirection;	//!< Direction of the strongest DC signal.
	uint32_t acDirection;	//!< Direction of the strongest AC signal.
	uint32_t enhStrength;	//!< Signal strength.
	uint32_t enhDirection;	//!< Direction of the strongest signal.
	uint32_t acValues[5];	//!< AC signal value from all five sensors.
	uint32_t dcValues[5];	//!< DC signal value from all five sensors.
	uint32_t dcAvg;	*/
		Hitechnic_IRSeeker::data val;
		sensor.read(val);
		LED1.toggle();
		printf("Direction: of the strongest DC signal: %d, of the strongest AC signal: %d, of the strongest signal: %d \r\n",val.dcDirection,val.acDirection, val.enhDirection);
		printf("AC signal value from all five sensors:");
		for(int i = 0; i<5; i++)
		{
			printf("%d, %d, %d, %d, %d", val.acValues[i]);
		}
		printf("\r\n DC signal value from all five sensors:");
		for(int i = 0; i<5; i++)
		{
			printf("%d, %d, %d, %d, %d", val.dcValues[i]);
		}
		printf("\r\n Average of DC signal value: %d, direction of the strongest signal: %d, signal strength: %d", val.dcAvg, val.enhDirection, val.enhStrength);
		sys.delay_ms(10);
	}
}
