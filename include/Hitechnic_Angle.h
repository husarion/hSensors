#ifndef __HITECHNIC_ANGLE_H__
#define __HITECHNIC_ANGLE_H__

#include <hFramework.h>

namespace hSensors
{
/**
 * @brief Provides interface for LineLeader sensor.
 */
class Hitechnic_Angle
{
public:
	enum EError { ERROR_OK, ERROR_PROTO };

	typedef struct
	{
		uint16_t Angle;	//!< Angle, expected values 0-359
		int32_t AccumulatedAngle;	//!< Accumulated Angle
		int16_t rpm; //!< velocity in revolution per minute
	} data;

	/**
	 * @brief Create sensor object.
	 * @param sensor - I2C capable hSensor port (eg. hSens1, hSens2) or software I2C
	 * implementation (eg. \c hSens3.getSoftwareI2C(), \c hSens4.getSoftwareI2C())
	 */
	Hitechnic_Angle(ILegoSensor_i2c& sensor);
	~Hitechnic_Angle(); //!< Destory sensor object.

	EError init(); //!< Initialize sensor.
	void deinit(); //!< Deinitialize sensor.
	/**
	 * @brief Read all the sensor's data
	 *
	 * @param pTab - pointer to the sensor's data struct
	 * @return error code
	 */
	EError read(data *pTab);
	/**
	 * @brief Reset the AccumulatedAngle value
	 *
	 * @return error code
	 */
	EError resetAccmulatedAngle();

	/**
	 * @brief Reset the Angle value
	 *
	 * @return error code
	 */
	EError resetAngle();

private:



	/**
	 * @brief Send a command to the sensor
	 *
	 * @param cmd command to send to the sensor
	 * @return error code
	 */
	EError sendCmd(uint8_t cmd);

	ILegoSensor_i2c &sens;
	bool initialized;
};

}

#endif
