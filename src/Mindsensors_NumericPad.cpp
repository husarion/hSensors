#include "Mindsensors_NumericPad.h"

#include <hFramework.h>

#define I2C_ADDR  0x5A
#define DATA_REG  0x00

const int8_t MSNP_NumMap[] = { -1, 9, 6, 3, 0, 8, 2, 5, -1, 7, 1, 4};

using namespace hSensors;


Mindsensors_NumericPad::Mindsensors_NumericPad(ILegoSensor_i2c& sensor) : sens(sensor), initialized(false)
{
}
Mindsensors_NumericPad::~Mindsensors_NumericPad()
{
	deinit();
}

Mindsensors_NumericPad::EError Mindsensors_NumericPad::init()
{
	if (initialized)
	{
		return ERROR_OK;
	}
	sens.selectI2C();
	sens.getI2C().setDataRate(10000);

	uint8_t tx9[9];
	tx9[0] = 0x2B;
	tx9[1] = 0X01;
	tx9[2] = 0x01;
	tx9[3] = 0x00;
	tx9[4] = 0x00;
	tx9[5] = 0x01;
	tx9[6] = 0x01;
	tx9[7] = 0xFF;
	tx9[8] = 0x02;
	if (!sens.getI2C().write(I2C_ADDR, tx9, 9))
		return ERROR_PROTO;

	uint8_t tx15[15];
	tx15[0] = 0x41;
	tx15[1] = 0x0F;
	tx15[2]= 0x0A;
	tx15[3] = 0x0F;
	tx15[4] = 0x0A;
	tx15[5] = 0x0F;
	tx15[6] = 0x0A;
	tx15[7] = 0x0F;
	tx15[8] = 0x0A;
	tx15[9] = 0x0F;
	tx15[10] = 0x0A;
	tx15[11] = 0x0F;
	tx15[12] = 0x0A;
	tx15[13] = 0x0F;
	tx15[14] = 0x0A;
	if (!sens.getI2C().write(I2C_ADDR, tx15, 15))
		return ERROR_PROTO;

	uint8_t tx13[13];
	tx13[0] = 0x4F;
	tx13[1] = 0x0F;
	tx13[2] = 0x0A;
	tx13[3] = 0x0F;
	tx13[4] = 0x0A;
	tx13[5] = 0x0F;
	tx13[6] = 0x0A;
	tx13[7] = 0x0F;
	tx13[8] = 0x0A;
	tx13[9] = 0x0F;
	tx13[10] = 0x0A;
	tx13[11] = 0x0F;
	tx13[12] = 0x0A;
	if (!sens.getI2C().write(I2C_ADDR, tx13, 13))
		return ERROR_PROTO;

	uint8_t tx4[4];
	tx4[0] = 0x5C;
	tx4[1] = 0x0B;
	tx4[2] = 0x20;
	tx4[3] = 0x0C;

	if (!sens.getI2C().write(I2C_ADDR, tx4, 4))
		return ERROR_PROTO;

	uint8_t tx2[2];
	tx2[0] = 0x7B;
	tx2[1] = 0x0B;
	if (!sens.getI2C().write(I2C_ADDR, tx2, 2))
		return ERROR_PROTO;

	uint8_t tx4p[4];
	tx4p[0] = 0x7D;
	tx4p[1] = 0x9C;
	tx4p[2] = 0x65;
	tx4p[3] = 0x8C;

	if (!sens.getI2C().write(I2C_ADDR, tx4p, 4))
		return ERROR_PROTO;
	initialized = true;
	sys.delay_ms(10);
	return ERROR_OK;
}
void Mindsensors_NumericPad::deinit()
{
	if (!initialized)
		return;
	initialized = false;
}

Mindsensors_NumericPad::EError Mindsensors_NumericPad::scanKeys(Pressed & k)
{
	init();
	uint8_t tx[1];
	tx[0] = DATA_REG;
	uint8_t t[2];
	if(!sens.getI2C().rw(I2C_ADDR, tx, 1, t, 2))
		return ERROR_PROTO;
	k.pressed = t[0] + (t[1] * 256);
	return ERROR_OK;
}

Pressed::Pressed()
{
}
Pressed::~Pressed()
{
}

bool Pressed::zero()
{
	if(pressed & (1 << 4))
		return true;

	return false;
}

bool Pressed::one()
{
	if(pressed & 1 << 10)
		return true;

	return false;
}

bool Pressed::two()
{
	if(pressed & (1 << 6))
		return true;

	return false;
}

bool Pressed::three()
{
	if(pressed & 1 << 3)
		return true;

	return false;
}

bool Pressed::four()
{
	if(pressed & (1 << 11))
		return true;

	return false;
}

bool Pressed::five()
{
	if(pressed & (1 << 7))
		return true;

	return false;
}

bool Pressed::six()
{
	if(pressed & (1 << 2))
		return true;

	return false;
}

bool Pressed::seven()
{
	if(pressed & (1 << 9))
		return true;

	return false;
}

bool Pressed::eight()
{
	if(pressed & (1 << 5))
		return true;

	return false;
}

bool Pressed::nine()
{
	if(pressed & 1 << 1)
		return true;

	return false;
}

bool Pressed::hash()
{
	if((pressed) & 1)
		return true;

	return false;
}

bool Pressed::star()
{
	if(pressed & (1 << 8))
		return true;

	return false;
}
void Pressed::whichOne()
{
	uint8_t d = 0;
	if(zero())
	{
		printf("0 ");
		d = 1;
	}
	if(one())
	{
		printf("1 ");
		d = 1;
	}
	if(two())
	{
		printf("2 ");
		d = 1;
	}
	if(three())
	{
		printf("3 ");
		d = 1;
	}
	if(four())
	{
		printf("4 ");
		d = 1;
	}
	if(five())
	{
		printf("5 ");
		d = 1;
	}
	if(six())
	{
		printf("6 ");
		d = 1;
	}
	if(seven())
	{
		printf("7 ");
		d = 1;
	}
	if(eight())
	{
		printf("8 ");
		d = 1;
	}
	if(nine())
	{
		printf("9 ");
		d = 1;
	}
	if(hash())
	{
		printf("# ");
		d = 1;
	}
	if(star())
	{
		printf("*");
		d = 1;
	}
	if(d == 0)
		printf("none");
	return;
}

int16_t Pressed::getNumber()
{
	int16_t v = 0;
	uint8_t r = 0;
	for (uint8_t i = 0; i < 12; i++)
	{
		if(pressed & (1<<i))
		{
			r++;
			v = MSNP_NumMap[i];
		}
	}
	if(r == 0 || r>1)
		v = -1;
	return v;
}
