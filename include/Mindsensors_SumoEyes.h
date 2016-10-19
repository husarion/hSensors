#ifndef __MINDESNSORS_SUMOEYES_H__
#define __MINDESNSORS_SUMOEYES_H__


#include <hFramework.h>

namespace hSensors
{
/**
 * @brief Provides interface for Mindsensors Sumo Eyes sensor.
 */
class Mindsensors_SumoEyes
{
public:
	enum Zone {
		  NONE = 0,
		  FRONT = 1,
		  LEFT = 2,
		  RIGHT = 3 };
	/**
	 * @brief Create sensor object.
	 * @param sensor hSensor port (eg. hSens1, hSens2, hSens3)
	 */
	Mindsensors_SumoEyes(ILegoSensor& sensor);
	~Mindsensors_SumoEyes(); //!< Destory sensor object.

	void init(); //!< Initialize sensor.
	void deinit(); //!< Deinitialize sensor.

	/**
	 * @brief Read zone from the sensor
	 *
	 * @param pDataMsg pointer to the sensor's data struct
	 * @return zone NONE, FRONT, LEFT or RIGHT
	 */
	Zone readZone();

	/**
	 * @brief Configure the sensor to long range mode
	 *
	 */
	void setLongRange();

	/**
	 * @brief Configure the sensor to short range mode
	 *
	 */
	void setShortRange();

private:
	ILegoSensor &sensor;
	bool initialized;
};

}

#endif
