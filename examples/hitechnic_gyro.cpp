@PORTS: stm32
@NAME: hitechnic_gyro
#include <hFramework.h>

#include <Hitechnic_Gyro.h>

using namespace hSensors;

void hMain(void)
{
	sys.setLogDev(&Serial);
	
{% if board(robocore) %}
	Hitechnic_Gyro sensor(hSens5);
{% elif board(core2) %}
	hLegoSensor_simple ls(hSens5);
	Hitechnic_Gyro sensor(ls);
{% elif board(core2mini) %}
	hLegoSensor_serial ls(hSens3);
	Hitechnic_Gyro sensor(ls);
{% endif %}
	
	for (;;)
	{
		int16_t rot;
		rot = sensor.read();
		LED1.toggle();
		printf("rot %d\r\n", rot);
		sys.delay_ms(10);
	}
}
