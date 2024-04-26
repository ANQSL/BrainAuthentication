cmake_minimum_required(VERSION 3.5)

project(DataCommunicate_test LANGUAGES CXX)

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

find_package(Qt5 COMPONENTS Core widgets  REQUIRED)

add_executable(DataCommunicate_test  main.cpp)

target_link_libraries(DataCommunicate_test PRIVATE Qt5::Widgets DataCommunicate)

target_compile_definitions(DataCommunicate_test PRIVATE RESULTWIDGET_LIBRARY)
