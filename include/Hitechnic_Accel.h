/**
 ******************************************************************************
 * \file    Hitechnic_Accel.h
 * \author  Husarion team
 * \version V0.9
 * \date    2-June-2014
 * \brief   Provides interface for Hitechnic Accelerometer sensor.
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

#ifndef __HITECHNIC_ACCEL_H__
#define __HITECHNIC_ACCEL_H__

#include <hFramework.h>

/**
 * @brief hSensors
 */
namespace hSensors {
/**
 * @brief Provides interface for Hitechnic Accelerometer sensor.
 */
class Hitechnic_Accel
{
public:
	enum EError { ERROR_OK, ERROR_PROTO };

	/**
	 * @brief Create sensor object.
	 * @param sensor - I2C capable hSensor port (eg. hSens1, hSens2) or software I2C
	 * implementation (eg. \c hSens3.getSoftwareI2C(), \c hSens4.getSoftwareI2C())
	 */
	Hitechnic_Accel(ILegoSensor_i2c& sensor);
	~Hitechnic_Accel(); //!< Destory sensor object.

	void init(); //!< Initialize sensor.
	void deinit(); //!< Deinitialize sensor.

	/**
	 * @brief Read raw acceleration data.
	 * @param x x axis
	 * @param y y axis
	 * @param z z axis
	 * @return error code
	 */
	EError readRaw(int16_t& x, int16_t& y, int16_t& z);

	/**
	 * @brief Read acceleration data.
	 * @param x x axis in g
	 * @param y y axis in g
	 * @param z z axis in g
	 * @return error code
	 */
	EError read(float& x, float& y, float& z);

private:
	ILegoSensor_i2c &sens;
	bool initialized;
};

}

#endif
