/**
 ******************************************************************************
 * \file    Lego_Sound.h
 * \author  Husarion team
 * \version V0.9
 * \date    2-June-2014
 * \brief   Provides interface for Lego Sound sensor.
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

#ifndef __LEGO_SOUND_H__
#define __LEGO_SOUND_H__

#include <hFramework.h>

namespace hSensors
{
/**
 * @brief Provides interface for Lego Sound sensor.
 */
class Lego_Sound
{
public:
	enum EError { ERROR_OK, ERROR_PROTO };

	/**
	 * @brief Create sensor object.
	 * @param sensor - hSensor port (eg. hSens1, hSens2, hSens3)
	 */
	Lego_Sound(ILegoSensor& sensor);
	~Lego_Sound(); //!< Destory sensor object.

	void init(); //!< Initialize sensor.
	void deinit(); //!< Deinitialize sensor.

	int readRaw();
	int readNorm();
	void setDBA();
	void setDB();

private:
	ILegoSensor &sens;
	bool initialized;
};

}

#endif

