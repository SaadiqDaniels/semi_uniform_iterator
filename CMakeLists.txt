cmake_minimum_required(VERSION 3.15)
project(templ_iterator)

set(CMAKE_CXX_STANDARD 17)

add_executable(simple_vector s_vector_driver.cpp iteratorwrapper.h base.h handle.h iterator.h)
add_executable(complex_vector c_vector_driver.cpp iteratorwrapper.h base.h handle.h iterator.h)
add_executable(simple_map s_map_driver.cpp iteratorwrapper.h base.h handle.h iterator.h)
add_executable(complex_map c_map_driver.cpp iteratorwrapper.h base.h handle.h iterator.h)
add_executable(stl_algorithm algorithm_driver.cpp iteratorwrapper.h base.h handle.h iterator.h)
