#include "Hitechnic_EOPD.h"

#include <hFramework.h>


using namespace hSensors;

Hitechnic_EOPD::Hitechnic_EOPD(ILegoSensor_i2c& sensor) : sens(sensor), initialized(false)
{
}
Hitechnic_EOPD::~Hitechnic_EOPD()
{
	deinit();
}

void Hitechnic_EOPD::init()
{
	if (initialized)
		return;
	sens.getPinIntAdc().enableADC();
	initialized = true;
}
void Hitechnic_EOPD::deinit()
{
	if (!initialized)
		return;
	initialized = false;
}

Hitechnic_EOPD::EError Hitechnic_EOPD::read(data *pDataMsg)
{
	init();
	uint16_t k = sens.getPinIntAdc().analogReadRaw();
	pDataMsg->raw = 4095 - k;
	pDataMsg->processed = round(sqrt(((pDataMsg->raw) / 4) * 10));
	return ERROR_OK;

}

