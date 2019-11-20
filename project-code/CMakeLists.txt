cmake_minimum_required(VERSION 3.14)
project(project-code)

set(CMAKE_CXX_STANDARD 14)

add_executable(decoder Pes_Packet.cpp TSParser.h)