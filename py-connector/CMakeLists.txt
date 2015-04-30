cmake_minimum_required(VERSION 2.6)
get_filename_component(CURRENT_PY_DIR ${CMAKE_CURRENT_LIST_FILE} PATH) # for cmake before 2.8.3

project(hPySensors C CXX ASM)

if(NOT HFRAMEWORK_PATH)
	set(HFRAMEWORK_PATH ${CURRENT_PY_DIR}/../../hFramework)
endif()

if(NOT HPYTHON_PATH)
	set(HPYTHON_PATH ${CURRENT_PY_DIR}/../../hPython/)
endif()

include(${HFRAMEWORK_PATH}/robocore_common.cmake)
include(${HPYTHON_PATH}/hPython.cmake)
include(${CURRENT_PY_DIR}/../hSensors.cmake)

if(NOT RELEASE)
	set(TARGET_NAME hPySensorsd)
else()
	set(TARGET_NAME hPySensors)
endif()

set(HPYFRAMEWORK_SOURCES
	${CMAKE_CURRENT_BINARY_DIR}/gen_hPySensors.h
	${CMAKE_CURRENT_BINARY_DIR}/gen_hPySensors.c
	${CMAKE_CURRENT_BINARY_DIR}/gen_hPySensors.cpp)

set(EXPORTS_FILE ${CURRENT_PY_DIR}/exports)

add_custom_command(OUTPUT ${HPYFRAMEWORK_SOURCES}
	COMMAND python2.7 ${CURRENT_PY_DIR}/mpy-gen/generate.py --config ${EXPORTS_FILE} --outdir ${CMAKE_CURRENT_BINARY_DIR}
		--extern ${HFRAMEWORK_PATH}/py-connector/exports
	DEPENDS ${EXPORTS_FILE})

add_library(${TARGET_NAME} bindir ${HPYFRAMEWORK_SOURCES})

set(BINDIR "${CURRENT_PY_DIR}/../libs/RoboCORE_${ROBOCORE_VERSION}_${ROBOCORE_TYPE}")
add_custom_command(OUTPUT bindir COMMAND mkdir -p ${BINDIR})
set_target_properties(${TARGET_NAME}
	PROPERTIES
	ARCHIVE_OUTPUT_DIRECTORY ${BINDIR})
