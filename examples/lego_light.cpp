@PORTS: stm32
@NAME: lego_light
#include <hFramework.h>

#include <Lego_Light.h>

using namespace hSensors;

void hMain(void)
{
	sys.setLogDev(&Serial);
	
{% if board(robocore) %}
	Lego_Light sensor(hSens5);
{% elif board(core2) %}
	hLegoSensor_simple ls(hSens5);
	Lego_Light sensor(ls);
{% elif board(core2mini) %}
	hLegoSensor_serial ls(hSens3);
	Lego_Light sensor(ls);
{% endif %}
	
	for (;;)
	{
		int16_t val;
		val = sensor.readRaw();
		LED1.toggle();
		printf("val %5d\r\n", val);
		sys.delay_ms(10);
	}
}
