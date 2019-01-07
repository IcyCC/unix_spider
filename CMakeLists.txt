cmake_minimum_required(VERSION 3.12)
project(unxi_spider)

set(CMAKE_CXX_STANDARD 14)

include_directories(src)

add_executable(unxi_spider
        src/main.cpp
        src/parser.cpp
        src/util.h)
