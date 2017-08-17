@PORTS: stm32
@BOARDS: core2,core2mini
@NAME: lego_temp
#include <hFramework.h>
#include <stdio.h>

#include "Lego_Temp.h"

using namespace hFramework;
using namespace hSensors;

void hMain(void)
{
	hLegoSensor_i2c s(hSens1); // initialization of Lego Temperature sensor
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
		hLED1.toggle();
		printf("Temperature: %f, current accuracy %d \r\n",temp, A); // print data from sensor on Serial console
		sys.delay(100);
	}
}
