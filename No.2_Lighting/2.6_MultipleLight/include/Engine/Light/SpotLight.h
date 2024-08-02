#pragma once
#include "Engine/Basic/Light.h"

class SpotLight : public Light {
public:
    /** 聚光源
     * \param position 光源位置
     * \param direction 光源方向
     * \param ambient 环境光颜色
     * \param diffuse 漫反射光颜色
     * \param specular 高光颜色
     * \param inner_cut_off 内切角(角度)
     * \param outer_cut_off 外切角(角度)
     */
    SpotLight(glm::vec3 position, glm::vec3 direction, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float inner_cut_off, float outer_cut_off) 
    : Light(ambient, diffuse, specular) {
        this->position = position;
        this->direction = direction;
        this->inner_cut_off = inner_cut_off;
        this->outer_cut_off = outer_cut_off;
    }
    ~SpotLight() {}

public:
    /** 使用当前光源进行渲染
     * \param shader 物体使用的着色器程序
     * \param index 光源编号
     * \note 着色器程序中, 变量命名必须符合预定
    */
    void Use(Shader* shader, int index) {
        /* 光源颜色 */
        shader->SetUniform("spot_light.ambient", ambient);
        shader->SetUniform("spot_light.diffuse", diffuse);
        shader->SetUniform("spot_light.specular", specular);
        /* 光源属性 */
        shader->SetUniform("spot_light.position", position);
        shader->SetUniform("spot_light.direction", direction);
        shader->SetUniform("spot_light.inner_cut_off", glm::cos(glm::radians(inner_cut_off)));
        shader->SetUniform("spot_light.outer_cut_off", glm::cos(glm::radians(outer_cut_off)));
        /* 衰减 */
        shader->SetUniform("spot_light.constant", 1.0f);
        shader->SetUniform("spot_light.linear", 0.09f);
        shader->SetUniform("spot_light.quadratic", 0.032f);
    }
public:
    glm::vec3 position;
    glm::vec3 direction;
    float inner_cut_off;
    float outer_cut_off;
};