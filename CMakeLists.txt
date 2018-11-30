cmake_minimum_required(VERSION 3.13)

set(CMAKE_GENERATOR "CodeBlocks - Unix Makefiles")
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_C_COMPILER /usr/bin/clang)
set(CMAKE_CXX_COMPILER /usr/bin/clang++)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_CLANG_TIDY "clang-tidy" "-checks=*" "-format-style=google")


project(AdvancedLog)

add_executable(AdvancedLogSeed main.cpp)
