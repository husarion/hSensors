#include "Hitechnic_ColorV2.h"

#include <hFramework.h>

#define SENSOR_ADDRESS 0x01

#define HTCS2_CMD_REG         0x41      /*!< Command register */
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

using namespace hSensors;

static void RGBtoHSV(float red, float green, float blue, float &hue, float &sat, float &value);

Hitechnic_ColorV2::Hitechnic_ColorV2(ILegoSensor_i2c& sensor) : sens(sensor), initialized(false)
{
}
Hitechnic_ColorV2::~Hitechnic_ColorV2()
{
	deinit();
}

void Hitechnic_ColorV2::init()
{
	if (initialized)
		return;
	sens.selectI2C();
	sens.getI2C().setDataRate(10000);
}
void Hitechnic_ColorV2::deinit()
{
	if (!initialized)
		return;
	initialized = false;
}

int Hitechnic_ColorV2::readColor()
{
	init();
	if (mode != HTCS2_MODE_ACTIVE)
		sendCommand(HTCS2_MODE_ACTIVE);

	uint8_t tx[1], rx[3];
	tx[0] = HTCS2_OFFSET + HTCS2_COLNUM_REG;
	if (!sens.getI2C().read(1, tx, 1, rx, 1))
		return 0;

	return rx[0];
}
bool Hitechnic_ColorV2::readRGB(uint8_t &red, uint8_t &green, uint8_t &blue)
{
	init();
	if (mode != HTCS2_MODE_ACTIVE)
		sendCommand(HTCS2_MODE_ACTIVE);

	uint8_t tx[1], rx[3];
	tx[0] = HTCS2_OFFSET + HTCS2_RED_REG;
	if (!sens.getI2C().read(1, tx, 1, rx, 3))
		return false;

	red = rx[0];
	green = rx[1];
	blue = rx[2];

	return true;
}
bool Hitechnic_ColorV2::readHSV(float &hue, float &saturation, float &value)
{
	uint8_t red, green, blue;

	bool ret = readRGB(red, green, blue);
	RGBtoHSV(red, green, blue, hue, saturation, value);

	return ret;
}
bool Hitechnic_ColorV2::readWhite(int &white)
{
	init();
	if (mode != HTCS2_MODE_ACTIVE)
		sendCommand(HTCS2_MODE_ACTIVE);

	uint8_t tx[1], rx[1];
	tx[0] = HTCS2_OFFSET + HTCS2_WHITE_REG;
	if (!sens.getI2C().read(1, tx, 1, rx, 1))
		return false;

	white = rx[0];

	return true;
}
bool Hitechnic_ColorV2::readNormRGB(int &red, int &green, int &blue)
{
	init();
	uint8_t tx[1], rx[3];
	tx[0] = HTCS2_OFFSET + HTCS2_RED_NORM_REG;
	if (!sens.getI2C().read(1, tx, 1, rx, 3))
		return false;

	red = rx[0];
	green = rx[1];
	blue = rx[2];

	return true;
}
bool Hitechnic_ColorV2::readRawRGB(bool passive, long &red, long &green, long &blue)
{
	init();
	if (passive && (mode != HTCS2_MODE_PASSIVE))
		sendCommand(HTCS2_MODE_PASSIVE);
	if (!passive && (mode != HTCS2_MODE_RAW))
		sendCommand(HTCS2_MODE_RAW);

	uint8_t tx[1], rx[8];
	tx[0] = HTCS2_OFFSET + HTCS2_RED_MSB;
	if (!sens.getI2C().read(1, tx, 1, rx, 8))
		return false;

	red = (long)rx[0] * 256 + rx[1];
	green = (long)rx[2] * 256 + rx[3];
	blue = (long)rx[4] * 256 + rx[5];

	return true;
}
bool Hitechnic_ColorV2::readRawWhite(bool passive, long &white)
{
	init();
	if (passive && (mode != HTCS2_MODE_PASSIVE))
		sendCommand(HTCS2_MODE_PASSIVE);
	if (!passive && (mode != HTCS2_MODE_RAW))
		sendCommand(HTCS2_MODE_RAW);

	uint8_t tx[1], rx[2];
	tx[0] = HTCS2_OFFSET + HTCS2_WHITE_MSB;
	if (!sens.getI2C().read(1, tx, 1, rx, 2))
		return false;

	white = (long)rx[0] * 256 + rx[1];

	return true;
}
int Hitechnic_ColorV2::readColorIndex()
{
	init();
	if (mode != HTCS2_MODE_ACTIVE)
		sendCommand(HTCS2_MODE_ACTIVE);

	uint8_t tx[1], rx[1];
	tx[0] = HTCS2_OFFSET + HTCS2_COL_INDEX_REG;
	if (!sens.getI2C().read(1, tx, 1, rx, 1))
		return false;

	return rx[0];
}

bool Hitechnic_ColorV2::sendCommand(uint8_t command)
{
	uint8_t tx[2];
	tx[0] = HTCS2_CMD_REG;
	tx[1] = command;

	if (command < 30)
		mode = command;

	return sens.getI2C().write(1, tx, 2);
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
