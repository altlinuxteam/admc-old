cmake_minimum_required (VERSION 2.8.8)
project (ADMC)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set (SOURCES
        main.cpp
        common.h
        mainwindow.h
        mainwindow.cpp
        objectdata.h
        objectdata.cpp
        ldapobject.h
        ldapobject.cpp
        ldapobjectmodel.h
        ldapobjectmodel.cpp
        mainwindow.ui
        resources.qrc
    )

add_executable(admc ${SOURCES})

find_library(LDB_LIBRARY NAMES ldb)

find_package(Qt5Widgets REQUIRED)
target_link_libraries(admc Qt5::Widgets ${LDB_LIBRARY})
