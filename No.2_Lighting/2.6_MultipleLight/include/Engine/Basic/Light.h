#pragma once
#include "Utils.h"
#include "Engine/Basic/Shader.h"

class Light {
public:
    /** 光源
     * \param ambient 环境光颜色
     * \param diffuse 漫反射光颜色
     * \param specular 高光颜色
     */
    Light(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular) {
        this->ambient = ambient;
        this->diffuse = diffuse;
        this->specular = specular;
    }

public:
    /** 使用当前光源进行渲染
     * \param shader 物体使用的着色器程序
     * \note 着色器程序中, 变量命名必须符合统一规范
    */
    virtual void Use(Shader* shader, int index) = 0;

public:
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
};