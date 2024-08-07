#pragma once
#include "Engine/Basic/Light.h"

class PointLight : public Light {
public:
    /** 点光源
     * \param position 光源位置
     * \param ambient 环境光颜色
     * \param diffuse 漫反射光颜色
     * \param specular 高光颜色
     */
    PointLight(glm::vec3 position, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular) 
    : Light(ambient, diffuse, specular) {
        this->position = position;
    }
    ~PointLight() {}

public:
    /** 使用当前光源进行渲染
     * \param shader 物体使用的着色器程序
     * \param index 光源编号
     * \note 着色器程序中, 变量命名必须符合预定
    */
    void Use(Shader* shader, int index) {
        /* 光源颜色 */
        shader->SetUniform("point_lights[" + std::to_string(index) + "].ambient", ambient);
        shader->SetUniform("point_lights[" + std::to_string(index) + "].diffuse", diffuse);
        shader->SetUniform("point_lights[" + std::to_string(index) + "].specular", specular);
        /* 光源属性 */
        shader->SetUniform("point_lights[" + std::to_string(index) + "].position", position);
        /* 衰减 */
        shader->SetUniform("point_lights[" + std::to_string(index) + "].constant", 1.0f);
        shader->SetUniform("point_lights[" + std::to_string(index) + "].linear", 0.09f);
        shader->SetUniform("point_lights[" + std::to_string(index) + "].quadratic", 0.032f);
    }
public:
    glm::vec3 position;
};