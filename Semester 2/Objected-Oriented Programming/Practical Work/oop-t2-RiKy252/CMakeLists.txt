cmake_minimum_required(VERSION 3.27)
project(oop_t2_RiKy252)

set(CMAKE_CXX_STANDARD 14)

add_executable(oop_t2_RiKy252
        test.cpp
        Engine.h
        Engine.cpp
        ElectricEngine.h
        ElectricEngine.cpp
        TurboEngine.h
        TurboEngine.cpp
        Car.h
        Car.cpp
        Service.h
        Service.cpp
        UI.h
        UI.cpp
)
