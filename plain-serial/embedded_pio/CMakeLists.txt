cmake_minimum_required(VERSION 3.6)
project(embedded_pio)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    src/main.cpp)

add_executable(embedded_pio ${SOURCE_FILES})