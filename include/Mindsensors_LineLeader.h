#ifndef __MINDSENSOR_LINELEADER_H__
#define __MINDSENSOR_LINELEADER_H__

#include <hFramework.h>

namespace hSensors
{
/**
 * @brief Provides interface for LineLeader sensor.
 */
class Mindsensors_LineLeader
{
public:
	enum EError { ERROR_OK, ERROR_PROTO };

	/**
	 * @brief Create sensor object.
	 * @param sensor - I2C capable hSensor port (eg. hSens1, hSens2) or software I2C
	 * implementation (eg. \c hSens3.getSoftwareI2C(), \c hSens4.getSoftwareI2C())
	 */
	Mindsensors_LineLeader(ILegoSensor_i2c& sensor);
	~Mindsensors_LineLeader(); //!< Destory sensor object.

	EError init(); //!< Initialize sensor.
	void deinit(); //!< Deinitialize sensor.

	/**
	* @brief Read the uncalibrated sensors' values from the Line Leader.
	*
	* Each sensor returns a 16 bit value.
	* @param SensorUncVal - is 8 bytes returned. One for each sensor.
	* @return error code
	*/
	EError  readSensorUncalibrated(int8_t *SensorUncVal);

	/**
	* @brief Read the "Raw Sensor" values from the Line Leader.
	*
	* Amount of light or dark each sensor sees.  Typically between 0-20.  0=black, 100=white
	* @param pTab - is 8 ubytes returned.  One for each sensor.
	* @return error code
	*/
	EError  readSensorRaw(uint8_t *pTab);

	/**
	* @brief Read ubyte value with each bit equal to a sensor.
	*
	* 1 = Line<br>
	* 0 = No Line
	* <pre>SENSOR:      0    1    2    3    4    5    6    7
	* MULTIPLIER:  1    2    4    8    16   32   64   128</pre>
	* To determine if a given sensor is over a line or not, use binary math
	* to test each bit.<br>
	* EXAMPLE: A returned value of 5 means sensor 0 and 2 are over a line.
	* @param v - is a ubyte returned.
	* @return  error code
	*/
	EError  readResult(uint8_t &v);

	/**
	* @brief Read the Weighted "Average" value from the sensor.
	*
	* Average is calculated internally by the sensor where each of the eight sensors is either triggered or not
	* and multiplied by a a factor to help determine if the line is left, right or
	* on center of the line (according to the set point).<br>
	* EXPECTED VALUES: 0-80<br>
	* <pre>SENSOR:       0    1    2    3    4    5    6    7
	* MULTIPLIER:  10   20   30   40   50   60   70   80</pre>
	* FORMULA: Sum(Weighted Values)/Number sensors on line<br>
	* EXAMPLE: if sensor 6 and 7 are over a line, the average is:<br>
	*     (0 + 0 + 0 + 0 + 0 + 0 + 70 + 80)/2 = 75<br>
	*     in this case 75 > 45 (set point) so the bot is right of center
	* @param v - is a ubyte returned.
	* @return error code
	*/
	EError  readAverage(uint8_t &v);

	/**
	* @brief Read the "Steering" value from the sensor.
	*
	* This value is calculated internally and can directly be used to set turning values for the robot's motors.<br>
	* EXPECTED VALUES: -100 to 100
	* @param v - is a one byte returned.
	* @return error code
	*/
	EError  readSteering(int8_t &v);

	/**
	*@brief Reads the "setPoint" value from the sensor.
	*
	* The set point is used by internally (or externally) by the sensor to
	* determine the middle of the sensor over a line.
	* @param v - is a ubyte returned.
	* @return error code
	*/
	EError  readsetPoint(uint8_t &v);

	/**
	* @brief Read the "Kp" value from the sensor.
	*
	* Reads Kp value, p = Kp / KpFactor
	* @param v - return value.
	* @return error code
	*/
	EError  readKp(uint8_t &v);

	/**
	* @brief Read the "Kp factor" value from the sensor.
	*
	* @param v - returned value.
	* @return error code
	*/
	EError  readKpFactor(uint8_t &v);

	/**
	* @brief Read the "Ki" value from the sensor.
	*
	* This function reads Ki value, i = Ki / KiFactor
	* @param v - retured value.
	* @return error code
	*/
	EError  readKi(uint8_t &v);

	/**
	* @brief Read the "Ki factor" value from the sensor.
	*
	* @param v - returned value.
	* @return error code
	*/
	EError  readKiFactor(uint8_t &v);

	/**
	* @brief Read the "Kd" value from the sensor.
	*
	* This function reads Kd value, d = Kd / KdFactor
	* @param v - returned value.
	* @return error code
	*/
	EError  readKd(uint8_t &v);

	/**
	* @brief Read the "Kd factor" value from the sensor.
	*
	* @param v - returned value.
	* @return error code
	*/
	EError  readKdFactor(uint8_t &v);

	/**
	* @brief Read the "White Threshold" values from the Line Leader for each sensor.
	*
	* Each of the eight sensors has a value.  Raw values greater then this threshold
	* equal white (area).<br>
	* The values are set when calibrating the white points for the sensor.
	* @param pTab - is 8 bytes returned.  One for each sensor with Threshold.
	* @return error code
	*/
	EError readWhiteThresh(uint8_t *pTab);

	/**
	* @brief Read the "Black Threshold" values
	*
	* Read the "Black Threshold" values from the Line Leader for each sensor.<br>
	* Each of the eight sensors has a value.  Raw values less then this threshold
	* equal black (line).<br>
	* The values are set when calibrating the black points for the sensor.
	* @param pTab - is 8 bytes returned.  One for each sensor with Threshold.
	* @return error code
	*/
	EError readBlackThresh(uint8_t *pTab);

