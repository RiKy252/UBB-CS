cmake_minimum_required(VERSION 3.27)
project(CLion_DSA)

set(CMAKE_CXX_STANDARD 17)

add_executable(CLion_DSA
        Matrix.h
        Matrix.cpp
        App.cpp
        ExtendedTest.h
        ExtendedTest.cpp
        ShortTest.h
        ShortTest.cpp)
