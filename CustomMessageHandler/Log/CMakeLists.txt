cmake_minimum_required(VERSION 3.5)

project(Log LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Core REQUIRED)

add_subdirectory(test)

file(GLOB src "src/*")
add_library(Log ${src} )

target_link_libraries(Log PRIVATE Qt5::Core)

target_compile_definitions(Log PRIVATE DATAPROCESS_LIBRARY)

target_include_directories(Log PUBLIC "src")
