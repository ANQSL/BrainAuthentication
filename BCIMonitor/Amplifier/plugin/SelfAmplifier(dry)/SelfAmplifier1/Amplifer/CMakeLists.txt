cmake_minimum_required(VERSION 3.5)

project(Amplifer LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

##添加测试
add_subdirectory(test)
enable_testing()
##修改MSVC的编码
add_compile_options("/source-charset:utf-8")
add_compile_options("/execution-charset:utf-8")

find_package(Qt5 COMPONENTS  Core widgets  serialport REQUIRED)

file(GLOB SRC "src/*" )
file(GLOB private "src/private/*")
add_library(${PROJECT_NAME}  ${SRC} ${private})

target_link_libraries(Amplifer  Qt5::Widgets Qt5::SerialPort)

target_include_directories(Amplifer PUBLIC "src")
target_include_directories(Amplifer PRIVATE "src/private")

