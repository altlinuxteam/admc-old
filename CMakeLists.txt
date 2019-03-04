cmake_minimum_required (VERSION 2.8.8)
project (ADMC)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC_SEARCH_PATHS ui)

set (SOURCES
        main.cpp
        common.h
        mainwindow.h
        mainwindow.cpp
        connector.h
        connector.cpp
        objectdata.h
        objectdata.cpp
        ldapconnection.h
        ldapconnection.cpp
        ldapobject.h
        ldapobject.cpp
        ldapobjectmodel.h
        ldapobjectmodel.cpp
        ldaptablemodel.h
        ldaptablemodel.cpp
        ui/mainwindow.ui
        ui/userproperties.ui
        resources.qrc
    )

add_executable(admc ${SOURCES})

find_package(Qt5Widgets REQUIRED)
target_link_libraries(admc Qt5::Widgets)
