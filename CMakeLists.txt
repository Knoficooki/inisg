cmake_minimum_required(VERSION 3.25)
project(Inisg VERSION 0.0.0)

message("Building inisg version: ${CMAKE_PROJECT_VERSION}")

set(CMAKE_CXX_STANDARD 17)

message("Minimum C++ version: ${CMAKE_CXX_STANDARD}")

file(GLOB_RECURSE CPP_SOURCES RELATIVE ${CMAKE_SOURCE_DIR} "src/*.cpp")

message("Files to compile: ${CPP_SOURCES}")

add_executable(inisg ${CPP_SOURCES})

set_target_properties(inisg PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")

message("Build finished!")