cmake_minimum_required(VERSION 3.10)
project(templ_iterator)

set(CMAKE_CXX_STANDARD 17)

add_executable(simple_vector s_vector_driver.cpp base.h iterator.h iterator_base.h const_iterator_base.h iterator_wrapper.h const_iterator_wrapper.h)
add_executable(const_vector c_vector_driver.cpp base.h iterator.h iterator_base.h const_iterator_base.h iterator_wrapper.h const_iterator_wrapper.h)
add_executable(simple_map s_map_driver.cpp base.h iterator.h iterator_base.h const_iterator_base.h iterator_wrapper.h const_iterator_wrapper.h)
add_executable(const_map c_map_driver.cpp base.h iterator.h iterator_base.h const_iterator_base.h iterator_wrapper.h const_iterator_wrapper.h)
add_executable(stl_algorithm algorithm_driver.cpp base.h iterator.h iterator_base.h const_iterator_base.h iterator_wrapper.h const_iterator_wrapper.h)
