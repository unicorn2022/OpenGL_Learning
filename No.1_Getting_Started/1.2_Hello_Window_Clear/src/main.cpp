#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

static const int width = 800;
static const int height = 600;

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

int main() {
    /* 初始化窗口, 设置窗口属性 */
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* 创建窗口对象 */
    GLFWwindow* window = glfwCreateWindow(width, height, "LearnOpenGL", NULL, NULL);
    if (window == NULL) {
        std::cout << "创建GLFW窗口对象失败\n";
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    /* 初始化GLAD */
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "初始化GLAD失败\n";
        return -1;
    }

    /* 设置视口大小, 注册回调函数 */
    glViewport(0, 0, width, height);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    /* 渲染循环 */
    while (!glfwWindowShouldClose(window)) {
        // 处理输入
        processInput(window);
        // 渲染指令
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        // 检查并调用事件, 交换缓存
        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    /* 程序结束 */
    glfwTerminate();
    return 0;
}