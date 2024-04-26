cmake_minimum_required(VERSION 3.5)

project(BPAmplifier_test LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


find_package(Qt5 COMPONENTS Core  widgets REQUIRED)

## 添加BP文件
file(GLOB src "src/*")


add_executable(${PROJECT_NAME} ${src} ../res/res.qrc)

target_link_libraries(${PROJECT_NAME}  Qt5::Core Qt5::Widgets BPAmplifier)


