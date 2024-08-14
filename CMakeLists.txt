cmake_minimum_required(VERSION 3.5)

project(BrainAuthentication LANGUAGES CXX)

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

#添加模块
add_subdirectory(BCIMonitor)
add_subdirectory(DataProcess)
add_subdirectory(ControlFly)
add_subdirectory(SSVEPWidget)
add_subdirectory(CustomMessageHandler)
add_subdirectory(CalculateTest)
add_subdirectory(AuthorityManage)
add_subdirectory(BCIIA)

find_package(Qt5 COMPONENTS Widgets REQUIRED)
file(COPY ${CURVE_RES} DESTINATION "res")
## 添加mat库
file(COPY ${MATDLL} DESTINATION ".")
#message("${MonitorRes}")
# 添加数据库
file(COPY ${sql} DESTINATION "sql")
file(COPY ${onnxruntime_DLL} DESTINATION ".")
file(GLOB SRC "src/*")
#添加onnruntime动态库
file(COPY ${onnxruntime_DLL} DESTINATION .)

#添加ffmepg库
file(COPY ${FFMPEGDLL} DESTINATION .)

add_executable(${PROJECT_NAME} WIN32 main.cpp ${SRC}  ${MonitorRes} ${AmpliferRes})
target_link_libraries(${PROJECT_NAME}  Qt5::Widgets)
target_link_libraries(${PROJECT_NAME}  BCIMonitor  DataProcess ControlFly SSVEPWidget
                      CustomMessageHandler CalculateTest AuthorityManage Calculate)

target_include_directories(${PROJECT_NAME} PUBLIC src)
