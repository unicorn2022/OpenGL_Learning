#pragma once
#include "Utils.h"
#include "Engine/Basic/Shader.h"
#include "Engine/Basic/Texture.h"

class Material {
public:
    Material(Shader* shader) {
        this->shader = shader;
    }

public:
    /** 使用当前材质进行渲染
     * \note 着色器程序中, 变量命名必须符合统一规范
    */
    virtual void Use() = 0;

public:
    Shader* shader;
};

class BasicMaterial: public Material {
public:
    /** 基础材质
     * \param shader 着色器程序
     * \param color 颜色
     */
    BasicMaterial(Shader* shader, glm::vec3 color) : Material(shader) {
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


class PhongMaterial : public Material {
public:
    /** 冯模型材质
     * \param shader 着色器程序
     * \param diffuse 漫反射贴图
     * \param specular 高光贴图
     * \param shininess 反光度
     */
    PhongMaterial(Shader* shader, Texture* diffuse, Texture* specular, float shininess)
    : Material(shader) {
        this->diffuse = diffuse;
        this->specular = specular;
        this->shininess = shininess;
    }
    ~PhongMaterial() {}

public:
    /** 使用当前光源进行渲染
     * \note 着色器程序中, 变量命名必须是: `material.diffuse, material.specular, material.shininess` 
    */
    void Use() {
        shader->Use();

        if (diffuse != NULL) {
            diffuse->Use(0);
            shader->SetUniform("material.diffuse", 0);
        }
        if (specular != NULL) {
            specular->Use(1);
            shader->SetUniform("material.specular", 1);
        }
        shader->SetUniform("material.shininess", shininess);
    }

private:
    Texture* diffuse;  // 漫反射贴图
    Texture* specular; // 高光贴图
    float shininess;   // 反光度
};