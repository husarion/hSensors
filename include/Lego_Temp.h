#ifndef __LEGO_TEMP_H__
#define __LEGO_TEMP_H__

#include <hFramework.h>
namespace hSensors
{
/**
 * @brief Provides interface for LineLeader sensor.
 */
class Lego_Temp
{
public:
	enum EError { ERROR_OK, ERROR_PROTO };
	enum Accuracy {
		  A_MIN   = 8, // !<0.5,   * 16
		  A_MEAN1 = 4, // !<0.25   * 16
		  A_MEAN2 = 2, // !<0.125  * 16
		  A_MAX   = 1  // !<0.0625 * 16
	};

	/**
	 * @brief Create sensor object.
	 * @param sensor - I2C capable hSensor port (eg. hSens1, hSens2) or software I2C
	 * implementation (eg. \c hSens3.getSoftwareI2C(), \c hSens4.getSoftwareI2C())
	 */
	Lego_Temp(ILegoSensor_i2c& sensor);
	~Lego_Temp(); //!< Destory sensor object.

	EError init(); //!< Initialize sensor.
	void deinit(); //!< Deinitialize sensor.

	/**
	 * @brief Read the temperature.
	 *
	 * @param v the temperature value,
	 * @return error code
	 */
	EError readTemp(float &v);

	/**
	 * @brief Read the temperature sensor's accuracy
	 *
	 * @param v the accuracy value to be read
	 * @return error code
	 */
	EError readAccuracy(Accuracy &v);

	/**
	 * @brief Set the temperature sensor's accuracy
	 *
	 * @param v the accuracy value to be set
	 * @return error code
	 */
	EError setAccuracy(Accuracy v);

	/**
	 * @brief Configure the sensor for Single Shot mode
	 *
	 * @return error code
	 */
	EError setSingleShot();

	/**
	 * @brief Configure the sensor for Continuous mode
	 *
	 * @return error code
	 */
	EError setContinuous();
private:

	ILegoSensor_i2c &sens;
	bool initialized;

	/**
	 * @brief Retrieve the accuracy level from the config bytes
	 *
	 * @param conf the contents of the register
	 * @return error code
	 */
	Accuracy convertAccuracy(uint8_t conf);

	/**
	 * @brief Read the current configuration register
	 *
	 * @param conf the contents of the register
	 * @return error code
	 */
	EError readConfig(uint8_t &conf);

	/**
	 * @brief Set the configuration register
	 *
	 * @param conf the contents of the register
	 * @return error code
	 */
	EError setConfig(uint8_t conf);
};

}

#endif
