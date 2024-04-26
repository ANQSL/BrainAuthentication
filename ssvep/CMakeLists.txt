cmake_minimum_required(VERSION 3.5)

project(ssvep LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Core Widgets REQUIRED)
add_subdirectory(test)
File(GLOB src "src/*")
File(GLOB CCA "src/CCA/*")
add_library(ssvep ${src} ${CCA})

target_link_libraries(ssvep PRIVATE Qt5::Core Qt5::Widgets)

target_compile_definitions(ssvep PRIVATE SSVEP_LIBRARY)
target_include_directories(ssvep PUBLIC "src")
