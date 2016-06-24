#include "Mindsensors_Pressure.h"

#include <hFramework.h>
#define MSPPS_I2C_ADDR       0x01  /*!< MSPPS I2C device address */

#define MSPPS_CMD            0x41  /*!< MSPPS command register */

#define MSPPS_UNIT           0x42  /*!< Configure measurement unit */
#define MSPPS_PRESS_ABS      0x43  /*!< Read the absolute pressure */
#define MSPPS_PRESS_GAUGE    0x45  /*!< Read the gauge pressure */
#define MSPPS_PRESS_REF      0x47  /*!< Read or write the reference pressure */

#define MSPPS_UNIT_PSI       0x50   /*!< PSI unit */
#define MSPPS_UNIT_MB        0x62   /*!< Millibar unit */
#define MSPPS_UNIT_KPA       0x6B   /*!< Kilo Pascal unit */

#define MSPSS_CMD_SETREF     0x44    /*!< Set reference pressure to current absolute pressure */

using namespace hSensors;

Mindsensors_Pressure::Mindsensors_Pressure(ILegoSensor_i2c& sensor) : sens(sensor), initialized(false)
{
}
Mindsensors_Pressure::~Mindsensors_Pressure()
{
	deinit();
}

void Mindsensors_Pressure::init()
{
	if (initialized)
		return;
	sens.getPinIntAdc().enableADC();
	initialized = true;

}
void Mindsensors_Pressure::deinit()
{
	if (!initialized)
		return;
	initialized = false;
}

Mindsensors_Pressure::EError Mindsensors_Pressure::read(float &v)
{
	init();
	uint16_t k = sens.getPinIntAdc().analogReadRaw();
	float f1 = 0.04;
	float f2 = 0.00369;
	float Press_mult = (1.0/(f2 * 1023));
	float Offset = (f1 / f2);

	v = k*Press_mult - Offset;
	return ERROR_OK;

}

