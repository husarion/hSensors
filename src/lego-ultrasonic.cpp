#include "lego-ultrasonic.h"

#define LEGOUS_I2C_ADDR    0x02      /*!< Lego US I2C address */
#define LEGOUS_REG_CMD     0x41      /*!< Command register */
#define LEGOUS_REG_DATA    0x42      /*!< Start of measurement data registers */

#define LEGOUS_CMD_OFF     0x00      /*!< Command to switch US off */
#define LEGOUS_CMD_SSHOT   0x01      /*!< Command to turn on Single Shot mode */
#define LEGOUS_CMD_CONT    0x02      /*!< Command to turn on Continuous Mode */
#define LEGOUS_CMD_ECAPT   0x03      /*!< Command to turn on Event Capture Mode */
#define LEGOUS_CMD_RST     0x04      /*!< Command to request a warm reset */

static void _init(tLegoSensor_i2c& link)
{
	link.sens.currentSourceOn(1);
	link.sens.selectI2C();
	link.initialized = true;
}
int USreadDist(tLegoSensor_i2c& link)
{
	if (!link.initialized) _init(link);
	uint8_t tx[1], rx[1];
	tx[0] = LEGOUS_REG_DATA;
	if (!link.sens.getI2C().read(1, tx, 1, rx, 1))
		return -1;
		
	return rx[0];
}
bool USreadDistances(tLegoSensor_i2c& link, uint8_t distances[8])
{
	if (!link.initialized) _init(link);
	uint8_t tx[1];
	tx[0] = LEGOUS_REG_DATA;
	return link.sens.getI2C().read(1, tx, 1, distances, 8);
}
bool _USsendCmd(tLegoSensor_i2c& link, uint8_t command)
{
	if (!link.initialized) _init(link);
	uint8_t tx[2];
	tx[0] = LEGOUS_REG_CMD;
	tx[1] = command;
	return link.sens.getI2C().write(1, tx, 2);
}
bool USsetSingleMode(tLegoSensor_i2c& link)
{
	if (!link.initialized) _init(link);
	return _USsendCmd(link, LEGOUS_CMD_SSHOT);
}
bool USsetContinuousMode(tLegoSensor_i2c& link)
{
	if (!link.initialized) _init(link);
	return _USsendCmd(link, LEGOUS_CMD_CONT);
}
bool USsetOff(tLegoSensor_i2c& link)
{
	if (!link.initialized) _init(link);
	return _USsendCmd(link, LEGOUS_CMD_OFF);
}
bool USsetEventCapture(tLegoSensor_i2c& link)
{
	if (!link.initialized) _init(link);
	return _USsendCmd(link, LEGOUS_CMD_ECAPT);
}
bool USreset(tLegoSensor_i2c& link)
{
	if (!link.initialized) _init(link);
	return _USsendCmd(link, LEGOUS_CMD_RST);
}
