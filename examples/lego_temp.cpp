#include <hFramework.h>
#include <stdio.h>

#include "Lego_Temp.h"

using namespace hFramework;
using namespace hSensors;

void hMain(void)
{
	sys.setLogDev(&Serial);

	Lego_Temp sensor(hSens1);
	Lego_Temp::Accuracy Acc;
	Acc = Lego_Temp::Accuracy(1);
	sensor.setAccuracy(Acc);

	for (;;)
	{
		float temp;
		uint8_t conf;
		Lego_Temp::Accuracy A;
		sensor.readTemp(temp);
		sensor.readConfig(conf);
		sensor.readAccuracy(A);
		LED1.toggle();
		printf("Temperature: %f, current configuration: %d, current accuracy \r\n",temp, conf, A);
		sys.delay_ms(10);
	}
}
