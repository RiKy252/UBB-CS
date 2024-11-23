cmake_minimum_required(VERSION 3.27)
project(L2_SMM)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(L2_SMM
        App.cpp
        ExtendedTest.cpp
        ExtendedTest.h
        ShortTest.cpp
        ShortTest.h
        SMMIterator.cpp
        SMMIterator.h
        SortedMultiMap.cpp
        SortedMultiMap.h)
