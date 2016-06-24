#include "Mindsensors_SumoEyes.h"

using namespace hSensors;

Mindsensors_SumoEyes::Mindsensors_SumoEyes(ILegoSensor& sensor) : sensor(sensor), initialized(false)
{
}
Mindsensors_SumoEyes::~Mindsensors_SumoEyes()
{
	deinit();
}

void Mindsensors_SumoEyes::init()
{
	if (initialized)
		return;
	sensor.getPinIntAdc().enableADC();
	sensor.getPin1().setOut();
	initialized = true;
}
void Mindsensors_SumoEyes::deinit()
{
	if (!initialized)
		return;
	sensor.getPinIntAdc().disableADC();
	sensor.getPin1().setIn();
	initialized = false;
}

Mindsensors_SumoEyes::Zone Mindsensors_SumoEyes::readZone()
{
	init();
	  int16_t sensordata = 0;
uint32_t k = sensor.getPinIntAdc().analogReadRaw();
	  sensordata = (k)*100/4095;

	   if ( sensordata > 33 && sensordata < 38 )
	   {
	    return FRONT;
	  }
	  else if ( sensordata > 40 && sensordata < 47 )
	  {
	    return LEFT;
	  }
	  else if ( sensordata >= 63 && sensordata <= 70 )
	  {
	    return RIGHT;
	  }
	  else
	  {
	    return NONE;
	  }
}

void Mindsensors_SumoEyes::setLongRange()
{
	init();
	sensor.getPin1().write(1);
}

void Mindsensors_SumoEyes::setShortRange()
{
	init();
	sensor.getPin1().write(0);
}
