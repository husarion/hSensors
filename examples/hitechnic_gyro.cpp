@PORTS: stm32
@BOARDS: core2
@NAME: hitechnic_gyro
#include <hFramework.h>
#include <Hitechnic_Gyro.h>

using namespace hSensors;

void hMain(void)
{
	sys.setLogDev(&Serial); 
	hLegoSensor_simple ls(hSens5); // initialization of Hitechnic gyro sensor
	Hitechnic_Gyro sensor(ls);
	
	for (;;) 
	{
		int16_t rot;  
		rot = sensor.read();  // reading data from sensor
		hLED1.toggle(); 
		printf("rot %d\r\n", rot); // print data from sensor on Serial console
		sys.delay(10); 
	}
}

@PORTS: stm32
@BOARDS: core2mini
@NAME: hitechnic_gyro
#include <hFramework.h>
#include <Hitechnic_Gyro.h>

using namespace hSensors;

void hMain(void)
{
	sys.setLogDev(&Serial);
	hLegoSensor_simple ls(hSens3); // initialization of Hitechnic gyro sensor
	Hitechnic_Gyro sensor(ls);
	
	for (;;) 
	{
		int16_t rot;  
		rot = sensor.read();   // reading data from sensor
		hLED1.toggle();  
		printf("rot %d\r\n", rot);  // print data from sensor on Serial console
		sys.delay(10); 
	}
}
