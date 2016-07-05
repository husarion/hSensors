/**
 ******************************************************************************
 * \file    Lego_Ultrasonic.h
 * \author  Husarion team
 * \version V0.9
 * \date    2-June-2014
 * \brief   Provides interface for Lego Ultrasonic sensor.
 ******************************************************************************
 * \details This file is part of robocore-sensors library.
 *
 * \copyright Copyright (C) 2014 Husarion Sp. z o.o. <husarion.com> - All Rights Reserved.
 * Unauthorized copying of this file and the robocore-sensors library,
 * via any medium is strictly prohibited. Proprietary and confidential.
 *
 * \attention
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
 * PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
 * OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 ******************************************************************************
 */

#ifndef __LEGO_ULTRASONIC_H__
#define __LEGO_ULTRASONIC_H__

#include <hFramework.h>

namespace hSensors
{
/**
 * @brief Provides interface for Lego Ultrasonic sensor.
 */
class Lego_Ultrasonic
{
public:
	enum EError { ERROR_OK, ERROR_PROTO };

	/**
	 * @brief Create sensor object.
	 * @param sensor - I2C capable hSensor port (eg. hSens1, hSens2) or software I2C
	 * implementation (eg. \c hSens3.getSoftwareI2C(), \c hSens4.getSoftwareI2C())
	 */
	Lego_Ultrasonic(ILegoSensor_i2c& sensor);
	~Lego_Ultrasonic(); //!< Destory sensor object.

	void init(); //!< Initialize sensor.
	void deinit(); //!< Deinitialize sensor.

	int readDist(); //!< Read distance from sensor.
	bool readDistances(uint8_t distances[8]); //!< Read last 8 distances from sensor.
	bool setSingleMode();
	bool setContinuousMode();
	bool setOff(); //!< Turn the sensor off.
	bool setEventCapture();
	bool reset(); //!< Reset the sensor.

private:
	ILegoSensor_i2c &sens;
	bool initialized;

	bool sendCmd(uint8_t command);
};

}

#endif
