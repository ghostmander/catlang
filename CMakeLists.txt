cmake_minimum_required(VERSION 3.30)
project(progaming_language CXX)

set(CMAKE_CXX_STANDARD 17)

include_directories(${CMAKE_SOURCE_DIR}/headers)

add_executable(progaming_language main.cpp)
