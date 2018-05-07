cmake_minimum_required(VERSION 3.10)
project(ThreadSync)

set(CMAKE_CXX_STANDARD 14)

add_executable(ThreadSync concurrent_rw.cpp)

TARGET_LINK_LIBRARIES(ThreadSync pthread)