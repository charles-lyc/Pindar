# The following lines of boilerplate have to be in your project's CMakeLists
# in this exact order for cmake to work correctly
cmake_minimum_required(VERSION 3.5)

include($ENV{IDF_PATH}/tools/cmake/project.cmake)

# add_subdirectory(mcu)
# add_subdirectory(driver)
# add_subdirectory(module)
# add_subdirectory(app)

# target_link_libraries(mcu)
# target_link_libraries(driver)
# target_link_libraries(module)
# target_link_libraries(app)

set(EXTRA_COMPONENT_DIRS ${CMAKE_SOURCE_DIR}/components/mcu)
set(EXTRA_COMPONENT_DIRS ${CMAKE_SOURCE_DIR}/components/drivers)
set(EXTRA_COMPONENT_DIRS ${CMAKE_SOURCE_DIR}/components/module)
set(EXTRA_COMPONENT_DIRS ${CMAKE_SOURCE_DIR}/components/app)

project(pindar)
