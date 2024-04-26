cmake_minimum_required(VERSION 3.10.0)
project(amplifer_test)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Core REQUIRED)

add_executable(amplifer_test main.cpp)
target_link_libraries(amplifer_test Qt5::Core Amplifer)
