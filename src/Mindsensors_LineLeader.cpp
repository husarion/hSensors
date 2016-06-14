#include "Mindsensors_LineLeader.h"

#include <hFramework.h>

#define I2C_ADDR       0x01
#define CMD_REG        0x41

#define SETPOINT       0x45
#define KP_VALUE       0x46
#define KI_VALUE       0X47
#define KD_VALUE       0X48
#define KP_FACTOR      0x61
#define KI_FACTOR      0X62
#define KD_FACTOR      0X63

#define READ_STEERING   0x42
#define READ_AVERAGE    0X43
#define READ_RESULT     0X44
#define SENSOR_RAW     0X49
#define WHITE_LIMIT     0X51
#define BLACK_LIMIT    0X59
#define SENSOR_UNCAL   0x74


using namespace hSensors;


Mindsensors_LineLeader::Mindsensors_LineLeader(ILegoSensor_i2c& sensor) : sens(sensor), initialized(false)
{
}
Mindsensors_LineLeader::~Mindsensors_LineLeader()
{
	deinit();
}

Mindsensors_LineLeader::EError Mindsensors_LineLeader::init()
{
	if (initialized)
		return ERROR_OK;
	sens.selectI2C();
	sens.getI2C().setDataRate(10000);
	if (!initialized)
		return ERROR_PROTO;
	if (wakeUp() == ERROR_PROTO)
		return ERROR_PROTO;
	if (resetLineColor() == ERROR_PROTO)
		return ERROR_PROTO;
	return ERROR_OK;
}
void Mindsensors_LineLeader::deinit()
{
	if (!initialized)
		return;
	initialized = false;
}

Mindsensors_LineLeader::EError Mindsensors_LineLeader::_read(uint8_t regToRead, uint16_t numBytes, uint8_t *pDataTab)
{
	init();
	uint8_t tx[1];
	tx[0] = regToRead;
	if (!sens.getI2C().rw(I2C_ADDR, tx, 1, pDataTab, numBytes))
		return ERROR_PROTO;

	return ERROR_OK;

}

Mindsensors_LineLeader::EError  Mindsensors_LineLeader::_read(uint8_t regToRead, uint8_t *retval)
{
	init();
	uint8_t tx[1];
	tx[0] = regToRead;
	if (!sens.getI2C().rw(I2C_ADDR, tx, 1, retval, 1))
		return ERROR_PROTO;

	return ERROR_OK;

}

Mindsensors_LineLeader::EError  Mindsensors_LineLeader::readSensorRaw(uint8_t *pTab)
{
	return _read(SENSOR_RAW, 8, pTab);

}

Mindsensors_LineLeader::EError  Mindsensors_LineLeader::readResult(uint8_t &v)
{
	uint8_t t[1];
	if ((_read(READ_RESULT, t)) == ERROR_PROTO)
		return ERROR_PROTO;
	v = t[0];
	return ERROR_OK;

}

Mindsensors_LineLeader::EError  Mindsensors_LineLeader::readsetPoint(uint8_t &v)
{
	uint8_t t[1];
	if ((_read(SETPOINT, t)) == ERROR_PROTO)
		return ERROR_PROTO;
	v = t[0];
	return ERROR_OK;

}

Mindsensors_LineLeader::EError  Mindsensors_LineLeader::readAverage(uint8_t &v)
{
	uint8_t t[1];
	if ((_read(READ_AVERAGE, t)) == ERROR_PROTO)
		return ERROR_PROTO;
	v = t[0];
	return ERROR_OK;

}

Mindsensors_LineLeader::EError  Mindsensors_LineLeader::readSteering(int8_t &v)
{
	uint8_t t[1];
	if ((_read(READ_STEERING, t)) == ERROR_PROTO)
		return ERROR_PROTO;
	v = (0xFF & t[0]);
	return ERROR_OK;

}

Mindsensors_LineLeader::EError  Mindsensors_LineLeader::readKp(uint8_t &v)
{
	uint8_t t[1];
	if ((_read(KP_VALUE, t)) == ERROR_PROTO)
		return ERROR_PROTO;
	v = t[0];
	return ERROR_OK;

}

Mindsensors_LineLeader::EError  Mindsensors_LineLeader::readKpFactor(uint8_t &v)
{
	uint8_t t[1];
	if ((_read(KP_FACTOR, t)) == ERROR_PROTO)
		return ERROR_PROTO;
	v = t[0];
	return ERROR_OK;

}

Mindsensors_LineLeader::EError  Mindsensors_LineLeader::readKi(uint8_t &v)
{
	uint8_t t[1];
	if ((_read(KI_VALUE, t)) == ERROR_PROTO)
		return ERROR_PROTO;
	v = t[0];
	return ERROR_OK;

}

