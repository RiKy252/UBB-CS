cmake_minimum_required(VERSION 3.27)
project(a8_9)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(Qt6_DIR "C:\\Qt\\6.7.0\\mingw_64\\lib\\cmake\\Qt6")

find_package(Qt6Widgets REQUIRED)

find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        Charts
        REQUIRED)

set(UI_FILES
        gui.ui
)

qt6_wrap_ui(WRAP_FILES gui.ui)

add_executable(a8_9
        AdminCSVRepo.cpp
        AdminCSVRepo.h
        CSVRepo.cpp
        CSVRepo.h
        domain.cpp
        domain.h
        FileException.h
        MenuException.h
        MovieException.h
        RepoException.h
        HTMLRepo.cpp
        HTMLRepo.h
        repo.cpp
        repo.h
        service.cpp
        service.h
        ui.cpp
        ui.h
        IntegerValidator.h
        MenuValidator.h
        MovieValidator.h
        RepoValidator.h
        App.cpp
        interface.cpp
        interface.h
        GUI.cpp
        GUI.h
        Action.h
        Action.h
        ActionAdd.cpp
        ActionAdd.h
        ActionRemove.cpp
        ActionRemove.h
        ActionUpdate.cpp
        ActionUpdate.h
        MovieTableModel.cpp
        MovieTableModel.h
        MovieTableView.cpp
        MovieTableView.h
)

target_link_libraries(a8_9
        Qt6::Core
        Qt6::Gui
        Qt6::Widgets
        Qt6::Charts
)

if (WIN32 AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    set(DEBUG_SUFFIX)
    if (MSVC AND CMAKE_BUILD_TYPE MATCHES "Debug")
        set(DEBUG_SUFFIX "d")
    endif ()
    set(QT_INSTALL_PATH "${CMAKE_PREFIX_PATH}")
    if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
        set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
            set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        endif ()
    endif ()
    if (EXISTS "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E make_directory
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
    endif ()
    foreach (QT_LIB Core Gui Widgets)
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/bin/Qt6${QT_LIB}${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>")
    endforeach (QT_LIB)
endif ()
