cmake_minimum_required(VERSION 3.5)

project(Plotting VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)


set(PROJECT_SOURCES
        src/main.cpp
        include/mainwindow.cpp
        include/mainwindow.h
        include/mainwindow.ui
        include/exprtk.hpp
        include/header.hpp
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(Plotting
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
else()
    if(ANDROID)
        add_library(Plotting SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(Plotting
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(Plotting PRIVATE Qt${QT_VERSION_MAJOR}::Widgets sfml-graphics sfml-audio)

set_target_properties(Plotting PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS Plotting
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(Plotting)
endif()
