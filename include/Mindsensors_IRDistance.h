#ifndef __MINDSENSOR_IRDISTANCE_H__
#define __MINDSENSOR_IRDISTANCE_H__

#include <hFramework.h>

namespace hSensors
{
/**
 * @brief Provides interface for LineLeader sensor.
 */
class Mindsensors_IRDistance
{
public:
	enum EError { ERROR_OK, ERROR_PROTO };

	/**
	 * @brief Create sensor object.
	 * @param sensor - I2C capable hSensor port (eg. hSens1, hSens2) or software I2C
	 * implementation (eg. \c hSens3.getSoftwareI2C(), \c hSens4.getSoftwareI2C())
	 */
	Mindsensors_IRDistance(ILegoSensor_i2c& sensor);
	~Mindsensors_IRDistance(); //!< Destory sensor object.

	EError init(); //!< Initialize sensor.
	void deinit(); //!< Deinitialize sensor.

	/**
	 * @brief Read the distance
	 *
	 * Read the distance from the sensor in mm.
	 * @param v - returned value
	 * @return error code
	 */
	EError readReal(int16_t &v);

	/**
	 * @brief Read the Voltage value
	 *
	 * Read the voltage value from the sensor.
	 * @param v - returned value
	 * @return error code
	 */
	EError readVoltage(int16_t &v);
private:

	ILegoSensor_i2c &sens;
	bool initialized;
};

}

#endif
