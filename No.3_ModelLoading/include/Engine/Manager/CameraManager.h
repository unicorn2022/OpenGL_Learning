#pragma once
#include "Engine/Basic/Camera.h"
    
class CameraManager {
public:
    static CameraManager& GetInstance(){
        static CameraManager instance;
        return instance;
    }

private:
    CameraManager() {
        main_camera = new RoamingCameraPerspective(
            SCR_WIDTH / SCR_HEIGHT,         // 宽高比
            glm::vec3(0.0f, 9.0f, 26.0f),   // 位置
            glm::vec3(0.0f, 1.0f, 0.0f),    // 向上方向
            -90.0f,                         // 偏航角
            0.0f,                           // 俯仰角
            45.0f,                          // 视野, 0~90°
            0.1f,                           // 近平面距离
            100.0f                          // 远平面距离
        );
    }
    ~CameraManager(){
        delete main_camera;
    }

public:
    void HandleKeyBoard(GLFWwindow* window, float delta_time) {
        if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
            main_camera->ProcessKeyboard(CameraMovement::UP, delta_time);
        }
        if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
            main_camera->ProcessKeyboard(CameraMovement::DOWN, delta_time);
        }
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
            main_camera->ProcessKeyboard(CameraMovement::LEFT, delta_time);
        }
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
            main_camera->ProcessKeyboard(CameraMovement::RIGHT, delta_time);
        }
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
            main_camera->ProcessKeyboard(CameraMovement::FORWARD, delta_time);
        }
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
            main_camera->ProcessKeyboard(CameraMovement::BACKWARD, delta_time);
        }
    }
    
    void HandleMouseMovement(float x_offset, float y_offset) {
        main_camera->ProcessMouseMovement(x_offset, y_offset);
    }
    
    void HandleMouseScroll(float y_offset) {
        main_camera->ProcessMouseScroll(y_offset);
    }

public:
    RoamingCamera* main_camera;
};