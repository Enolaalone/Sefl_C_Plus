cmake_minimum_required(VERSION 3.27)
project(MineSweeperEX)

set(CMAKE_CXX_STANDARD 20)

include_directories(./EasyX/include)
link_directories(./EasyX/lib64)
link_libraries(libeasyx.a)

file(GLOB SOURCE_FILES "*.cpp")
file(GLOB HEADER_FILES "*.h")

add_executable(MineSweeper ${SOURCE_FILES} ${HEADER_FILES})
