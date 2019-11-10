cmake_minimum_required(VERSION 3.1.0)

project(lamp)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin )

if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

find_package(Qt5 COMPONENTS Widgets Network REQUIRED)

add_executable(lamp
    mainwindow.ui
    mainwindow.h
    mainwindow.cpp
    main.cpp
    execobj.h 
    formcoloroperator.h
    formonoffexec.h
    formpaintexec.h
    execobj.cpp
    formcoloroperator.cpp
    formonoffexec.cpp
    formpaintexec.cpp 
)


foreach(plugin ${Qt5Network_PLUGINS})
  get_target_property(_loc ${plugin} LOCATION)
  message("Plugin ${plugin} is at location ${_loc}")
endforeach()


target_link_libraries(lamp Qt5::Widgets Qt5::Network)


