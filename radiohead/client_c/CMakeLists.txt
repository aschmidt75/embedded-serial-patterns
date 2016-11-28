cmake_minimum_required(VERSION 3.5)
project(radiohead1)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES src/main.cpp 
        lib/RadioHead/RH_Serial.cpp
        lib/RadioHead/RHCRC.cpp
        lib/RadioHead/RHGenericDriver.cpp
        lib/RadioHead/RHDatagram.cpp
        lib/RadioHead/RHReliableDatagram.cpp
        lib/RadioHead/RHutil/HardwareSerial.cpp
        )


include_directories(lib/RadioHead)
include_directories(lib/RadioHead/RHutil)
link_directories(lib/RadioHead)

add_executable(radiohead1 ${SOURCE_FILES})
