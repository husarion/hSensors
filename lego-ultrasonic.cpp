#include "lego-ultrasonic.h"

#define LEGOUS_I2C_ADDR    0x02      /*!< Lego US I2C address */
#define LEGOUS_REG_CMD     0x41      /*!< Command register */
#define LEGOUS_REG_DATA    0x42      /*!< Start of measurement data registers */

#define LEGOUS_CMD_OFF     0x00      /*!< Command to switch US off */
#define LEGOUS_CMD_SSHOT   0x01      /*!< Command to turn on Single Shot mode */
#define LEGOUS_CMD_CONT    0x02      /*!< Command to turn on Continuous Mode */
#define LEGOUS_CMD_ECAPT   0x03      /*!< Command to turn on Event Capture Mode */
#define LEGOUS_CMD_RST     0x04      /*!< Command to request a warm reset */

void USinit(ISensor_i2c& link)
{
	link.currentSourceOn(1);
	link.selectI2C();
}
void USdeinit(ISensor_i2c& link)
{
	link.currentSourceOn(0);
	link.selectGPIO();
}
int USreadDist(ISensor_i2c& link)
{
	uint8_t tx[1], rx[1];
	tx[0] = LEGOUS_REG_DATA;
	if (!link.getI2C().read(1, tx, 1, rx, 1))
		return -1;
		
	return rx[0];
}
bool USreadDistances(ISensor_i2c& link, uint8_t distances[8])
{
	uint8_t tx[1];
	tx[0] = LEGOUS_REG_DATA;
	return link.getI2C().read(1, tx, 1, distances, 8);
}
bool _USsendCmd(ISensor_i2c& link, uint8_t command)
{
	uint8_t tx[2];
	tx[0] = LEGOUS_REG_CMD;
	tx[1] = command;
	return link.getI2C().write(1, tx, 2);
}
bool USsetSingleMode(ISensor_i2c& link)
{
	return _USsendCmd(link, LEGOUS_CMD_SSHOT);
}
bool USsetContinuousMode(ISensor_i2c& link)
{
	return _USsendCmd(link, LEGOUS_CMD_CONT);
}
bool USsetOff(ISensor_i2c& link)
{
	return _USsendCmd(link, LEGOUS_CMD_OFF);
}
bool USsetEventCapture(ISensor_i2c& link)
{
	return _USsendCmd(link, LEGOUS_CMD_ECAPT);
}
bool USreset(ISensor_i2c& link)
{
	return _USsendCmd(link, LEGOUS_CMD_RST);
}
