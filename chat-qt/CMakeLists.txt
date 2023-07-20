cmake_minimum_required(VERSION 3.25)
project(chat_qt)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 COMPONENTS
        Core
        WebSockets
        Gui
        Widgets
        REQUIRED)
find_package(spdlog REQUIRED)

add_executable(chat_qt
        mainwindow.ui mainwindow.cpp mainwindow.h
        connectdialog.ui connectdialog.cpp connectdialog.h
        main.cpp WsClient.h WsClient.cpp)

target_link_libraries(chat_qt
        Qt5::Core
        Qt5::WebSockets
        Qt5::Gui
        Qt5::Widgets
        spdlog::spdlog
        )

