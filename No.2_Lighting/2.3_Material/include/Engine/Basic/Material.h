#pragma once
#include "Engine/Basic/Utils.h"
#include "Engine/Basic/Shader.h"

class Material {
public:
    Material() {}

public:
    /** 使用当前材质进行渲染
     * \param shader 物体使用的着色器程序
     * \note 着色器程序中, 变量命名必须符合统一规范
    */
    virtual void Use(Shader* shader) = 0;
};

class PhongMaterial : public Material {
public:
    /** 冯模型材质
     * \param ambient 环境光颜色
     * \param diffuse 漫反射光颜色
     * \param specular 高光颜色
     * \param shininess 反光度
     */
    PhongMaterial(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float shininess) {
        this->ambient = ambient;
        this->diffuse = diffuse;
        this->specular = specular;
        this->shininess = shininess;
    }
    ~PhongMaterial() {}

public:
    /** 使用当前光源进行渲染
     * \param shader 物体使用的着色器程序
     * \note 着色器程序中, 变量命名必须是: `material.ambient, material.diffuse, material.specular, material.shininess` 
    */
    void Use(Shader* shader) {
        shader->SetUniform("material.ambient", ambient);
        shader->SetUniform("material.diffuse", diffuse);
        shader->SetUniform("material.specular", specular);
        shader->SetUniform("material.shininess", shininess);
    }

private:
    glm::vec3 ambient;  // 环境光颜色
    glm::vec3 diffuse;  // 漫反射光颜色
    glm::vec3 specular; // 高光颜色
    float shininess;    // 反光度
};