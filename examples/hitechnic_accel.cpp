@PORTS: stm32
@NAME: hitechnic_accel
#include <hFramework.h>

#include <Hitechnic_Accel.h>

using namespace hSensors;

void hMain(void)
{
	sys.setLogDev(&Serial);
	
{% if board(robocore) %}
	Hitechnic_Accel sensor(hSens1);
{% else %}
	hLegoSensor_i2c ls(hSens1);
	Hitechnic_Accel sensor(ls);
{% endif %}
	
	for (;;)
	{
		int16_t x, y, z;
		sensor.readRaw(x, y, z);
		LED1.toggle();
		printf("x %5d y %5d z %5d\r\n", x, y, z);
		sys.delay_ms(10);
	}
}