Mindsensors_LineLeader::EError  Mindsensors_LineLeader::readKiFactor(uint8_t &v)
{
	uint8_t t[1];
	if ((_read(KI_FACTOR, t)) == ERROR_PROTO)
		return ERROR_PROTO;
	v = t[0];
	return ERROR_OK;

}

Mindsensors_LineLeader::EError  Mindsensors_LineLeader::readKd(uint8_t &v)
{
	uint8_t t[1];
	if ((_read(KD_VALUE, t)) == ERROR_PROTO)
		return ERROR_PROTO;
	v = t[0];
	return ERROR_OK;

}

Mindsensors_LineLeader::EError  Mindsensors_LineLeader::readKdFactor(uint8_t &v)
{
	uint8_t t[1];
	if ((_read(KD_FACTOR, t)) == ERROR_PROTO)
		return ERROR_PROTO;
	v = t[0];
	return ERROR_OK;

}

Mindsensors_LineLeader::EError  Mindsensors_LineLeader::readWhiteThresh(uint8_t *pTab)
{
	return _read(WHITE_LIMIT, 8, pTab);
}

Mindsensors_LineLeader::EError  Mindsensors_LineLeader::readBlackThresh(uint8_t *pTab)
{
	return _read(BLACK_LIMIT, 8, pTab);
}

Mindsensors_LineLeader::EError  Mindsensors_LineLeader::readSensorUncalibrated(int8_t *SensorUncVal)
{
	uint8_t sensorData[16];
	if (_read(SENSOR_UNCAL, 16, sensorData) == ERROR_PROTO)
		return ERROR_PROTO;
	for (uint8_t i = 0; i < 8; ++i)
	{
		SensorUncVal[i] = (0xFF & sensorData[i * 2]) + ((0xFF & sensorData[(i * 2) + 1]) << 8);
	}
	return ERROR_OK;
}


Mindsensors_LineLeader::EError Mindsensors_LineLeader::sendCmd(uint8_t cmd)
{
	init();
	uint8_t tx[2];
	tx[0] = CMD_REG;
	tx[1] = cmd;
	if (!sens.getI2C().write(1, tx, 2))
		return ERROR_PROTO;
	return ERROR_OK;
}

Mindsensors_LineLeader::EError Mindsensors_LineLeader::_write(uint8_t regToWrite, uint8_t data)
{
	init();
	uint8_t tx[2];
	tx[0] = regToWrite;
	tx[1] = data;
	if (!sens.getI2C().write(1, tx, 2))
		return ERROR_PROTO;
	return ERROR_OK;
}

Mindsensors_LineLeader::EError Mindsensors_LineLeader::wakeUp()
{
	return sendCmd('P');
}

Mindsensors_LineLeader::EError Mindsensors_LineLeader::sleep()
{
	return sendCmd('D');
}

Mindsensors_LineLeader::EError Mindsensors_LineLeader::invertLineColor()
{
	return sendCmd('I');
}

Mindsensors_LineLeader::EError Mindsensors_LineLeader::resetLineColor()
{
	return sendCmd('R');
}

Mindsensors_LineLeader::EError Mindsensors_LineLeader::takeSnapshot()
{
	return sendCmd('S');
}

Mindsensors_LineLeader::EError Mindsensors_LineLeader::calWhite()
{
	return sendCmd('W');
}

Mindsensors_LineLeader::EError Mindsensors_LineLeader::calBlack()
{
	return sendCmd('B');
}


Mindsensors_LineLeader::EError Mindsensors_LineLeader::setKp(uint8_t k, uint8_t factor)
{
	if (_write(KP_VALUE, k) == ERROR_PROTO)
		return ERROR_PROTO;
	if (factor == 0) factor = 1;
	if (_write(KP_FACTOR, factor) == ERROR_PROTO)
		return ERROR_PROTO;
	return ERROR_OK;
}

Mindsensors_LineLeader::EError Mindsensors_LineLeader::setKi(uint8_t k, uint8_t factor)
{
	if (_write(KI_VALUE, k) == ERROR_PROTO)
		return ERROR_PROTO;
	if (factor == 0) factor = 1;
	if (_write(KI_FACTOR, factor) == ERROR_PROTO)
		return ERROR_PROTO;
	return ERROR_OK;
}

Mindsensors_LineLeader::EError Mindsensors_LineLeader::setKd(uint8_t k, uint8_t factor)
{
	if (_write(KD_VALUE, k) == ERROR_PROTO)
		return ERROR_PROTO;
	if (factor == 0) factor = 1;
	if (_write(KD_FACTOR, factor) == ERROR_PROTO)
		return ERROR_PROTO;
	return ERROR_OK;
}

Mindsensors_LineLeader::EError Mindsensors_LineLeader::setPoint(uint8_t data)
{
	return _write(SETPOINT, data);
}
