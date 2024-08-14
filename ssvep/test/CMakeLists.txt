cmake_minimum_required(VERSION 3.5)

project(ssvep_test LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Core Widgets REQUIRED)

add_executable(ssvep_test WIN32 main.cpp)

target_link_libraries(ssvep_test PRIVATE Qt5::Core Qt5::Widgets ssvep)

target_compile_definitions(ssvep_test PRIVATE SSVEP_LIBRARY)
