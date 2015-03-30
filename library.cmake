set(CMAKE_SYSTEM_NAME "Generic")
# cmake_minimum_required (VERSION 2.6)
get_filename_component(CURRENT_DIR ${CMAKE_CURRENT_LIST_FILE} PATH) # for cmake before 2.8.3

include_directories("${CURRENT_DIR}/include")

FILE(GLOB srcs "${CURRENT_DIR}/src/*.cpp")
add_source_files("${srcs}")
