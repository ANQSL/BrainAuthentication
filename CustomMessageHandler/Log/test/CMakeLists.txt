cmake_minimum_required(VERSION 3.5)

project(Log_test LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Core REQUIRED)


add_executable(Log_test main.cpp)

target_link_libraries(Log_test PRIVATE Qt5::Core Log)

target_compile_definitions(Log_test PRIVATE DATAPROCESS_LIBRARY)
