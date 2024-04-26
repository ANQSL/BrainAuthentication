cmake_minimum_required(VERSION 3.5)

project(FileAmplifier LANGUAGES CXX)

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
if(MSVC)
    if(CMAKE_CL_64)
        #matio包的位置设置
        if(${CMAKE_BUILD_TYPE} STREQUAL "Release")
            set(MATINCLUDE "matio/x64/release/include")
            file(GLOB MATLIB "matio/x64/release/lib/*.lib")
            file(GLOB MATDLL "matio/x64/release/bin/*.dll")
        else()
            set(MATINCLUDE "matio/x64/debug/include")
            file(GLOB MATLIB "matio/x64/debug/lib/*.lib")
            file(GLOB MATDLL "matio/x64/debug/bin/*.dll")
        endif()
    else()
        if(${CMAKE_BUILD_TYPE} STREQUAL "Release")
            set(MATINCLUDE "matio/x86/release/include")
            file(GLOB MATLIB "matio/x86/release/lib/*.lib")
            file(GLOB MATDLL "matio/x86/release/bin/*.dll")
        else()
            set(MATINCLUDE "matio/x86/debug/include")
            file(GLOB MATLIB "matio/x86/debug/lib/*.lib")
            file(GLOB MATDLL "matio/x86/debug/bin/*.dll")
        endif()
    endif()
    set(MATDLL ${MATDLL} CACHE PATH "path of TinyMat")
    include_directories(MATINCLUDE)
endif()


find_package(Qt5 COMPONENTS Core widgets  REQUIRED)

#add_subdirectory(test)

file(GLOB src "src/*")
add_library(${PROJECT_NAME}  SHARED ${src})
#add_library(${PROJECT_NAME}  ${src})

target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Core Qt5::Widgets ${MATLIB})

target_compile_definitions(${PROJECT_NAME} PRIVATE BPAMPLIFIER_LIBRARY)

target_include_directories(${PROJECT_NAME} PUBLIC "src")

target_include_directories(${PROJECT_NAME} PUBLIC "src" ${MATINCLUDE})
