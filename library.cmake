set(CMAKE_SYSTEM_NAME "Generic")
get_filename_component(CURRENT_LIB_DIR ${CMAKE_CURRENT_LIST_FILE} PATH) # for cmake before 2.8.3

include(${CURRENT_LIB_DIR}/hSensors.cmake)

add_source_files("${HSENSORS_SOURCES}")
