cmake_minimum_required(VERSION 3.14)
project(project-code)

set(CMAKE_CXX_STANDARD 14)

add_executable(decoder Pes_Packet.cpp Decoder.cpp "Transport Packet Structure/TransportPacket.cpp" "Transport Packet Structure/TransportPacket.h" PacketParsers/TSParser.cpp "Transport Packet Structure/AdaptationField.cpp" "Transport Packet Structure/AdaptationField.h" PacketParsers/AFParser.cpp Util/BitManipulator.cpp)
