cmake_minimum_required(VERSION 3.5)

project(SSVEPWidget LANGUAGES CXX)

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
add_subdirectory(test)
find_package(Qt5 COMPONENTS Core widgets REQUIRED)
file(GLOB src "src/*")
add_library(SSVEPWidget ${src})

target_link_libraries(SSVEPWidget PUBLIC Qt5::Core Qt5::Widgets)

target_compile_definitions(SSVEPWidget PRIVATE SSVEP_LIBRARY)
target_include_directories(SSVEPWidget PUBLIC "src")
