/**
 ******************************************************************************
 * \file    hitechnic-color-v2.h
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

#ifndef __HITECHNIC_COLOR_V2_H__
#define __HITECHNIC_COLOR_V2_H__

#include "hitechnic.h"

bool HTCS2init(tHitechnicSensor& link);
bool HTCS2deinit(tHitechnicSensor& link);
int HTCS2readColor(tHitechnicSensor& link);
bool HTCS2readRGB(tHitechnicSensor& link, int &red, int &green, int &blue);
bool HTCS2readHSV(tHitechnicSensor& link, float &hue, float &saturation, float &value);
bool HTCS2readWhite(tHitechnicSensor& link, int &white);
bool HTCS2readNormRGB(tHitechnicSensor& link, int &red, int &green, int &blue);
bool HTCS2readRawRGB(tHitechnicSensor& link, bool passive, long &red, long &green, long &blue);
bool HTCS2readRawWhite(tHitechnicSensor& link, bool passive, long &white);
int HTCS2readColorIndex(tHitechnicSensor& link);
bool _HTCSsendCommand(tHitechnicSensor& link, uint8_t command);

#endif
