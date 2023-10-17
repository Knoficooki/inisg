cmake_minimum_required(VERSION 3.25)
project(Inisg)

set(CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE CPP_SOURCES RELATIVE ${CMAKE_SOURCE_DIR} "src/*.cpp")

add_executable(inisg ${CPP_SOURCES})

set_target_properties(inisg PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")
