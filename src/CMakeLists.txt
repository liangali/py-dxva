cmake_minimum_required(VERSION 3.4)
project(pydxva)

if(DEFINED ENV{PYTHON_INCLUDE} AND DEFINED ENV{PYBIND11_INCLUDE})
    message(STATUS "#### INFO: PYTHON_INCLUDE=" $ENV{PYTHON_INCLUDE})
    message(STATUS "#### INFO: PYBIND11_INCLUDE=" $ENV{PYBIND11_INCLUDE})
else()
    message(FATAL_ERROR "#### ERROR: PYTHON_INCLUDE & PYBIND11_INCLUDE is not set")
endif()

include_directories ("C:\\Program Files\\Python39\\Include" "C:\\Users\\neptu\\AppData\\Roaming\\Python\\Python39\\site-packages\\pybind11\\include")
link_directories("C:\\Program Files\\Python39\\libs")
add_library(pydxva SHARED test.cpp)
set_target_properties(pydxva PROPERTIES SUFFIX ".pyd")

