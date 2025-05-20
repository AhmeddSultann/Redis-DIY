cmake_minimum_required(VERSION 3.31)
project(Redis_DIY)

set(CMAKE_CXX_STANDARD 14)

include_directories(Server)

add_executable(Redis_DIY
        Server/server.cpp
        Server/server.h)
