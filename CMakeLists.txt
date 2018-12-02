project(AdvancedLog)

cmake_minimum_required(VERSION 3.13)

set(CMAKE_GENERATOR "CodeBlocks - Unix Makefiles")
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD 17)

add_subdirectory(vendor/clickhouse)

set(CMAKE_CXX_CLANG_TIDY "clang-tidy" "-checks=*" "-format-style=google")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")

add_executable(advanced_log_seed main.cpp)
target_link_libraries (advanced_log_seed clickhouse-client-lib)
