cmake_minimum_required(VERSION 3.30)
project(catlang CXX)

set(CMAKE_CXX_STANDARD 17)
add_link_options(-static -static-libgcc -static-libstdc++)

include_directories(${CMAKE_SOURCE_DIR}/headers)

add_executable(catlang main.cpp)
