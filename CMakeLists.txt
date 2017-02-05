cmake_minimum_required(VERSION 2.6)
project(hSensors NONE)

include(${HFRAMEWORK_PATH}/hFramework.cmake)

include_directories("include")

add_library(hSensors
  ./src/Hitechnic_Accel.cpp
  ./src/Hitechnic_ColorV2.cpp
  ./src/Hitechnic_Compass.cpp
  ./src/Hitechnic_Gyro.cpp
  ./src/Lego_Light.cpp
  ./src/Lego_Sound.cpp
  ./src/Lego_Ultrasonic.cpp
  ./src/Hitechnic_Angle.cpp
  ./src/Hitechnic_EOPD.cpp
  ./src/Hitechnic_IRSeeker.cpp
  ./src/Lego_Temp.cpp
  ./src/Lego_Touch.cpp
  ./src/Mindsensors_IRDistance.cpp
  ./src/Mindsensors_LineLeader.cpp
  ./src/Mindsensors_NumericPad.cpp
  ./src/Mindsensors_Pressure.cpp
  ./src/Mindsensors_SumoEyes.cpp)
