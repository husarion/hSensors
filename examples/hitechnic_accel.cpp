@PORTS: stm32
@BOARDS: core2,core2mini
@NAME: hitechnic_accel
#include <hFramework.h>
#include <Hitechnic_Accel.h> 

using namespace hSensors;

void hMain(void)
{
	hLegoSensor_i2c ls(hSens1); // initialization of acceleration sensor
	Hitechnic_Accel sensor(ls);

	for (;;)
	{
		int16_t x, y, z;
		sensor.readRaw(x, y, z); // reading data from sensor
		hLED1.toggle();
		Serial.printf("x %5d y %5d z %5d\r\n", x, y, z); // print data from sensor on Serial console
		sys.delay(10);
	}
}

