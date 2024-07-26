#pragma once
#include "Engine/Basic/Utils.h"
#include "Engine/Basic/Shader.h"

class Light {
public:
    /** 光源
     * \param position 光源位置
     * \param color 光源颜色
     */
    Light(glm::vec3 position, glm::vec3 color) {
        light_position = position;
        light_color = color;
    }

public:
    /** 使用当前光源进行渲染
     * \param shader 物体使用的着色器程序
     * \note 着色器程序中, 变量命名必须符合统一规范
    */
    virtual void Use(Shader* shader) = 0;

public:
    glm::vec3 light_position;
    glm::vec3 light_color;
};

class PointLight : public Light {
public:
    /** 点光源
     * \param position 光源位置
     * \param color 光源颜色
     */
    PointLight(glm::vec3 position, glm::vec3 color) : Light(position, color) {}
    ~PointLight() {}

public:
    /** 使用当前光源进行渲染
     * \param shader 物体使用的着色器程序
     * \note 着色器程序中, 变量命名必须是: `light_position, light_color` 
    */
    void Use(Shader* shader) {
        shader->SetUniform("light_position", light_position);
        shader->SetUniform("light_color", light_color);
    }
};