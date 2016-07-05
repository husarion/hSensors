@PORTS: stm32
@NAME: lego_ultrasonic
#include <hFramework.h>

#include <Lego_Ultrasonic.h>

using namespace hSensors;

void hMain(void)
{
	sys.setLogDev(&Serial);
	
{% if board(robocore) %}
	Lego_Ultrasonic sensor(hSens1);
{% else %}
	hLegoSensor_i2c ls(hSens1);
	Lego_Ultrasonic sensor(ls);
{% endif %}
	
	for (;;)
	{
		int dist = sensor.readDist();
		LED1.toggle();
		printf("dist %d\r\n", dist);
		sys.delay_ms(10);
	}
}
