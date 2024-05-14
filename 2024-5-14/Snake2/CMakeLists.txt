cmake_minimum_required(VERSION 3.27)
project(Snake2)

set(CMAKE_CXX_STANDARD 20)

#动态库配置
include_directories(./EasyX/include)
link_directories(./EasyX/lib64)
link_libraries(libeasyx.a)

# 添加头文件目录
include_directories(Inc)

#搜索源文件
file(GLOB SOURCE_FILES "Src/*.cpp")
#配置源文件
add_executable(Snake ${SOURCE_FILES} )
#静态构建库
set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")