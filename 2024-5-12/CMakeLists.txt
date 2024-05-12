cmake_minimum_required(VERSION 3.27)
project(MineSweeperEX3)

set(CMAKE_CXX_STANDARD 20)

#EasyX库
include_directories(./EasyX/include)
link_directories(./EasyX/lib64)
link_libraries(libeasyx.a)

# 添加头文件目录
include_directories(Inc)

#搜索源文件
file(GLOB SOURCE_FILES "Src/*.cpp")

#构建项目
add_executable(MineSweeper ${SOURCE_FILES})

#静态链接库
set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")

