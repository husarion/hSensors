@PORTS: stm32
@BOARDS: core2, core2mini
@NAME: hitechnic_colorv2
#include <hFramework.h>
#include <Hitechnic_ColorV2.h>

using namespace hSensors;

void hMain(void)
{
	sys.setLogDev(&Serial);  
	hLegoSensor_i2c ls(hSens1); // initialization of Hitechnic ColorV2 sensor
	Hitechnic_ColorV2 sensor(ls);
	
	for (;;)
	{
		uint8_t r, g, b;
		sensor.readRGB(r, g, b); // reading raw data from sensor
		hLED1.toggle(); 	
		printf("r %4d g %4d b %4d\r\n", r, g, b); // printing on Serial console values of variables
		sys.delay(10);
	}
}

