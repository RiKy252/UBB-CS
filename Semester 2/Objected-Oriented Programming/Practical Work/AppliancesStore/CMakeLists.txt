cmake_minimum_required(VERSION 3.27)
project(AppliancesStore)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_PREFIX_PATH "C:\\Qt\\6.7.0\\mingw_64\\lib\\cmake")

find_package(Qt5Widgets REQUIRED)

add_executable(AppliancesStore main.cpp
        Appliance.cpp
        Appliance.h
        Service.cpp
        Service.h
        Refrigerator.cpp
        Refrigerator.h
        WashingMachine.cpp
        WashingMachine.h
        UI.cpp
        UI.h)

target_link_libraries(AppliancesStore Qt5::Widgets)
