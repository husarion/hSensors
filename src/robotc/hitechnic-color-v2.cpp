#include "hitechnic-color-v2.h"

#define HTCS2_CMD_REG         0x41      /*!< Command register */
#define HTCS2_I2C_ADDR        0x02      /*!< HTCS2 I2C device address */
#define HTCS2_OFFSET          0x42      /*!< Offset for data registers */

// Values contained by registers in active mode
#define HTCS2_COLNUM_REG      0x00      /*!< Color number */
#define HTCS2_RED_REG         0x01      /*!< Red reading */
#define HTCS2_GREEN_REG       0x02      /*!< Green reading */
#define HTCS2_BLUE_REG        0x03      /*!< Blue reading */
#define HTCS2_WHITE_REG       0x04      /*!< White channel reading */
#define HTCS2_COL_INDEX_REG   0x05      /*!< Color index number */
#define HTCS2_RED_NORM_REG    0x06      /*!< Normalised red reading */
#define HTCS2_GREEN_NORM_REG  0x07      /*!< Normalised green reading */
#define HTCS2_BLUE_NORM_REG   0x08      /*!< Normalised blue reading */

// Values contained by registers in passive and raw mode
#define HTCS2_RED_MSB         0x00      /*!< Raw red reading - MSB */
#define HTCS2_RED_LSB         0x00      /*!< Raw red reading - LSB */
#define HTCS2_GREEN_MSB       0x00      /*!< Raw green reading - MSB */
#define HTCS2_GREEN_LSB       0x00      /*!< Raw green reading - LSB */
#define HTCS2_BLUE_MSB        0x00      /*!< Raw blue reading - MSB */
#define HTCS2_BLUE_LSB        0x00      /*!< Raw blue reading - LSB */
#define HTCS2_WHITE_MSB       0x00      /*!< Raw white channel reading - MSB */
#define HTCS2_WHITE_LSB       0x00      /*!< Raw white channel reading - LSB */

// Different modes
#define HTCS2_MODE_ACTIVE     0x00      /*!< Use ambient light cancellation */
#define HTCS2_MODE_PASSIVE    0x01      /*!< Disable ambient light cancellation */
#define HTCS2_MODE_RAW        0x03      /*!< Raw data from light sensor */
#define HTCS2_MODE_50HZ       0x35      /*!< Set sensor to 50Hz cancellation mode */
#define HTCS2_MODE_60HZ       0x36      /*!< Set sensor to 60Hz cancellation mode */

#define max3(a, b, c) (a > b) ? ((a > c) ? a : c) : ((b > c) ? b : c)
#define min3(a, b, c) (a < b) ? ((a < c) ? a : c) : ((b < c) ? b : c)

static void RGBtoHSV(float red, float green, float blue, float &hue, float &sat, float &value);

static void _init(tHitechnicSensor& link)
{
	link.sens.selectI2C();
	link.mode = -1;
	link.initialized = true;
}

