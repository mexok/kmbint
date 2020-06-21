cmake_minimum_required(VERSION 3.14)
project(kmbint C)

set(CMAKE_C_STANDARD 99)

add_library(kmbint STATIC src/kmbint.c)
target_include_directories(kmbint PUBLIC include)

add_executable(kmbint_tests src/tests.c)
target_link_libraries(kmbint_tests kmbint)

add_executable(kmbint_example src/example.c)
target_link_libraries(kmbint_example kmbint)
