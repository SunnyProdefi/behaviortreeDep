cmake_minimum_required(VERSION 3.5)
project(BehaviorTreeProject)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 17)

# 设置可执行文件的输出目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# 如果 BehaviorTree.CPP 库是全局安装的，并且你想要确保所有子项目都能找到它
find_package(behaviortree_cpp REQUIRED)

# 添加子目录，这样可以单独编译每个教程
add_subdirectory(tutorial_01)
add_subdirectory(tutorial_02)
add_subdirectory(tutorial_03)
add_subdirectory(tutorial_04)
add_subdirectory(tutorial_05)

# 可选：如果有全局的编译定义或链接需求，也可以在这里设置

