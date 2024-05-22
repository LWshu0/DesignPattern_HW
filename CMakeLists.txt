# 指定编译器
set (CMAKE_C_COMPILER "D:/compliers/mingw64_posix_seh/bin/gcc.exe")
set (CMAKE_CXX_COMPILER "D:/compliers/mingw64_posix_seh/bin/g++.exe")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# 设置编译器选项
# set(CMAKE_CXX_FLAGS   "")  
# set(CMAKE_C_FLAGS   "")  

# cmake 最低版本
cmake_minimum_required(VERSION 3.27)
# 项目名称
project(Funny_Json_Explorer)

# 定义路径
get_filename_component(PROJECT_DIR ${CMAKE_CURRENT_LIST_FILE} DIRECTORY)
set(INCLUDE_DIR ${PROJECT_DIR}/include)
set(RUN_DIR ${PROJECT_DIR}/run)
# 源文件路径
set(PROJECT_SOURCE_DIR ${PROJECT_DIR}/src)
# 可执行文件输出位置
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${RUN_DIR}/bin)
# 动态库输出位置
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${RUN_DIR}/bin)
# 静态库输出位置
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${RUN_DIR}/lib)

# 指明所有头文件路径
include_directories(${INCLUDE_DIR})
# 链接库文件
link_directories(${RUN_DIR}/lib
                 ${RUN_DIR}/bin)

add_subdirectory(
    ${PROJECT_SOURCE_DIR}
)