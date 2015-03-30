cmake_minimum_required (VERSION 2.6)
get_filename_component(CURRENT_DIR ${CMAKE_CURRENT_LIST_FILE} PATH) # for cmake before 2.8.3

project(hCloudClient C CXX ASM)

option(DEBUG "Enable debug informations" OFF)

if(NOT HFRAMEWORK_PATH)
	set(HFRAMEWORK_PATH ${CURRENT_DIR}/hFramework/)
endif()

set(debug_flags "-DSENSORS_DEBUG")

if(DEBUG)
	set(debug_flags "${debug_flags} -DDEBUG")
endif()

include(${HFRAMEWORK_PATH}/robocore_common.cmake)

include_directories("${CURRENT_DIR}/include/")

message("${include_flags}")

# set(ld_flags "-L${HFRAMEWORK_PATH}")

set(CMAKE_CXX_FLAGS "${common_flags} -std=c++11")
set(CMAKE_C_FLAGS "${common_flags} -std=c99")
# SET(CMAKE_SHARED_LIBRARY_LINK_C_FLAGS "${ld_flags}")
# SET(CMAKE_SHARED_LIBRARY_LINK_CXX_FLAGS "${ld_flags}")

FILE(GLOB srcs "${CURRENT_DIR}/src/*.cpp")

if(NOT RELEASE)
	add_library(sensorsd ${srcs})
else()
	add_library(sensors ${srcs})
endif()
