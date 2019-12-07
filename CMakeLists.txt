cmake_minimum_required(VERSION 3.15)
project(templ_iterator)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0")
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -O0")
set(CMAKE_CXX_STANDARD 17)
add_compile_options(-Wall -Wextra)

add_library(inheritance inheritance.cpp inheritance.h)

add_executable(simple_vector s_vector_driver.cpp iterator.h)
add_executable(complex_vector c_vector_driver.cpp iterator.h)
add_executable(simple_map s_map_driver.cpp iterator.h)
add_executable(complex_map c_map_driver.cpp iterator.h)
add_executable(stl_algorithm algorithm_driver.cpp iterator.h)

target_link_libraries(simple_vector inheritance)
target_link_libraries(complex_vector inheritance)
target_link_libraries(simple_map inheritance)
target_link_libraries(complex_map inheritance)
target_link_libraries(stl_algorithm inheritance)