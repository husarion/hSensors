#include "Mindsensors_Touch.h"

#include <hFramework.h>

using namespace hSensors;

Mindsensors_Touch::Mindsensors_Touch(ILegoSensor& sensor):sens(sensor), initialized(false){}

Mindsensors_Touch::~Mindsensors_Touch(){
	deinit();
}

void Mindsensors_Touch::Mindsensors_Touch::init(){
	if (initialized)
		return;
	sens.getPin2().setIn();
	initialized = true;
}

void Mindsensors_Touch::Mindsensors_Touch::deinit(){
	if (!initialized)
		return;
	sens.getPin2().reset();
	initialized = false;
}

bool Mindsensors_Touch::Mindsensors_Touch::readState(){
	init();
	return !sens.getPin2().read();
}

bool Mindsensors_Touch::isPressed(){
	return readState() == true;
}

bool Mindsensors_Touch::isReleased(){
	return readState() == false;
}

bool Mindsensors_Touch::waitUntilChange(uint32_t timeout){
	init();
	bool inState = sens.getPin2().read();
	uint32_t inTime = 0;
	while(sens.getPin2().read() == inState || inTime < timeout){
		sys.delay(1);
		inTime ++;
	}
	if(inTime < timeout)
	{
		return true;
	}
	return false;
}