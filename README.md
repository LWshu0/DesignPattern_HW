# 注意: 本项目是软件工程课程的个人作业, 截至 2024年6月12日

如有问题请联系我 eastwind10274@163.com

# 构建方法

1. 修改根目录下的 CMakeLists.txt 中编译器路径为自己的编译器路径, 即
   ```
    set (CMAKE_C_COMPILER "D:/compliers/mingw64_posix_seh/bin/gcc.exe")
    set (CMAKE_CXX_COMPILER "D:/compliers/mingw64_posix_seh/bin/g++.exe")
   ```

2. 运行根目录下的 make_build.bat 脚本, 将在 build 目录中构建项目, 生成的可执行文件位于 run/bin 中

# 文件说明

Design Pattern 习题.md 为作业说明

design.md 为设计文档

Result.png 为作业要求的截图