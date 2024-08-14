cmake_minimum_required(VERSION 3.10)

project(BrainAuthentication LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(Qt5_DIR "D:\\Qt\\Qt5.14.2\\5.14.2\\msvc2017_64\\lib\\cmake\\Qt5")
##修改MSVC的编码
if(MSVC)
    add_compile_options("/source-charset:utf-8")
    add_compile_options("/execution-charset:utf-8")
endif()

#添加模块
add_subdirectory(BCIMonitor)
add_subdirectory(DataProcess)
add_subdirectory(ControlFly)
add_subdirectory(SSVEPWidget)
add_subdirectory(CustomMessageHandler)
add_subdirectory(CalculateTest)
add_subdirectory(AuthorityManage)
add_subdirectory(BCIIA)

find_package(Qt5 COMPONENTS Core Widgets REQUIRED)
file(COPY ${CURVE_RES} DESTINATION "res")
## 添加mat库
file(COPY ${MAT_DLL} DESTINATION ".")
#message("${MonitorRes}")
# 添加数据库
file(COPY ${sql} DESTINATION "sql")

#添加onnruntime动态库
file(COPY ${onnxruntime_DLL} DESTINATION ".")

#添加ffmepg库

file(COPY ${FFMPEG_DLL} DESTINATION ".")

file(GLOB SRC "src/*")
file(GLOB Login_SRC "src/Login/src/*")

add_executable(${PROJECT_NAME}  main.cpp ${SRC} ${Login_SRC} ${MonitorRes} ${AmpliferRes} "src/Login/src/login.h")
target_link_libraries(${PROJECT_NAME} Qt5::Core  Qt5::Widgets)
target_link_libraries(${PROJECT_NAME}  BCIMonitor  DataProcess ControlFly SSVEPWidget
                      CustomMessageHandler CalculateTest AuthorityManage Calculate)

target_include_directories(${PROJECT_NAME} PUBLIC src)
target_include_directories(${PROJECT_NAME} PUBLIC src/Login/src)
