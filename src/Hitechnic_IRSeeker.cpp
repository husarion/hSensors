#include "Hitechnic_IRSeeker.h"

#include <hFramework.h>

#define I2C_ADDR    0x08
#define DSP_MODE    0x41
#define OFFSET      0x42
#define DC_DIR      0x00
#define DC_SSTR1    0x01
#define DC_SAVG     0x06
#define AC_DIR      0x07
#define AC_SSTR1    0x08

#define DSP_1200    0

using namespace hSensors;

Hitechnic_IRSeeker::Hitechnic_IRSeeker(ILegoSensor_i2c& sensor) : sens(sensor), initialized(false)
{
}
Hitechnic_IRSeeker::~Hitechnic_IRSeeker()
{
	deinit();
}

Hitechnic_IRSeeker::EError Hitechnic_IRSeeker::init()
{
	if (initialized)
		return ERROR_OK;
	sens.selectI2C();
	sens.getI2C().setDataRate(10000);
	initialized = true;

	return config();
}

void Hitechnic_IRSeeker::deinit()
{
	if (!initialized)
		return;
	initialized = false;
}

Hitechnic_IRSeeker::EError Hitechnic_IRSeeker::config()
{

	uint8_t tx[2];
	tx[0] = DSP_MODE;
	tx[1] = DSP_1200;
	if(!sens.getI2C().write(1, tx, 2))
	    return ERROR_PROTO;
	return ERROR_OK;
}

Hitechnic_IRSeeker::EError Hitechnic_IRSeeker::read(data *pDataMsg)
{
	init();
	int32_t dcSigSum = 0;
	int32_t iMax = 0;
	uint8_t tx[1];
	tx[0] = OFFSET + DC_DIR;
	uint8_t retVal[13];
	if(!sens.getI2C().rw(I2C_ADDR,tx,1,retVal,13))
		return ERROR_PROTO;
	pDataMsg->dcDirection = retVal[0];
	for (int8_t i = 0; i < 5; i++)
	{
		pDataMsg->dcValues[i] = retVal[DC_SSTR1 + i];
	}
	pDataMsg->dcAvg = retVal[DC_SAVG];
	pDataMsg->acDirection = retVal[AC_DIR];

	for (int8_t i = 0; i < 5; i++)
	{
		pDataMsg->acValues[i] = retVal[AC_SSTR1 + i];
	}

	for (int8_t i = 0; i<5; i++)
	{
		if(pDataMsg->dcValues[i] > pDataMsg->dcValues[iMax])
			iMax = i;
	}

	pDataMsg->enhDirection = iMax * 2 + 1;

	dcSigSum = pDataMsg->dcValues[iMax] + pDataMsg->dcAvg;

	if((iMax > 0) && (pDataMsg->dcValues[iMax-1] > (pDataMsg->dcValues[iMax] /2)))
	{
		pDataMsg->enhDirection--;
		dcSigSum += pDataMsg->dcValues[iMax -1];
	}

	if ((iMax <4) && (pDataMsg->dcValues[iMax + 1] > (pDataMsg->dcValues[iMax] / 2)))
	{
		pDataMsg->enhDirection++;
		dcSigSum += pDataMsg->dcValues[iMax +1];
	}

	pDataMsg->enhStrength = sqrt(dcSigSum * 500);

	if((pDataMsg->enhStrength <= 200) && (pDataMsg->enhDirection > 0))
	{
		pDataMsg->enhStrength = pDataMsg->acValues[0] + pDataMsg->acValues[1]
		                           + pDataMsg->acValues[2] + pDataMsg->acValues[3]
		                           + pDataMsg->acValues[4];
	}

	return ERROR_OK;
}
