/*
 * Copyright (C) 2015 Krystian Dużyński <krystian.duzynski@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */

#ifndef __HITECHNIC_ACCELEROMETER_H__
#define __HITECHNIC_ACCELEROMETER_H__

#include "hitechnic.h"

bool HTACinit(tHitechnicSensor& link);
bool HTACdeinit(tHitechnicSensor& link);
bool HTACreadAllAxes(tHitechnicSensor& link, int &x, int &y, int &z);

#endif
