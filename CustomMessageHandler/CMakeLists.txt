cmake_minimum_required(VERSION 3.5)

project(CustomMessageHandler LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
##修改MSVC的编码
if(MSVC)
    add_compile_options("/source-charset:utf-8")
    add_compile_options("/execution-charset:utf-8")
endif()
add_subdirectory(Log)
add_subdirectory(test)
find_package(Qt5 COMPONENTS Core REQUIRED)
file(GLOB src "src/*")
add_library(CustomMessageHandler ${src})

target_link_libraries(CustomMessageHandler PUBLIC Qt5::Core Log)

target_compile_definitions(CustomMessageHandler PRIVATE SSVEP_LIBRARY)
target_include_directories(CustomMessageHandler PUBLIC "src")