	/**
	*@brief Wake up the sensor
	*
	* This function wakes the line leader to prepare for use.
	* Using any function reading from sensor or writing to it also wake up line leader.
	* @return error code
	*/
	EError wakeUp();

	/**
	* @brief Puts to sleep mode
	*
	* This function puts the line leader to sleep conserve power.
	* @return error code
	*/
	EError sleep();

	/**
	* @brief Invert Line color
	*
	* The function toggles from dark line on light to light line on dark and back.
	* @return error code
	*/
	EError invertLineColor();

	/**
	* @brief Reset line's color to default
	*
	* The function resets to default of sensing a dark line on light background
	* @return error code
	*/
	EError resetLineColor();

	/**
	* @brief Take a snapshot
	*
	* This function takes a snapshot of the line under the sensor
	* and tracks that position in subsequent tracking operations.
	* Also this function will set inversion if it sees white line
	* on dark background
	* @return error code
	*/
	EError takeSnapshot();

	/**
	* @brief Calibration White Thresold
	*
	* This function calibrates the white threshold for each sensor in the array.
	* Place the array over the white surface with all sensors on the white
	* area.  Execute this command to set white values internally.
	* @return error code
	*/
	EError calWhite();

	/**
	* @brief Calibration Black Threshold
	*
	* This function calibrates the black threshold for each sensor in the array.
	* Place the array over the white surface with all sensors on the black
	* area.  Execute this command to set black values internally.
	* @return error code
	*/
	EError calBlack();

	/**
	* Setting parameters
	*/

	/**
	* @brief Set the "Kp" value for the sensor's internal PID calculations.
	*
	* This value is usually set close to 1.0  default 25/32<br>
	* EXPECTED VALUES: 0 to 255<br>
	* DEFAULT VALUE: 25<br>
	* EXPECTED FACTORS: 1 to 255<br>
	* DEFAULT FACTOR: 32
	* @param  k - the value to set Kp
	* @param  factor - the Kp factor, p = Kp/Kpfactor
	* @return error code
	*/
	EError setKp(uint8_t k, uint8_t factor);

	/**
	* @brief Set the "Ki" value for the sensor's internal PID calculations.
	*
	* This value is usually set close to 0  default 0/1<br>
	* EXPECTED VALUES: 0 to 255<br>
	* DEFAULT VALUE: 0<br>
	* EXPECTED FACTORS: 1 to 255<br>
	* DEFAULT FACTOR: 1
	* @param  k - the value to set Ki
	* @param  factor - the Ki factor, i = Ki/Kifactor
	* @return error code
	*/
	EError setKi(uint8_t k, uint8_t factor);

	/**
	* @brief Set the "Kd" value for the sensor's internal PID calculations.
	*
	* This value is usually set lower to stabilize default 8/32<br>
	* EXPECTED VALUES: 0 to 255<br>
	* DEFAULT VALUE: 8<br>
	* EXPECTED VALUES: 1 to 255<br>
	* DEFAULT FACTOR: 32
	* @param  k - the value to set Kd
	* @param  factor - the Kd factor, d = Kd/Kdfactor
	* @return error code
	*/
	EError setKd(uint8_t k, uint8_t factor);

	/**
	* @brief Set "SetPoint" value,
	*
	* The set point is used by internally (or externally) by the sensor to
	* determine the middle of the sensor over a line.  This value is compared to
	* the average value to help the robot know if it is left or right of center.
	* @param  data - the value to set the set point to.
	* @return error code
	*/
	EError setPoint(uint8_t data);


private:
	/**
	* @brief Reads multiple bytes from a register in the Line leader sensor over I2C.
	*
	* Note: this is an internal function and should not be called directly.
	* @param  regToRead - the register to read from
	* @param  numBytes  - the number of bytes to read
	* @param  pDataMsg  - one bytes array to store reply
	* @return error code
	*/
	EError  _read(uint8_t regToRead, uint16_t numBytes, uint8_t *pDataTab);

	/**
	* @brief Reads one ubyte from a register in the Line leader sensor over I2C.
	*
	* Note: this is an internal function and should not be called directly.
	* @param  regToRead - the register to read from
	* @param  retval    - the uint8_t value in which to store the reply
	* @return error code
	*/
	EError  _read(uint8_t regToRead, uint8_t *retval);
	//funkcje używane do wpisywania wartości do sensora

	/**
	 * @brief Sending command to line leader
	* This function sends a command to the lineleader over I2C.
	*
	* @param  cmd - the command to be sent
	* @return error code
	PRELIMINARY COMMANDS FROM NXC LIB CODE
	- A American frequency compensation
	- B for black calibration
	- D sensor power down
	- E European frequency compensation
	- I invert line color
	- P power on sensor
	- R reset line color to dark
	- S snapshot to determine line color
	- U Universal frequency compensation (default)
	- S setpoint based on snapshot (automatically set's invert if needed)
	- W White balance
	*/
	EError sendCmd(uint8_t cmd);

	/**
	 * @brief Writing data to sensor
	* This function writes data to a register in the line leader sensor over I2C.
	*
	* Note: this is an internal function and should not be called directly.
	* @param  regToWrite - the register to write to
	* @param  data       - the value to write to the register
	* @return error code
	*/
	EError _write(uint8_t regToWrite, uint8_t data);

	ILegoSensor_i2c &sens;
	bool initialized;
};

}

#endif
