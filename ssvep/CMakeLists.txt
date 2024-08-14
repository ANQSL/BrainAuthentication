cmake_minimum_required(VERSION 3.5)

project(ssvep LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(Qt5_DIR "D:\\Qt\\Qt5.14.2\\5.14.2\\msvc2017_64\\lib\\cmake\\Qt5")
##修改MSVC的编码
if(MSVC)
    add_compile_options("/source-charset:utf-8")
    add_compile_options("/execution-charset:utf-8")
endif()
find_package(Qt5 COMPONENTS Core Widgets network REQUIRED)
add_subdirectory(test)
File(GLOB src "src/*")
add_library(ssvep ${src} )

target_link_libraries(ssvep PUBLIC Qt5::Core Qt5::Widgets Qt5::Network)

target_compile_definitions(ssvep PRIVATE SSVEP_LIBRARY)
target_include_directories(ssvep PUBLIC "src")
