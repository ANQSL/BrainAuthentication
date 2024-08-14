cmake_minimum_required(VERSION 3.5)

project(ControlFly LANGUAGES CXX)

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
find_package(Qt5 COMPONENTS Core network widgets REQUIRED)
file(GLOB src "src/*")


#添加ffmpeg库
#添加头文件
include_directories("D:/C++/ffmpeg/include")
if(CMAKE_CL_64)
    #静态库路径
    file(GLOB FFMPEGLIB "D:/C++/ffmpeg/lib/*.lib")
    file(GLOB FFMPEGDLL "D:/C++/ffmpeg/bin/*.dll")
    set(FFMPEGDLL ${FFMPEGDLL} CACHE PATH "dll of ffmpeg")
endif()
add_library(ControlFly ${src})

#target_link_libraries(ControlFly PRIVATE ${FFMPEGLIB})
target_link_libraries(ControlFly PUBLIC Qt5::Core Qt5::Network Qt5::Widgets ${FFMPEGLIB})

target_include_directories(ControlFly PUBLIC "src")
