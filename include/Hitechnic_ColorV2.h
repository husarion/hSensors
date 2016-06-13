/**
 ******************************************************************************
 * \file    Hitechnic_ColorV2.h
 * \author  Husarion team
 * \version V0.9
 * \date    2-June-2014
 * \brief   Provides interface for Hitechnic Color V2 sensor.
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

#ifndef __HITECHNIC_COLORV2_H__
#define __HITECHNIC_COLORV2_H__

#include <hFramework.h>

namespace hSensors
{
/**
 * @brief Provides interface for Hitechnic Color V2 sensor.
 */
class Hitechnic_ColorV2
{
public:
	enum EError { ERROR_OK, ERROR_PROTO };

	/**
	 * @brief Create sensor object.
	 * @param sensor - I2C capable hSensor port (eg. hSens1, hSens2) or software I2C
	 * implementation (eg. hSens3.getSoftwareI2C(), hSens4.getSoftwareI2C())
	 */
	Hitechnic_ColorV2(ILegoSensor_i2c& sensor);
	~Hitechnic_ColorV2(); //!< Destory sensor object.

	void init(); //!< Initialize sensor.
	void deinit(); //!< Deinitialize sensor.

	int readColor();
	bool readRGB(uint8_t &red, uint8_t &green, uint8_t &blue); //!< Read color as RGB.
	bool readHSV(float &hue, float &saturation, float &value); //!< Read color as HSV.
	bool readWhite(int &white); //!< Read grayscale.
	bool readNormRGB(int &red, int &green, int &blue);
	bool readRawRGB(bool passive, long &red, long &green, long &blue);
	bool readRawWhite(bool passive, long &white);
	int readColorIndex();

private:
	ILegoSensor_i2c &sens;
	bool initialized;
	int mode;

	bool sendCommand(uint8_t command);
};

}

#endif
