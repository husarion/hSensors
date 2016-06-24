#ifndef __MINDSENSORS_NUMERICPAD_H__
#define __MINDSENSORS_NUMERICPAD_H__

#include <hFramework.h>
namespace hSensors
{
/**
 * @brief Provides interface for LineLeader sensor.
 */

class Pressed
{
public:
	Pressed();
	~Pressed(); //!< Destory sensor object.
	uint16_t pressed;
	bool zero();
	bool one();
	bool two();
	bool three();
	bool four();
	bool five();
	bool six();
	bool seven();
	bool eight();
	bool nine();
	bool hash();
	bool star();
	void whichOne();
	int16_t getNumber();

};
class Mindsensors_NumericPad
{
public:
	enum EError { ERROR_OK, ERROR_PROTO };

	/**
	 * @brief Create sensor object.
	 * @param sensor - I2C capable hSensor port (eg. hSens1, hSens2) or software I2C
	 * implementation (eg. \c hSens3.getSoftwareI2C(), \c hSens4.getSoftwareI2C())
	 */
	Mindsensors_NumericPad(ILegoSensor_i2c& sensor);
	~Mindsensors_NumericPad(); //!< Destory sensor object.

	EError init(); //!< Initialize sensor.
	void deinit(); //!< Deinitialize sensor.

	/**
	 * @brief Scan the keypad for pressed keys.
	 *
	 * @param pressed a binary representation of all keys pressed
	 * @param key character representation of the first key pressed, X if no key was pressed
	 * @param number the numeric equivalent, 0-9 for digits, -1 for # and -2 for *, -255 when nothing is pressed
	 * @return error code
	 */
	EError scanKeys(Pressed & k);

private:

	ILegoSensor_i2c &sens;
	bool initialized;

};

}

#endif
