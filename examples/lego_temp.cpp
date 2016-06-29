#include <hFramework.h>
#include <stdio.h>

#include "Lego_Temp.h"

using namespace hFramework;
using namespace hSensors;

void hMain(void)
{
	hLegoSensor_i2c s(hSens1);
	Lego_Temp sensor(s);
	Lego_Temp::Accuracy Acc;
	Acc = Lego_Temp::Accuracy(1);
	sensor.setAccuracy(Acc);

	for (;;)
	{
		float temp;
		Lego_Temp::Accuracy A;
		sensor.readTemp(temp);
		sensor.readAccuracy(A);
		LED1.toggle();
		printf("Temperature: %f, current accuracy %d \r\n",temp, A);
		sys.delay_ms(100);
	}
}
