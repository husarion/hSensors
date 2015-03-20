/**
 ******************************************************************************
 * \file    lego-ultrasonic.h
 * \author  Husarion team
 * \version V0.9
 * \date    2-June-2014
 * \brief   Provides interface for Lego Touch sensor.
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

void USinit(ISensor_i2c& link);
void USdeinit(ISensor_i2c& link);
int USreadDist(ISensor_i2c& link);
bool USreadDistances(ISensor_i2c& link, uint8_t distances[8]);
bool _USsendCmd(ISensor_i2c& link, uint8_t command);
bool USsetSingleMode(ISensor_i2c& link);
bool USsetContinuousMode(ISensor_i2c& link);
bool USsetOff(ISensor_i2c& link);
bool USsetEventCapture(ISensor_i2c& link);
bool USreset(ISensor_i2c& link);

#endif
