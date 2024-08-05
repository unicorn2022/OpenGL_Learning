#pragma once
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Utils.h"
#include "Engine/Basic/INCLUDE_ALL.h"
#include "Engine/Object/INCLUDE_ALL.h"
#include "Engine/Manager/INCLUDE_ALL.h"
#include "Engine/Material/INCLUDE_ALL.h"
#include "Engine/Light/INCLUDE_ALL.h"


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void keyboard_callback(GLFWwindow* window);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);


class Engine {
public:
    static Engine& GetInstance(){
        static Engine instance;
        return instance;
    }

private:
    Engine() {
        InitOpenGL();
    }

    ~Engine() {
        glfwTerminate();
    }

public:
    void Run() {
        /* 1. 启动深度测试、模板测试 */
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);
        glEnable(GL_STENCIL_TEST);
        glStencilFunc(GL_NOTEQUAL, 1, 0xff);
        glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE); // 通过模板&深度测试时, 将模板值设置为 glStencilFunc 指定的 ref 值
            
        /* 2. 渲染循环 */
        while (!glfwWindowShouldClose(window)) {
            /* 2.0 预处理 */
            float current_time = glfwGetTime();
            delta_time = current_time - last_time;
            last_time = current_time;

            /* 2.1 处理输入 */ 
            keyboard_callback(window);
            ObjectManager::GetInstance().GameTick();
            
            /* 2.2 渲染指令 */ 
            // 2.2.1 清屏: 颜色缓冲, 深度缓冲, 模板缓冲
            glClearColor(COLOR_BACKGROUND.x, COLOR_BACKGROUND.y, COLOR_BACKGROUND.z, COLOR_BACKGROUND.w);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
            // 2.2.2 绘制物体(1): 更新模板缓冲
            glStencilFunc(GL_ALWAYS, 1, 0xff); 
            glStencilMask(0xff); // 更新模板值
            ObjectManager::GetInstance().RenderTick();
            // 2.2.3 绘制物体(2): 根据模板缓冲绘制边界
            glStencilFunc(GL_NOTEQUAL, 1, 0xff); // frag对应的模板值不为1时, 通过测试
            glStencilMask(0x00);        // 禁止更新模板值
            glDisable(GL_DEPTH_TEST);   // 禁止深度检测
            ObjectManager::GetInstance().RenderTick(MaterialManager::GetInstance().border_material);
            glStencilMask(0xff);
            glStencilFunc(GL_ALWAYS, 0, 0xff);
            glEnable(GL_DEPTH_TEST);
            
            /* 2.3 检查并调用事件, 交换缓存 */
            glfwPollEvents();
            glfwSwapBuffers(window);
        }
    }
    
private:
    void InitOpenGL(){
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
        glfwSetCursorPosCallback(window, mouse_callback);
        glfwSetScrollCallback(window, scroll_callback);

        /* 设置鼠标捕捉 */
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    
        /* 检查扩展是否支持 */
        const std::string extension_name[1] = {"GL_ARB_shading_language_include" };
        GLint n;
        glGetIntegerv(GL_NUM_EXTENSIONS, &n);
        std::cout << "支持的扩展总数: " << n << "\n";
        for(int i = 0; i < n; i++){
            std::string extension = (char*)glGetStringi(GL_EXTENSIONS, i);
            for (auto name : extension_name) {
                if (extension == name) {
                    std::cout << "支持扩展: " << name << std::endl;
                }
            }
        }
    }

public:
    /* GLFW 窗口对象 */
    GLFWwindow* window;
    /* 帧时间 */
    float last_time = 0.0f;
    float delta_time = 0.0f;
    /* 鼠标灵敏度 */
    float mouse_sensitivity = 0.05f;
};


void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
}

void keyboard_callback(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
    
    CameraManager::GetInstance().HandleKeyBoard(window, Engine::GetInstance().delta_time);
    ObjectManager::GetInstance().HandleInput(window);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
    static bool first_mouse = true;
    static float x_last = 0.0f, y_last = 0.0f;

    if (first_mouse) {
        x_last = xpos;
        y_last = ypos;
        first_mouse = false;
    }

    float x_offset = (xpos - x_last) * Engine::GetInstance().mouse_sensitivity;
    float y_offset = (y_last - ypos) * Engine::GetInstance().mouse_sensitivity;
    x_last = xpos;
    y_last = ypos;
    CameraManager::GetInstance().HandleMouseMovement(x_offset, y_offset);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
    CameraManager::GetInstance().HandleMouseScroll(yoffset);
}