cmake_minimum_required(VERSION 3.5)

project(SunCAD VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake)


include(UtilsMacros REQUIRED)

include(SetupWxWidgets REQUIRED)

add_subdirectory(src)
