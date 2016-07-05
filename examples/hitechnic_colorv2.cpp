@PORTS: stm32
@NAME: hitechnic_colorv2
#include <hFramework.h>

#include <Hitechnic_ColorV2.h>

using namespace hSensors;

void hMain(void)
{
	sys.setLogDev(&Serial);
	
{% if board(robocore) %}
	Hitechnic_ColorV2 sensor(hSens1);
{% else %}
	hLegoSensor_i2c ls(hSens1);
	Hitechnic_ColorV2 sensor(ls);
{% endif %}
	
	for (;;)
	{
		uint8_t r, g, b;
		sensor.readRGB(r, g, b);
		LED1.toggle();
		printf("r %4d g %4d b %4d\r\n", r, g, b);
		sys.delay_ms(10);
	}
}
