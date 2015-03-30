set(CMAKE_SYSTEM_NAME "Generic")
# cmake_minimum_required (VERSION 2.6)
get_filename_component(CURRENT_DIR ${CMAKE_CURRENT_LIST_FILE} PATH) # for cmake before 2.8.3

# projectname is the same as the main-executable
# project(robocore-sensors)

# add_definitions('-g')
# add_definitions('-Wall')
#add_definitions('-std=c++11')

# add_executable(${PROJECT_NAME} ${PROJECT_NAME}.cpp)
# set(include_flags "${include_flags} -I ${CURRENT_DIR}/include/")

# add_custom_target(${PROJECT_NAME}-symlink ALL ln --force -s ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME} ${CMAKE_SOURCE_DIR}/${PROJECT_NAME} DEPENDS ${PROJECT_NAME})
# set_directory_properties(PROPERTIES ADDITIONAL_MAKE_CLEAN_FILES ${CMAKE_SOURCE_DIR}/${PROJECT_NAME})

include_directories("${CURRENT_DIR}/include")

FILE(GLOB srcs "${CURRENT_DIR}/src/*.cpp")
add_source_files("${srcs}")
