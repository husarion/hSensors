#include <hFramework.h>

#include <Hitechnic_Gyro.h>

using namespace hSensors;

void hMain(void)
{
	sys.setLogDev(&Serial);
	hLegoSensor_serial ls(hSens3);
	Hitechnic_Gyro sensor(ls);
	
	for (;;)
	{
		int16_t rot;
		rot = sensor.read();
		LED1.toggle();
		printf("rot %d\r\n", rot);
		sys.delay_ms(10);
	}
}
