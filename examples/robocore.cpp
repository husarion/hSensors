@PORTS: stm32
@BOARDS: robocore
@NAME: hitechnic_accel
#include <hFramework.h>
#include <Hitechnic_Accel.h> 

using namespace hSensors;

void hMain(void)
{
	Hitechnic_Accel sensor(hSens1); // initialization of acceleration sensor

	for (;;)
	{
		int16_t x, y, z;
		sensor.readRaw(x, y, z); // reading raw data from sensor
		hLED1.toggle();
		Serial.printf("x %5d y %5d z %5d\r\n", x, y, z); // printing on Serial console raw sensor value
		sys.delay(10);
	}
}

@PORTS: stm32
@BOARDS: robocore
@NAME: lego_ultrasonic

#include <hFramework.h>
#include <Lego_Ultrasonic.h>

using namespace hSensors;

void hMain(void)
{
	sys.setLogDev(&Serial);			// setting USB-serial as a default printf output
	Lego_Ultrasonic sensor(hSens1); 	// initialization of Lego Ultrasonic sensor

	for (;;) 
	{
// 		int dist = sensor.readDist(); //reading raw data from sensor
		hLED1.toggle();				
		printf("dist %d\r\n", dist);  // printing on Serial "dist (value of dist variable)"
		sys.delay(10);			 
	}
}


@PORTS: stm32
@BOARDS: robocore
@NAME: lego_touch

#include <hFramework.h>
#include <Lego_Touch.h>

using namespace hSensors;

void hMain(void)
{
	sys.setLogDev(&Serial);  // setting USB-serial as a default printf output
	Lego_Touch sensor(hSens5);  // initialization of Lego Touch sensor

	for (;;)  // Main program loop
	{
		bool pressed = sensor.isPressed();  // reading raw data from sensor
		hLED1.toggle();  
		printf("state %d\r\n", pressed);    // printing on Serial "state (value of pressed variable)"
		sys.delay(10); 
	}
}

@PORTS: stm32
@BOARDS: robocore
@NAME: lego_sound
#include <hFramework.h>
#include <Lego_Sound.h>

using namespace hSensors;

void hMain(void)
{
	sys.setLogDev(&Serial); // setting USB-serial as a default printf output
	Lego_Sound sensor(hSens5); // initialization of Lego Sound sensor

	for (;;)  // Main program loop
	{
		int16_t val; 
		val = sensor.readRaw(); // reading raw data from sensor
		hLED1.toggle();  
		printf("val %5d\r\n", val); // printing on Serial "val (value of val variable)"
		sys.delay(10);   
	}
}

@PORTS: stm32
@BOARDS: robocore
@NAME: lego_light
#include <hFramework.h>
#include <Lego_Light.h>

using namespace hSensors;

void hMain(void)
{
	sys.setLogDev(&Serial);  // setting USB-serial as a default printf output
	Lego_Light sensor(hSens5);  // initialization of Lego Light sensor

	for (;;)
	{
		int16_t val;  
		val = sensor.readRaw();  // reading raw data from sensor
		hLED1.toggle();  
		printf("val %5d\r\n", val);  // printing on Serial "val (value of val variable)"
		sys.delay(10); 
	}
}

@PORTS: stm32
@BOARDS: robocore
@NAME: hitechnic_colorv2
#include <hFramework.h>
#include <Hitechnic_ColorV2.h>

using namespace hSensors;

void hMain(void)
{
	sys.setLogDev(&Serial);  // setting USB-serial as a default printf output
	Hitechnic_ColorV2 sensor(hSens1); // initialization of Hitechnic ColorV2 sensor
	
	for (;;)
	{
		uint8_t r, g, b;  
		sensor.readRGB(r, g, b); // reading raw data from sensor
		hLED1.toggle();  
		printf("r %4d g %4d b %4d\r\n", r, g, b); //  printing on Serial console raw sensor value
		sys.delay(10);
	}
}

@PORTS: stm32
@BOARDS: robocore
@NAME: hitechnic_compass
#include <hFramework.h>
#include <Hitechnic_Compass.h>

using namespace hSensors;

void hMain(void)
{
	sys.setLogDev(&Serial);  // setting USB-serial as a default printf output
	Hitechnic_Compass sensor(hSens1); // initialization of Hitechnic Compass sensor

	for (;;)  
	{
		uint16_t heading; 
		sensor.readHeading(heading);  // reading raw data from sensor
		hLED1.toggle();
		printf("head %d\r\n", heading);  // printing on Serial "head (value of heading variable)"
		sys.delay(10); 
	}
}

@PORTS: stm32
@BOARDS: robocore
@NAME: hitechnic_gyro
#include <hFramework.h>
#include <Hitechnic_Gyro.h>

using namespace hSensors;

void hMain(void)
{
	sys.setLogDev(&Serial); // setting USB-serial as a default printf output
	Hitechnic_Gyro sensor(hSens5); // initialization of Hitechnic gyro sensor
	
	for (;;) 
	{
		int16_t rot;  
		rot = sensor.read();  // reading raw data from sensor
		hLED1.toggle();  
		printf("rot %d\r\n", rot); // printing on Serial "rot (value of rot variable)"
		sys.delay(10);  
	}
}
