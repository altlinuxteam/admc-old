cmake_minimum_required (VERSION 2.8.8)
project (ADMC)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set (SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.ui
        resources.qrc
    )

add_executable(admc ${SOURCES})

find_package(Qt5Widgets REQUIRED)
target_link_libraries(admc Qt5::Widgets)
