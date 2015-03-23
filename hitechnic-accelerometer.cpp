#include "hitechnic-accelerometer.h"

#define HTAC_I2C_ADDR  0x02      /*!< IR Seeker I2C device address */
#define HTAC_OFFSET    0x42      /*!< Offset for data registers */
#define HTAC_X_UP      0x00      /*!< X axis upper 8 bits */
#define HTAC_Y_UP      0x01      /*!< Y axis upper 8 bits */
#define HTAC_Z_UP      0x02      /*!< Z axis upper 8 bits */
#define HTAC_X_LOW     0x03      /*!< X axis lower 2 bits */
#define HTAC_Y_LOW     0x04      /*!< Y axis lower 2 bits */
#define HTAC_Z_LOW     0x05      /*!< Z axis lower 2 bits */

bool HTACinit(tHitechnicSensor& link)
{
	link.sens.selectI2C();
	return true;
}
bool HTACdeinit(tHitechnicSensor& link)
{
	return true;
}
bool HTACreadAllAxes(tHitechnicSensor& link, int &x, int &y, int &z)
{
	uint8_t tx[1], rx[6];
	tx[0] = HTAC_OFFSET + HTAC_X_UP;
	if (!link.sens.getI2C().read(1, tx, 1, rx, 6))
		return false;
		
	x = ((int16_t)(rx[0] << 8) >> 6) | (rx[3] & 0x03);
	y = ((int16_t)(rx[1] << 8) >> 6) | (rx[4] & 0x03);
	z = ((int16_t)(rx[2] << 8) >> 6) | (rx[5] & 0x03);
	
	return true;
}
