#include "hitechnic-gyro.h"

#define HTAC_I2C_ADDR  0x02      /*!< IR Seeker I2C device address */
#define HTAC_OFFSET    0x42      /*!< Offset for data registers */
#define HTAC_X_UP      0x00      /*!< X axis upper 8 bits */
#define HTAC_Y_UP      0x01      /*!< Y axis upper 8 bits */
#define HTAC_Z_UP      0x02      /*!< Z axis upper 8 bits */
#define HTAC_X_LOW     0x03      /*!< X axis lower 2 bits */
#define HTAC_Y_LOW     0x04      /*!< Y axis lower 2 bits */
#define HTAC_Z_LOW     0x05      /*!< Z axis lower 2 bits */

static void _init(tHitechnicSensor& link)
{
	link.sens.selectGPIO();
	link.sens.getPinIntAdc().enableADC();
	link.initialized = true;
	link.param1 = 1750.0f;
}

float HTGYROreadRot(tHitechnicSensor& link)
{
	if (!link.initialized) _init(link);
	return (float)link.sens.getPinIntAdc().analogReadRaw() - link.param1;
}
float HTGYROstartCal(tHitechnicSensor& link)
{
	if (!link.initialized) _init(link);
	long _avgdata = 0;
	
	for (int i = 0; i < 50; i++)
	{
		_avgdata += link.sens.getPinIntAdc().analogReadRaw();
		sys.delay_ms(5);
	}

	link.param1 = (float)_avgdata / 50.0f;

	return link.param1;
}
void HTGYROsetCal(tHitechnicSensor& link, int offset)
{
	link.param1 = offset;
}
float HTGYROreadCal(tHitechnicSensor& link)
{
	return link.param1;
}
