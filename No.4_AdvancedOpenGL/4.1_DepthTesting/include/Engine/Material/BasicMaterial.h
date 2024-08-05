#pragma once
#include "Engine/Basic/Material.h"

class BasicMaterial: public Material {
public:
    /** 基础材质
     * \param shader 着色器程序
     * \param color 颜色
     */
    BasicMaterial(Shader* shader, glm::vec3 color = glm::vec3(0.0f)) : Material(shader) {
        this->color = color;
    }
    ~BasicMaterial() {}

public:
    /** 使用当前光源进行渲染
     * \note 着色器程序中, 变量命名必须是: `color` 
    */
    void Use() {
        shader->Use();
        shader->SetUniform("color", color);
    }

public:
    glm::vec3 color;
};

