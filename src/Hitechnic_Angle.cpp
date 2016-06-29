#include "Hitechnic_Angle.h"

#include <hFramework.h>
#define I2C_ADDR         0x01
#define CMD_REG          0x41
#define OFFSET           0x42


#define ANG2             0x00

#define CMD_MEASURE      0x00
#define CMD_RST_ANG      0x43
#define CMD_RST_ACC_ANG  0x52


using namespace hSensors;


Hitechnic_Angle::Hitechnic_Angle(ILegoSensor_i2c& sensor) : sens(sensor), initialized(false)
{
}
Hitechnic_Angle::~Hitechnic_Angle()
{
	deinit();
}

Hitechnic_Angle::EError Hitechnic_Angle::init()
{
	if (initialized)
		return ERROR_OK;
	initialized = true;
	sens.selectI2C();
	sens.getI2C().setDataRate(10000);

	return sendCmd(CMD_MEASURE);
}
void Hitechnic_Angle::deinit()
{
	if (!initialized)
		return;
	initialized = false;
}

Hitechnic_Angle::EError Hitechnic_Angle::sendCmd(uint8_t cmd)
{
	uint8_t tx[2];
	tx[0] = CMD_REG;
	tx[1] = cmd;
	if (!sens.getI2C().write(1, tx, 2))
		return ERROR_PROTO;
	return ERROR_OK;
}

Hitechnic_Angle::EError Hitechnic_Angle::read(data *pTab)
{
	init();
	uint8_t tx[1];
	uint8_t DataTab[8];
	tx[0] = OFFSET + ANG2;
	if (!sens.getI2C().rw(I2C_ADDR, tx, 1, DataTab, 8))
		return ERROR_PROTO;
	int32_t angle = (DataTab[0] * 2) + DataTab[1];
	pTab->Angle = (DataTab[0] * 2) + DataTab[1];
	pTab->AccumulatedAngle = (DataTab[2] << 24) + (DataTab[3] << 16) + (DataTab[4] << 8) + DataTab[5];
	pTab->rpm = static_cast<int16_t>(DataTab[6] << 8) + DataTab[7];
	return ERROR_OK;

}

Hitechnic_Angle::EError Hitechnic_Angle::resetAccmulatedAngle()
{
	init();
	sys.delay_ms(70);
	return sendCmd(CMD_RST_ACC_ANG);
}

Hitechnic_Angle::EError Hitechnic_Angle::resetAngle()
{
	init();
	sys.delay_ms(70);
	return sendCmd(CMD_RST_ANG);
}


