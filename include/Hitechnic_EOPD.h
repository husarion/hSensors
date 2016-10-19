#ifndef __HITECHNIC_EOPD_H__
#define __HITECHNIC_EOPD_H__

#include <hFramework.h>

namespace hSensors
{
/**
 * @brief Provides interface for LineLeader sensor.
 */
class Hitechnic_EOPD
{
public:
	enum EError { ERROR_OK, ERROR_PROTO };
	typedef struct
	{
		uint32_t raw;
		uint16_t processed;
	} data;
	/**
	 * @brief Create sensor object.
	 * @param sensor - I2C capable hSensor port (eg. hSens1, hSens2) or software I2C
	 * implementation (eg. \c hSens3.getSoftwareI2C(), \c hSens4.getSoftwareI2C())
	 */
	Hitechnic_EOPD(ILegoSensor_i2c& sensor);
	~Hitechnic_EOPD(); //!< Destory sensor object.

	void init(); //!< Initialize sensor.
	void deinit(); //!< Deinitialize sensor.

	/**
	 * @brief Read all the sensor's data
	 *
	 * @param pDataMsg pointer to the sensor's data struct
	 * @return error code
	 */
	EError read(data *pDataMsg);

	/**
	 * @brief Configure the sensor to long range mode
	 *
	 */
	void setModeLong();
	/**
	 * @brief Configure the sensor to short range mode
	 *
	 */
	void setModeShort();
private:

	ILegoSensor_i2c &sens;
	bool initialized;
};

}

#endif
