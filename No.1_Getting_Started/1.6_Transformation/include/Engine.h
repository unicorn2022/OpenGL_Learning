#pragma once
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Engine/Basic/INCLUDE_ALL.h"
#include "Engine/Manager/INCLUDE_ALL.h"
#include "Engine/Object/INCLUDE_ALL.h"

static const int SCR_WIDTH = 800;
static const int SCR_HEIGHT = 800;
static const char* SCR_NAME = "LearnOpenGL";


void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
}

void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
    /* ↑增加mix_rate */
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
        float mix_rate = GlobalValue::GetInstance().GetValue("mix_rate");
        mix_rate += 0.01;
        GlobalValue::GetInstance().SetValue("mix_rate", mix_rate, 0.0, 1.0);
    }
    /* ↓减少mix_rate */
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
        float mix_rate = GlobalValue::GetInstance().GetValue("mix_rate");
        mix_rate -= 0.01;
        GlobalValue::GetInstance().SetValue("mix_rate", mix_rate, 0.0, 1.0);
    }
}

class Engine {
public:
    Engine() {
        /* 初始化窗口, 设置窗口属性 */
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        /* 创建窗口对象 */
        window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, SCR_NAME, NULL, NULL);
        if (window == NULL) {
            std::cout << "[ERROR::Engine.h::Engine()] 创建GLFW窗口对象失败\n";
            glfwTerminate();
            exit(-1);
        }
        glfwMakeContextCurrent(window);

        /* 初始化GLAD */
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
            std::cout << "[ERROR::Engine.h::Engine()] 初始化GLAD失败\n";
            exit(-1);
        }

        /* 设置视口大小, 注册回调函数 */
        glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
        glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

        /* 创建物体, 着色器程序 */
        shader_manager = new ShaderManager();
        texture_manager = new TextureManager();
        object_manager = new ObjectManager(shader_manager, texture_manager);
    }

    ~Engine() {
        glfwTerminate();
        delete shader_manager;
    }

public:
    void Run() {
        /* 渲染循环 */
        while (!glfwWindowShouldClose(window)) {
            /* 处理输入 */ 
            processInput(window);
            /* 渲染指令 */ 
            // 清屏
            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);
            // 绘制物体
            object_manager->DrawAll();
            /* 检查并调用事件, 交换缓存 */
            glfwPollEvents();
            glfwSwapBuffers(window);
        }
    }

private:
    /* GLFW 窗口对象 */
    GLFWwindow* window;
    /* 资产管理 */
    ShaderManager* shader_manager;
    ObjectManager* object_manager;
    TextureManager* texture_manager;
};