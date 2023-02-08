cmake_minimum_required(VERSION 3.5)

project(notepad VERSION 0.1 LANGUAGES CXX)

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
        include/qt_window.h
        include/sfml_window.h
        include/qt_sfml_window.cpp
        include/exprtk.hpp
        include/mainwindow.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(notepad
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
else()
    if(ANDROID)
        add_library(notepad SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(notepad
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(notepad PRIVATE Qt${QT_VERSION_MAJOR}::Widgets sfml-graphics sfml-audio)

set_target_properties(notepad PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS notepad
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(notepad)
endif()
