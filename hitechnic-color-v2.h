#ifndef __HITECHNIC_COLOR_V2_H__
#define __HITECHNIC_COLOR_V2_H__

#include "hitechnic.h"

int HTCS2init(tHitechnicSensor& link);
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
