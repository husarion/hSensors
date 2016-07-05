#include "Lego_Ultrasonic.h"

#include <hFramework.h>

#define SENSOR_ADDRESS 0x01

#define LEGOUS_REG_CMD     0x41      /*!< Command register */
#define LEGOUS_REG_DATA    0x42      /*!< Start of measurement data registers */

#define LEGOUS_CMD_OFF     0x00      /*!< Command to switch US off */
#define LEGOUS_CMD_SSHOT   0x01      /*!< Command to turn on Single Shot mode */
#define LEGOUS_CMD_CONT    0x02      /*!< Command to turn on Continuous Mode */
#define LEGOUS_CMD_ECAPT   0x03      /*!< Command to turn on Event Capture Mode */
#define LEGOUS_CMD_RST     0x04      /*!< Command to request a warm reset */

using namespace hSensors;

Lego_Ultrasonic::Lego_Ultrasonic(ILegoSensor_i2c& sensor) : sens(sensor), initialized(false)
{
}
Lego_Ultrasonic::~Lego_Ultrasonic()
{
	deinit();
}

void Lego_Ultrasonic::init()
{
	if (initialized)
		return;
	sens.currentSourceOn(1);
	sens.selectI2C();
	sens.getI2C().setDataRate(10000);
	initialized = true;
}
void Lego_Ultrasonic::deinit()
{
	if (!initialized)
		return;
	sens.currentSourceOn(0);
	initialized = false;
}

int Lego_Ultrasonic::readDist()
{
	init();
	uint8_t tx[1], rx[1];
	tx[0] = LEGOUS_REG_DATA;
	if (!sens.getI2C().read(1, tx, 1, rx, 1))
		return -1;

	return rx[0];
}
bool Lego_Ultrasonic::readDistances(uint8_t distances[8])
{
	init();
	uint8_t tx[1];
	tx[0] = LEGOUS_REG_DATA;
	return sens.getI2C().read(1, tx, 1, distances, 8);
}
bool Lego_Ultrasonic::setSingleMode()
{
	init();
	return sendCmd(LEGOUS_CMD_SSHOT);
}
bool Lego_Ultrasonic::setContinuousMode()
{
	init();
	return sendCmd(LEGOUS_CMD_CONT);
}
bool Lego_Ultrasonic::setOff()
{
	init();
	return sendCmd(LEGOUS_CMD_OFF);
}
bool Lego_Ultrasonic::setEventCapture()
{
	init();
	return sendCmd(LEGOUS_CMD_ECAPT);
}
bool Lego_Ultrasonic::reset()
{
	init();
	return sendCmd(LEGOUS_CMD_RST);
}

bool Lego_Ultrasonic::sendCmd(uint8_t command)
{
	init();
	uint8_t tx[2];
	tx[0] = LEGOUS_REG_CMD;
	tx[1] = command;
	return sens.getI2C().write(1, tx, 2);
}
