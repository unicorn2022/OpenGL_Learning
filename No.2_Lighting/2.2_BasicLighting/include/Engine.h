#pragma once
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Engine/Basic/INCLUDE_ALL.h"
#include "Engine/Object/INCLUDE_ALL.h"
#include "Engine/Manager/INCLUDE_ALL.h"`

static const char* SCR_NAME = "LearnOpenGL";
static const int SCR_WIDTH = 800;
static const int SCR_HEIGHT = 800;
static const glm::vec4 SCR_BACKGROUND = glm::vec4(0.2f, 0.3f, 0.3f, 1.0f);


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
        delete shader_manager;
    }

public:
    void Run() {
        /* 1. 创建 manager */
        shader_manager = new ShaderManager();
        texture_manager = new TextureManager();
        light_manager = new LightManager();
        object_manager = new ObjectManager(shader_manager, texture_manager, light_manager);
        camera_manager = new CameraManager(SCR_WIDTH, SCR_HEIGHT);

        /* 2. 启动深度测试 */
        glEnable(GL_DEPTH_TEST);

        /* 3. 渲染循环 */
        while (!glfwWindowShouldClose(window)) {
            /* 3.0 预处理 */
            float current_time = glfwGetTime();
            delta_time = current_time - last_time;
            last_time = current_time;

            /* 3.1 处理输入 */ 
            keyboard_callback(window);
            object_manager->GameTick();
            
            /* 3.2 渲染指令 */ 
            // 清屏
            glClearColor(SCR_BACKGROUND.x, SCR_BACKGROUND.y, SCR_BACKGROUND.z, SCR_BACKGROUND.w);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            // 绘制物体
            object_manager->RenderTick(camera_manager, light_manager);
            
            /* 3.3 检查并调用事件, 交换缓存 */
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
    }

public:
    /* GLFW 窗口对象 */
    GLFWwindow* window;
    /* 资产管理 */
    ShaderManager* shader_manager;
    TextureManager* texture_manager;
    LightManager* light_manager;
    ObjectManager* object_manager;
    CameraManager* camera_manager;
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
    
    Engine::GetInstance().camera_manager->HandleKeyBoard(window, Engine::GetInstance().delta_time);
    Engine::GetInstance().object_manager->HandleInput(window);
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
    Engine::GetInstance().camera_manager->HandleMouseMovement(x_offset, y_offset);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
    Engine::GetInstance().camera_manager->HandleMouseScroll(yoffset);
}