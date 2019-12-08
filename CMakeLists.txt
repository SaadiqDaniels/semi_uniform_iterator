cmake_minimum_required(VERSION 3.15)
project(templ_iterator)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0")
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -O0")
set(CMAKE_CXX_STANDARD 17)
add_compile_options(-Wall -Wextra -Werror -Wattributes)

add_executable(simple_vector s_vector_driver.cpp iterator.h inheritance.h)
add_executable(complex_vector c_vector_driver.cpp iterator.h inheritance.h)
add_executable(simple_map s_map_driver.cpp iterator.h inheritance.h)
add_executable(complex_map c_map_driver.cpp iterator.h inheritance.h)
add_executable(stl_algorithm algorithm_driver.cpp iterator.h inheritance.h)
