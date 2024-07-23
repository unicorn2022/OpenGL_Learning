cmake_minimum_required(VERSION 3.23)
set(OpenGL_Root_Path E:/MyProject/GameEngine/OpenGL_Learning/3rd-party/)
# 项目名称
project(Hello_Window_Clear)
# C++标准
set(CMAKE_CXX_STANDARD 20)
# 可执行文件输出路径
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
# 头文件路径
include_directories(
    ${OpenGL_Root_Path}/glfw-3.4/include
    ${OpenGL_Root_Path}/glad/include
    ${PROJECT_SOURCE_DIR}/include
)
# 库文件路径
link_directories(
    ${OpenGL_Root_Path}/glfw-3.4/lib
)
# 可执行文件
add_executable(Hello_Window_Clear 
    ${OpenGL_Root_Path}/glad/src/glad.c
    ${PROJECT_SOURCE_DIR}/src/main.cpp
)
# 库文件名称
target_link_libraries(Hello_Window_Clear glfw3)