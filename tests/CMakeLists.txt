cmake_minimum_required(VERSION 2.6)
get_filename_component(CURRENT_DIR ${CMAKE_CURRENT_LIST_FILE} PATH) # for cmake before 2.8.3

project(examples C CXX ASM)

if(NOT HFRAMEWORK_PATH)
	set(HFRAMEWORK_PATH "${CURRENT_DIR}/../")
endif()

include(${HFRAMEWORK_PATH}/hFramework.cmake)

# add_component_lib(sensors "${CURRENT_DIR}/../")
add_component_src("${CURRENT_DIR}/../")

add_hexecutable(hitechnic_accel ../examples/hitechnic_accel.cpp)
add_hexecutable(lego_light ../examples/lego_light.cpp)
# add_hexecutable(lego_sound ../examples/lego_sound.cpp)

add_hexecutable(robotc_lego_ultrasonic ../examples/robotc_lego_ultrasonic.cpp)
add_hexecutable(robotc_lego_touch ../examples/robotc_lego_touch.cpp)
add_hexecutable(robotc_lego_light ../examples/robotc_lego_light.cpp)
add_hexecutable(robotc_hitechnic_accel ../examples/robotc_hitechnic_accel.cpp)
add_hexecutable(robotc_hitechnic_gyro ../examples/robotc_hitechnic_gyro.cpp)
add_hexecutable(robotc_hitechnic_compass ../examples/robotc_hitechnic_compass.cpp)
