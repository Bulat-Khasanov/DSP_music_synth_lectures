# The following lines of boilerplate have to be in your project's
# CMakeLists in this exact order for cmake to work correctly
cmake_minimum_required(VERSION 3.16.0)

# This line is required
set(EXTRA_COMPONENT_DIRS ./components/esp-dsp)

include($ENV{IDF_PATH}/tools/cmake/project.cmake)
project(1-st_task)
