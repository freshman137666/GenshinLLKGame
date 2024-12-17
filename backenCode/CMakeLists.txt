cmake_minimum_required(VERSION 3.10)

# 项目信息
project(genshen2)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 查找源文件
file(GLOB SOURCES
   ${PROJECT_SOURCE_DIR}/src/*.cpp 
)

include_directories(${PROJECT_SOURCE_DIR}/external/mysql/include)
include_directories(${PROJECT_SOURCE_DIR}/external/httplib)
include_directories(${PROJECT_SOURCE_DIR}/src)
include_directories(${PROJECT_SOURCE_DIR}/external/json/include)
link_directories(${PROJECT_SOURCE_DIR}/external/mysql/lib)


# 添加可执行文件
add_executable(genshen2 ${SOURCES})

# 链接库
target_link_libraries(genshen2 mysql ws2_32
)