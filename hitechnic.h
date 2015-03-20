#ifndef __HITECHNIC_H__
#define __HITECHNIC_H__

#include <hFramework.h>

class tHitechnicSensor
{
public:
	tHitechnicSensor(ISensor_i2c& sens) : sens(sens) { }
	ISensor_i2c &sens;
	int mode, state;
};

#endif
