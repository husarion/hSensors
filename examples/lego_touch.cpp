@PORTS: stm32
@BOARDS: core2
@NAME: lego_touch

#include <hFramework.h>
#include <Lego_Touch.h>

using namespace hSensors;

void hMain(void)
{
	sys.setLogDev(&Serial); 
	hLegoSensor_simple ls(hSens5);  // initialization of Lego Touch sensor
	Lego_Touch sensor(ls);
	for (;;) 
	{
		bool pressed = sensor.isPressed(); // reading data from sensor
		hLED1.toggle();    
		printf("state %d\r\n", pressed);  // print data from sensor on Serial console
		sys.delay(10); 
	}
}

@PORTS: stm32
@BOARDS: core2mini
@NAME: lego_touch

#include <hFramework.h>
#include <Lego_Touch.h>

using namespace hSensors;

void hMain(void)
{
	sys.setLogDev(&Serial); 
	hLegoSensor_simple ls(hSens3);  // initialization of Lego Touch sensor
	Lego_Touch sensor(ls);
	for (;;)
	{
		bool pressed = sensor.isPressed(); // reading data from sensor
		hLED1.toggle();  
		printf("state %d\r\n", pressed);  // print data from sensor on Serial console
		sys.delay(10); 
	}
}
