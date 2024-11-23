cmake_minimum_required(VERSION 3.27)
project(MedicalAnalysis)

set(CMAKE_CXX_STANDARD 17)

add_executable(MedicalAnalysis main.cpp
        MedicalAnalysis.h
        BMI.cpp
        BMI.h
        BP.cpp
        BP.h
        UI.cpp
        UI.h
        Person.cpp
        Person.h)
