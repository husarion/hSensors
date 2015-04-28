set(CMAKE_SYSTEM_NAME "Generic")
# cmake_minimum_required (VERSION 2.6)
get_filename_component(CURRENT_LIB_DIR ${CMAKE_CURRENT_LIST_FILE} PATH) # for cmake before 2.8.3

include_directories("${CURRENT_LIB_DIR}/include")
include_directories("${CURRENT_LIB_DIR}/include/robotc")

FILE(GLOB tmp "${CURRENT_LIB_DIR}/src/*.cpp")
list(APPEND srcs ${tmp})
FILE(GLOB tmp "${CURRENT_LIB_DIR}/src/robotc/*.cpp")
list(APPEND srcs ${tmp})
set(HSENSORS_SOURCES "${srcs}")
