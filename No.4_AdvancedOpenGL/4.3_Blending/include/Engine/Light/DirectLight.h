#pragma once
#include "Engine/Basic/Light.h"

class DirectLight : public Light {
public:
    /** 方向光源
     * \param direction 光源方向
     * \param ambient 环境光颜色
     * \param diffuse 漫反射光颜色
     * \param specular 高光颜色
     */
    DirectLight(glm::vec3 direction, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular) 
    : Light(ambient, diffuse, specular) {
        this->direction = direction;
    }
    ~DirectLight() {}

public:
    /** 使用当前光源进行渲染
     * \param shader 物体使用的着色器程序
     * \param index 光源编号
     * \note 着色器程序中, 变量命名必须符合预定
    */
    void Use(Shader* shader, int index) {
        /* 光源颜色 */
        shader->SetUniform("direct_light.ambient", ambient);
        shader->SetUniform("direct_light.diffuse", diffuse);
        shader->SetUniform("direct_light.specular", specular);
        /* 光源属性 */
        shader->SetUniform("direct_light.direction", direction);
    }
public:
    glm::vec3 direction;
};