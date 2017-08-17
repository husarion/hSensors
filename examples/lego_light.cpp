@PORTS: stm32
@BOARDS: core2
@NAME: lego_light
#include <hFramework.h>
#include <Lego_Light.h>

using namespace hSensors;

void hMain(void)
{
	sys.setLogDev(&Serial); 
	hLegoSensor_simple ls(hSens5);  // initialization of Lego Light sensor
	Lego_Light sensor(ls);

	for (;;)
	{
		int16_t val;  
		val = sensor.readRaw();  // reading raw data from sensor
		hLED1.toggle();  
		printf("val %5d\r\n", val);  // printing data from sensor on Serial console
		sys.delay(10); 
	}
}

@PORTS: stm32
@BOARDS: core2mini
@NAME: lego_light
#include <hFramework.h>
#include <Lego_Light.h>

using namespace hSensors;

void hMain(void)
{
	sys.setLogDev(&Serial);  
	hLegoSensor_simple ls(hSens3);  // initialization of Lego Light sensor
	Lego_Light sensor(ls);

	for (;;) 
	{
		int16_t val; 
		val = sensor.readRaw();  // reading raw data from sensor
		hLED1.toggle(); 
		printf("val %5d\r\n", val);  // printing data from sensor on Serial console
		sys.delay(10); 
	}
}

