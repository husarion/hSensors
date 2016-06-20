#ifndef __HITECHNIC_IRSEEKER_H__
#define __HITECHNIC_IRSEEKER_H__

#include <hFramework.h>

namespace hSensors {


/**
 * @brief Provides interface for Hitechnic Infrared Seeker sensor.
 */
class Hitechnic_IRSeeker {
public:
	enum EError { ERROR_OK, ERROR_PROTO };
	/**
	 * @brief Sensor's data struct
	 */
	typedef struct
	{
		uint32_t dcDirection;	//!< Direction of the strongest DC signal.
		uint32_t acDirection;	//!< Direction of the strongest AC signal.
		uint32_t enhStrength;	//!< Signal strength.
		uint32_t enhDirection;	//!< Direction of the strongest signal.
		uint32_t acValues[5];	//!< AC signal value from all five sensors.
		uint32_t dcValues[5];	//!< DC signal value from all five sensors.
		uint32_t dcAvg;			//!< Average of dc signal value.
	} data;

	/**
	 * @brief Create sensor object.
	 *
	 * @param sensor - I2C capable hSensor port (eg. hSens1, hSens2) or software I2C
	 * implementation (eg. \c hSens3.getSoftwareI2C(), \c hSens4.getSoftwareI2C())
	 */
	Hitechnic_IRSeeker(ILegoSensor_i2c& sensor);
	~Hitechnic_IRSeeker(); //!< Destory sensor object.

	EError init(); //!< Initialize sensor.
	void deinit(); //!< Deinitialize sensor.


	/**
	 * @brief Read all the sensor's data
	 *
	 * @param pDataMsg - pointer to the sensor's data struct
	 * @return error code
	 */
	EError read(data *pDataMsg);

private:

	EError config();
	ILegoSensor_i2c &sens;
	bool initialized;
};

}

#endif
