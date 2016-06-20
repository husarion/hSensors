#ifndef __MINDSENSORS_PRESSURE_H__
#define __MINDSENSORS_PRESSURE_H__

#include <hFramework.h>

namespace hSensors {


/**
 * @brief Provides interface for Mindsensors Pressure sensor.
 */
class Mindsensors_Pressure {
public:
	enum EError { ERROR_OK, ERROR_PROTO };


	/**
	 * @brief Create sensor object.
	 *
	 * @param sensor - I2C capable hSensor port (eg. hSens1, hSens2) or software I2C
	 * implementation (eg. \c hSens3.getSoftwareI2C(), \c hSens4.getSoftwareI2C())
	 */
	Mindsensors_Pressure(ILegoSensor_i2c& sensor);
	~Mindsensors_Pressure(); //!< Destory sensor object.

	void init(); //!< Initialize sensor.
	void deinit(); //!< Deinitialize sensor.

	EError read(float &v);



private:

	ILegoSensor_i2c &sens;
	bool initialized;
};

}

#endif
