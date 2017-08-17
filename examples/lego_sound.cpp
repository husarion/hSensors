@PORTS: stm32
@BOARDS: core2
@NAME: lego_sound
#include <hFramework.h>
#include <Lego_Sound.h>

using namespace hSensors;

void hMain(void)
{
	sys.setLogDev(&Serial); 
	hLegoSensor_simple ls(hSens5); // initialization of Lego Sound sensor
	Lego_Sound sensor(ls);

	for (;;)  
	{
		int16_t val;  
		val = sensor.readRaw(); // reading raw data from sensor
		hLED1.toggle(); 
		printf("val %5d\r\n", val); // print data from sensor on Serial console
		sys.delay(10);  
	}
}

@PORTS: stm32
@BOARDS: core2mini
@NAME: lego_sound
#include <hFramework.h>
#include <Lego_Sound.h>

using namespace hSensors;

void hMain(void)
{
	sys.setLogDev(&Serial); 
	hLegoSensor_simple ls(hSens3); // initialization of Lego Sound sensor
	Lego_Sound sensor(ls);

	for (;;) 
	{
		int16_t val; 
		val = sensor.readRaw(); // reading raw data from sensor
		hLED1.toggle();  
		printf("val %5d\r\n", val); // print data from sensor on Serial console
		sys.delay(10);  
	}
}
