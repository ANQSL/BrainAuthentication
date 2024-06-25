cmake_minimum_required(VERSION 3.5)

project(AuthorityManage LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(MSVC)
    add_compile_options("/source-charset:utf-8")
    add_compile_options("/execution-charset:utf-8")
endif()
find_package(Qt5 COMPONENTS Core  sql  widgets REQUIRED)

add_subdirectory(test)
file(GLOB src "src/*")
file(GLOB sql "sql/*.sql")
set(sql ${sql} CACHE PATH "init database")
add_library(AuthorityManage ${src})
target_link_libraries(AuthorityManage  Qt5::Core Qt5::Widgets Qt5::Sql )

target_compile_definitions(AuthorityManage PRIVATE AUTHORITYMANAGE_LIBRARY)

target_include_directories(AuthorityManage PUBLIC "src" )
