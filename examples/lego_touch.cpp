@PORTS: stm32
@NAME: lego_touch
#include <hFramework.h>

#include <Lego_Touch.h>

using namespace hSensors;

void hMain(void)
{
	sys.setLogDev(&Serial);
	
{% if board(robocore) %}
	Lego_Touch sensor(hSens5);
{% elif board(core2) %}
	hLegoSensor_simple ls(hSens5);
	Lego_Touch sensor(ls);
{% elif board(core2mini) %}
	hLegoSensor_serial ls(hSens3);
	Lego_Touch sensor(ls);
{% endif %}
	
	for (;;)
	{
		bool pressed = sensor.isPressed();
		LED1.toggle();
		printf("state %d\r\n", pressed);
		sys.delay_ms(10);
	}
}
