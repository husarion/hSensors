cmake_minimum_required(VERSION 2.6)
get_filename_component(CURRENT_DIR ${CMAKE_CURRENT_LIST_FILE} PATH) # for cmake before 2.8.3

project(examples C CXX ASM)

if(NOT HFRAMEWORK_PATH)
	set(HFRAMEWORK_PATH "${CURRENT_DIR}/../")
endif()

include(${HFRAMEWORK_PATH}/hFramework.cmake)

add_component_lib(sensors "${CURRENT_DIR}/../")

add_hexecutable(lego_ultrasonic ../examples/lego_ultrasonic.cpp)
