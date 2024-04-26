cmake_minimum_required(VERSION 3.5)

project(BrainHeartEye14_test LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


find_package(Qt5 COMPONENTS Core widgets REQUIRED)

file(GLOB src "src/*")
add_executable(${PROJECT_NAME}   main.cpp  ${src})

target_link_libraries(${PROJECT_NAME} PRIVATE  Qt5::Widgets Qt5::SerialPort BrainHeartEye14)

target_compile_definitions(${PROJECT_NAME} PRIVATE BPAMPLIFIER_LIBRARY)

target_include_directories(${PROJECT_NAME} PUBLIC "src")
