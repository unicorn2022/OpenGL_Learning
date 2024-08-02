cmake_minimum_required(VERSION 3.23)
# 项目名称
project(MultipleLight)
# C++标准
set(CMAKE_CXX_STANDARD 11)

if(WIN32)
    add_compile_options(/wd4819)
endif()

# 根路径
set(OpenGL_Root_Path E:/MyProject/GameEngine/OpenGL_Learning/3rd-party/)
# 头文件路径
include_directories(
    ${OpenGL_Root_Path}
    ${OpenGL_Root_Path}/glfw-3.4/include
    ${OpenGL_Root_Path}/glad/include
    ${PROJECT_SOURCE_DIR}/include
)
# 库文件路径
link_directories(
    ${OpenGL_Root_Path}/glfw-3.4/lib
)
# 可执行文件
add_executable(MultipleLight 
    ${OpenGL_Root_Path}/glad/src/glad.c
    ${PROJECT_SOURCE_DIR}/src/main.cpp
)
# 库文件名称
target_link_libraries(MultipleLight glfw3)