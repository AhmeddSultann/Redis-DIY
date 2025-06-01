cmake_minimum_required(VERSION 3.31)
project(Redis_DIY)

set(CMAKE_CXX_STANDARD 14)

include_directories(ServerClient)

add_executable(Redis_DIY
        ServerClient/server.cpp
        ServerClient/server.h
        ServerClient/client.cpp
        ServerClient/client.h)
