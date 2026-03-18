cmake_minimum_required(VERSION 3.10)
project(Project1 LANGUAGES C CXX)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(FLEX REQUIRED)

FLEX_TARGET(Scanner cmos.l ${CMAKE_CURRENT_BINARY_DIR}/lex.yy.c)

add_executable(scanner ${FLEX_Scanner_OUTPUTS})

add_executable(cmos cmos.cpp)