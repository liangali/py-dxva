cmake_minimum_required(VERSION 3.4)
project(pydxva)

if(DEFINED ENV{PYTHON_INCLUDE} AND DEFINED ENV{PYBIND11_INCLUDE})
    message(STATUS "#### INFO: PYTHON_INCLUDE=" $ENV{PYTHON_INCLUDE})
    message(STATUS "#### INFO: PYBIND11_INCLUDE=" $ENV{PYBIND11_INCLUDE})
else()
    message(FATAL_ERROR "#### ERROR: PYTHON_INCLUDE & PYBIND11_INCLUDE is not set")
endif()

set (PYTHON_INCLUDE_DIR "C:\\Program Files\\Python39\\Include")
set (PYBIND11_INCLUDE_DIR "C:\\Users\\neptu\\AppData\\Roaming\\Python\\Python39\\site-packages\\pybind11\\include")
set (PYTHON_LIB_DIR "C:\\Program Files\\Python39\\libs")

include_directories(${PYTHON_INCLUDE_DIR} ${PYBIND11_INCLUDE_DIR})
link_directories(${PYTHON_LIB_DIR})
add_library(pydxva SHARED test.cpp)
target_link_libraries(pydxva d3d11)
set_target_properties(pydxva PROPERTIES SUFFIX ".pyd")

