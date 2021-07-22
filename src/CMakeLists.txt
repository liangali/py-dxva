cmake_minimum_required(VERSION 3.4)
project(pydxva)

if (DEFINED PYTHON_INCLUDE AND DEFINED PYBIND11_INCLUDE AND DEFINED PYTHON_LIB)
    message(STATUS "#### CMAKE: PYTHON_INCLUDE=" ${PYTHON_INCLUDE})
    message(STATUS "#### CMAKE: PYBIND11_INCLUDE=" ${PYBIND11_INCLUDE})
    message(STATUS "#### CMAKE: PYTHON_LIB=" ${PYTHON_LIB})
else()
    message(FATAL  "#### CMAKE: PYTHON_INCLUDE/PYBIND11_INCLUDE/PYTHON_LIB is not set properly, run python build.py")
endif()

include_directories(${PYTHON_INCLUDE} ${PYBIND11_INCLUDE})
link_directories(${PYTHON_LIB})
add_library(pydxva SHARED pydxva.cpp profile.cpp)
target_link_libraries(pydxva d3d11)
set_target_properties(pydxva PROPERTIES SUFFIX ".pyd")

