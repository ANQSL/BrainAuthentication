cmake_minimum_required(VERSION 3.5)

project(DataProcess LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Core REQUIRED)
include_directories(DSPFilter/include)
add_subdirectory(test)
file(GLOB filterSrc "DSPFilter/source/*.cpp")
file(GLOB src "src/*")
add_library(DataProcess ${src} ${filterSrc})

target_link_libraries(DataProcess PRIVATE Qt5::Core)

target_compile_definitions(DataProcess PRIVATE DATAPROCESS_LIBRARY)

target_include_directories(DataProcess PUBLIC "src")
target_include_directories(DataProcess PRIVATE "DSPFilter/include")
