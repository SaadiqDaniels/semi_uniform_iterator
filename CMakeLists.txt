cmake_minimum_required(VERSION 3.10)
project(templ_iterator)

set(CMAKE_CXX_STANDARD 17)

#add_compile_options(-Wall -Wextra -pedantic -ansi -Werror)

add_executable(constructor constructor_driver.cpp)
add_executable(vector vector_driver.cpp)
add_executable(map map_driver.cpp)
add_executable(stl_algorithm algorithm_driver.cpp)
