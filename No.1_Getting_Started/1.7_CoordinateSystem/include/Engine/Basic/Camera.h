#pragma once

#include "Engine/Basic/Utils.h"
#include "Engine/Basic/Shader.h"

class Camera{
public:
    Camera() {
        view_transform = glm::mat4(1.0f);
        view_transform = glm::translate(view_transform, glm::vec3(0, 0, -3));
    }
    ~Camera(){}

public:
    void Use(Shader* shader, std::string view_name, std::string projection_name) {
        shader->SetUniform(view_name, view_transform);
        shader->SetUniform(projection_name, projection_transform);
    }

protected:
    glm::mat4 view_transform;
    glm::mat4 projection_transform;
};

class CameraPerspective : public Camera {
public:
    /** 透视投影相机
     * \param aspect 宽高比
     * \param fov 视野, 0~90°
     * \param near 近平面距离
     * \param far 远平面距离
     */
    CameraPerspective(float aspect, float fov = 45.0f, float near = 0.1f, float far = 100.0f) {
        this->aspect = aspect;
        this->fov = fov;
        this->near = near;
        this->far = far;
        this->projection_transform = glm::perspective(glm::radians(fov), aspect, near, far);
    }

private:
    float aspect; // 宽高比
    float fov;    // 视野
    float near;   // 近平面距离
    float far;    // 远平面距离
};

class CameraOrtho : public Camera {
public:
    /** 正交投影相机
     * \param width 宽
     * \param height 高
     * \param near 近平面距离
     * \param far 远平面距离
     */
    CameraOrtho(float width, float height, float near = 0.1f, float far = 100.0f) {
        this->width = width;
        this->height = height;
        this->near = near;
        this->far = far;
        this->projection_transform = glm::ortho(0.0f, width, 0.0f, height, near, far);
    }

private:
    float width;    // 宽
    float height;   // 高
    float near;     // 近平面距离
    float far;      // 远平面距离
};

