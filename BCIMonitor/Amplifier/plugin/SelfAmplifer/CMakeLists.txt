cmake_minimum_required(VERSION 3.5)

project(SelfAmplifer LANGUAGES CXX C)

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

find_package(Qt5 COMPONENTS Core widgets serialport  network REQUIRED)

#add_subdirectory(test)


file(GLOB src "src/*")
file(GLOB Communication "src/Communication/*")
file(GLOB Protocols "src/Protocols/*")
#add_library(${PROJECT_NAME}  ${src} ${Communication} ${Protocols})
add_library(${PROJECT_NAME}  SHARED ${src} ${Communication} ${Protocols})
target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Core Qt5::Widgets Qt5::SerialPort Qt5::Network)

target_include_directories(${PROJECT_NAME} PUBLIC "src")

