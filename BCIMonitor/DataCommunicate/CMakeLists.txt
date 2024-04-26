cmake_minimum_required(VERSION 3.5)

project(DataCommunicate LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
if(MSVC)
    add_compile_options("/source-charset:utf-8")
    add_compile_options("/execution-charset:utf-8")
endif()
add_subdirectory(test)

find_package(Qt5 COMPONENTS Core network  REQUIRED)

file(GLOB src "src/*")
add_library(DataCommunicate  ${src})

target_link_libraries(DataCommunicate  Qt5::Core Qt5::Network )

target_compile_definitions(DataCommunicate PRIVATE RESULTWIDGET_LIBRARY)

target_include_directories(DataCommunicate PUBLIC "src")
