cmake_minimum_required(VERSION 3.5)

project(AwesomeQtSnake VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 REQUIRED COMPONENTS Core Widgets Test)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Widgets Test)

qt_standard_project_setup()

# include projects
add_subdirectory(src/snakecore)
add_subdirectory(src/widgetapp)

#include tests
enable_testing()
add_subdirectory(tests/auto/snakecore)