int HTCS2readColor(tHitechnicSensor& link)
{
	if (!link.initialized) _init(link);
	if (link.mode != HTCS2_MODE_ACTIVE)
		_HTCSsendCommand(link, HTCS2_MODE_ACTIVE);
		
	uint8_t tx[1], rx[3];
	tx[0] = HTCS2_OFFSET + HTCS2_COLNUM_REG;
	if (!link.sens.getI2C().read(1, tx, 1, rx, 1))
		return 0;
		
	return rx[0];
}
bool HTCS2readRGB(tHitechnicSensor& link, int &red, int &green, int &blue)
{
	if (!link.initialized) _init(link);
	if (link.mode != HTCS2_MODE_ACTIVE)
		_HTCSsendCommand(link, HTCS2_MODE_ACTIVE);

	uint8_t tx[1], rx[3];
	tx[0] = HTCS2_OFFSET + HTCS2_RED_REG;
	if (!link.sens.getI2C().read(1, tx, 1, rx, 3))
		return false;
		
	red = rx[0];
	green = rx[1];
	blue = rx[2];
	
	return true;
}
bool HTCS2readHSV(tHitechnicSensor& link, float &hue, float &saturation, float &value)
{
	int red, green, blue;
	
	bool ret = HTCS2readRGB(link, red, green, blue);
	RGBtoHSV(red, green, blue, hue, saturation, value);
	
	return ret;
}
bool HTCS2readWhite(tHitechnicSensor& link, int &white)
{
	if (!link.initialized) _init(link);
	if (link.mode != HTCS2_MODE_ACTIVE)
		_HTCSsendCommand(link, HTCS2_MODE_ACTIVE);

	uint8_t tx[1], rx[1];
	tx[0] = HTCS2_OFFSET + HTCS2_WHITE_REG;
	if (!link.sens.getI2C().read(1, tx, 1, rx, 1))
		return false;
		
	white = rx[0];
	
	return true;
}
bool HTCS2readNormRGB(tHitechnicSensor& link, int &red, int &green, int &blue)
{
	if (!link.initialized) _init(link);
	uint8_t tx[1], rx[3];
	tx[0] = HTCS2_OFFSET + HTCS2_RED_NORM_REG;
	if (!link.sens.getI2C().read(1, tx, 1, rx, 3))
		return false;
		
	red = rx[0];
	green = rx[1];
	blue = rx[2];
	
	return true;
}
bool HTCS2readRawRGB(tHitechnicSensor& link, bool passive, long &red, long &green, long &blue)
{
	if (!link.initialized) _init(link);
	if (passive && (link.mode != HTCS2_MODE_PASSIVE))
		_HTCSsendCommand(link, HTCS2_MODE_PASSIVE);
	if (!passive && (link.mode != HTCS2_MODE_RAW))
		_HTCSsendCommand(link, HTCS2_MODE_RAW);

	uint8_t tx[1], rx[8];
	tx[0] = HTCS2_OFFSET + HTCS2_RED_MSB;
	if (!link.sens.getI2C().read(1, tx, 1, rx, 8))
		return false;
		
  red =   (long)rx[0] * 256 + rx[1];
  green = (long)rx[2] * 256 + rx[3];
  blue =  (long)rx[4] * 256 + rx[5];
	
	return true;
}
bool HTCS2readRawWhite(tHitechnicSensor& link, bool passive, long &white)
{
	if (!link.initialized) _init(link);
	if (passive && (link.mode != HTCS2_MODE_PASSIVE))
		_HTCSsendCommand(link, HTCS2_MODE_PASSIVE);
	if (!passive && (link.mode != HTCS2_MODE_RAW))
		_HTCSsendCommand(link, HTCS2_MODE_RAW);

	uint8_t tx[1], rx[2];
	tx[0] = HTCS2_OFFSET + HTCS2_WHITE_MSB;
	if (!link.sens.getI2C().read(1, tx, 1, rx, 2))
		return false;
		
  white = (long)rx[0] * 256 + rx[1];
	
	return true;
}
int HTCS2readColorIndex(tHitechnicSensor& link)
{
	if (!link.initialized) _init(link);
	if (link.mode != HTCS2_MODE_ACTIVE)
		_HTCSsendCommand(link, HTCS2_MODE_ACTIVE);

	uint8_t tx[1], rx[1];
	tx[0] = HTCS2_OFFSET + HTCS2_COL_INDEX_REG;
	if (!link.sens.getI2C().read(1, tx, 1, rx, 1))
		return false;
		
	return rx[0];
}

bool _HTCSsendCommand(tHitechnicSensor& link, uint8_t command)
{
	uint8_t tx[2];
	tx[0] = HTCS2_CMD_REG;
	tx[1] = command;

	if (command < 30)
		link.mode = command;

	return link.sens.getI2C().write(1, tx, 2);
}


static void RGBtoHSV(float red, float green, float blue, float &hue, float &sat, float &value)
{
	hue = 0;
	sat = 0;
	value = 0;
	
	// Value
	float rgb_max = max3(red, green, blue);
	float rgb_min;
	value = rgb_max / 2.56;
	if (value == 0)
	{
		hue = -1;
		sat = -1;
		return;
	}
	
	// Saturation
	red /= rgb_max;
	green /= rgb_max;
	blue /= rgb_max;
	
	rgb_max = max3(red, green, blue);
	rgb_min = min3(red, green, blue);
	sat = (rgb_max - rgb_min) * 100;
	if (sat == 0)
	{
		hue = -1;
		return;
	}
	
	// Hue
	red = (red - rgb_min) / (rgb_max - rgb_min);
	green = (green - rgb_min) / (rgb_max - rgb_min);
	blue = (blue - rgb_min) / (rgb_max - rgb_min);
	
	rgb_max = max3(red, green, blue);
	rgb_min = min3(red, green, blue);
	
	if (rgb_max == red)
	{
		hue = 0.0 + 60.0 * (green - blue);
		if (hue < 0.0)
		{
			hue += 360.0;
		}
	}
	else if (rgb_max == green)
	{
		hue = 120.0 + 60.0 * (blue - red);
	}
	else
	{
		hue = 240.0 + 60.0 * (red - green);
	}
}
