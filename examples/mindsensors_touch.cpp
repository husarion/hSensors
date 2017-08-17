@PORTS: stm32
@BOARDS: core2, core2mini
@NAME: mindsensors_touch

#include <hFramework.h>
#include <Mindsensors_Touch.h>

using namespace hSensors;

void hMain(void)
{
	sys.setLogDev(&Serial); 
	hLegoSensor_i2c ls(hSens1);  // initialization of Lego Touch sensor
	Mindsensors_Touch sensor(ls);
	for (;;) 
	{
		bool pressed = sensor.isPressed(); // reading data from sensor
		hLED1.toggle();    
		printf("state %d\r\n", pressed);  // print data from sensor on Serial console
		sys.delay(10); 
	}
}
