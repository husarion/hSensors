#include "Lego_Temp.h"

#include <hFramework.h>

#define I2C_ADDR 0x4C
#define TEMP     0x00
#define CONFIG   0x01

using namespace hSensors;


Lego_Temp::Lego_Temp(ILegoSensor_i2c& sensor) : sens(sensor), initialized(false)
{
}
Lego_Temp::~Lego_Temp()
{
	deinit();
}

Lego_Temp::EError Lego_Temp::init()
{
	if (initialized)
		return ERROR_OK;
	sens.selectI2C();
	sens.getI2C().setDataRate(10000);
	initialized = true;

	return ERROR_OK;
}
void Lego_Temp::deinit()
{
	if (!initialized)
		return;
	initialized = false;
}

Lego_Temp::EError Lego_Temp::readConfig(uint8_t &conf)
{
	init();
	uint8_t tx[1];
	tx[0] = CONFIG;
	uint8_t t[1];
	if (!sens.getI2C().rw(I2C_ADDR, tx, 1, t, 1))
		return ERROR_PROTO;
	conf = t[0];
	return ERROR_OK;
}

Lego_Temp::EError Lego_Temp::setConfig(uint8_t conf)
{
	init();
	uint8_t tx[2];
	tx[0] = CONFIG;
	tx[1] = conf;
	if (!sens.getI2C().write(I2C_ADDR, tx, 2))
		return ERROR_PROTO;
	return ERROR_OK;
}

Lego_Temp::Accuracy  Lego_Temp::convertAccuracy(uint8_t conf)
{
	conf = (conf >> 5) & 3;
	switch(conf)
	{
	case 0:
		return A_MIN;
		break;
	case 1:
		return A_MEAN1;
		break;
	case 2:
		return A_MEAN2;
		break;
	case 3:
		return A_MAX;
		break;
	}
	return A_MIN;
}

Lego_Temp::EError Lego_Temp::readTemp(float &v)
{
	init();
	int16_t a1;
	float a2;
	uint8_t conf;

	if(!(readConfig(conf)==ERROR_OK))
		return ERROR_PROTO;
	if ((conf & 1) == 1)
	{
		conf |= (1<<7);
		if(!(setConfig(conf) == ERROR_OK))
			return ERROR_PROTO;
		switch (convertAccuracy(conf))
		{
		case A_MIN:
			sys.delay_ms(28);
			break;
		case A_MEAN1:
			sys.delay_ms(55);
			break;
		case A_MEAN2:
			sys.delay_ms(110);
			break;
		case A_MAX:
			sys.delay_ms(220);
			break;
		}
	}

	uint8_t tx[1];
	tx[0] = TEMP;
	uint8_t t[2];
	if (!sens.getI2C().rw(I2C_ADDR, tx, 1, t, 2))
		return ERROR_PROTO;
	a1 = static_cast<int16_t>(t[0]);
	switch (convertAccuracy(conf))
	{
	case A_MIN:
		a2 = (static_cast<int16_t>(t[1]) >> 7) * 0.5;
		break;
	case A_MEAN1:
		a2 = (static_cast<int16_t>(t[1]) >> 6) * 0.25;
		break;
	case A_MEAN2:
		a2 = (static_cast<int16_t>(t[1]) >> 5) * 0.125;
		break;
	case A_MAX:
		a2 = (static_cast<int16_t>(t[1]) >> 4) * 0.0625;
		break;
	}
	if (a1 < 128) v = a1+a2;
	if (a1 > 127) v = (a1 - 256) + a2;

	return ERROR_OK;

}

Lego_Temp::EError Lego_Temp::readAccuracy(Accuracy &v)
{
	uint8_t conf;
	if(!(readConfig(conf) == ERROR_OK))
		return ERROR_PROTO;
	v = convertAccuracy(conf);
	return ERROR_OK;
}

Lego_Temp::EError Lego_Temp::setAccuracy(Accuracy v)
{
	uint8_t conf;
	if(!(readConfig(conf)) == ERROR_OK)
		return ERROR_PROTO;
	conf &= 0x9F;
	switch (v)
	{
	case A_MIN:
		conf |= 0x00;
		break;
	case A_MEAN1:
		conf |= 0x20;
		break;
	case A_MEAN2:
		conf |= 0x40;
		break;
	case A_MAX:
		conf |= 0x60;
		break;
	}
	return setConfig(conf);
}

Lego_Temp::EError Lego_Temp::setSingleShot()
{
	uint8_t conf;
	if(!(readConfig(conf) == ERROR_OK))
		return ERROR_PROTO;
	conf |= 1;
	return setConfig(conf);
}

Lego_Temp::EError Lego_Temp::setContinuous()
{
	uint8_t conf;
	if(!(readConfig(conf) == ERROR_OK))
		return ERROR_PROTO;
	conf &= 0xFE;
	return setConfig(conf);
}
