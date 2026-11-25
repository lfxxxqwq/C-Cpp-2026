cmake_minimum_required(VERSION 3.16)
project(gobang CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 五子棋：三个源文件一起编译链接成一个程序
add_executable(game AI.cpp play.cpp chess.cpp)

# AI 搜索较慢，开启优化
# -include graphics.h 让图形头文件最先加载，避开 chess.h 中 #define n 与系统头文件的宏冲突
# 这样 play.cpp 里的 #include <graphics.h> 可以保留，方便后续大改图形界面
target_compile_options(game PRIVATE -O2 -include graphics.h)

# 链接 EasyX 图形库（play.cpp 里用到 initgraph/circle 等绘图函数）
target_link_libraries(game PRIVATE easyx)
