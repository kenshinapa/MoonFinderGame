cmake_minimum_required(VERSION 3.27)
project(Moonfinder_Program)

set(CMAKE_CXX_STANDARD 14)

include_directories(MoonfinderRedone/classes)

add_executable(Moonfinder_Program
        MoonfinderRedone/classes/Client.cpp
        MoonfinderRedone/classes/Client.h
        MoonfinderRedone/classes/Edge.cpp
        MoonfinderRedone/classes/Edge.h
        MoonfinderRedone/classes/Player.cpp
        MoonfinderRedone/classes/Player.h
        MoonfinderRedone/classes/Vertex.cpp
        MoonfinderRedone/classes/Vertex.h
        MoonfinderRedone/main.cpp)
