cmake_minimum_required(VERSION 3.27)
#project(HKpaper C)
project(StrDef )

#set(CMAKE_C_STANDARD 11)

set(CMAKE_CXX_STANDARD 17)
# 找到当前目录下的所有C源文件
file(GLOB SRC_FILES "*.cpp")

# 为每个源文件创建一个可执行文件
foreach(SOURCE_FILE ${SRC_FILES})
    get_filename_component(FILE_NAME ${SOURCE_FILE} NAME_WE)
    add_executable(${FILE_NAME} ${SOURCE_FILE})
endforeach()