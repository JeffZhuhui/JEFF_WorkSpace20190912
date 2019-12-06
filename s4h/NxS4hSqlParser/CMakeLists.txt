cmake_minimum_required(VERSION 3.14)
project(S4H_Test)

set(CMAKE_CXX_STANDARD 14)

include_directories(../tool)

add_executable(S4H_Test ../tool/file_opr_tool.cpp
        NXSFHLex.cpp
        main.cpp)