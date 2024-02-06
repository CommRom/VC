cmake_minimum_required(VERSION 3.26)
project(VC)

set(CMAKE_CXX_STANDARD 20)

add_executable(VC main.cpp
        BigNumber.h
        BigNumbersCode.cpp)
