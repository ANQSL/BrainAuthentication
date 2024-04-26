cmake_minimum_required(VERSION 3.5)

project(mat LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#if(${CMAKE_BUILD_TYPE} STREQUAL "Release")
#    set(EXECUTABLE_OUTPUT_PATH "../../../build/release")
#else()
#    set(EXECUTABLE_OUTPUT_PATH "../../../build/debug")
#endif()
find_package(Qt5 COMPONENTS Core concurrent REQUIRED)

if(MSVC)
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

file(GLOB src "src/*")
file(COPY ${MATDLL} DESTINATION ".")
add_executable(mat ${src}
  main.cpp
)
target_link_libraries(mat Qt5::Core Qt5::Concurrent ${MATLIB})
target_include_directories(mat PRIVATE "src" ${MATINCLUDE})
