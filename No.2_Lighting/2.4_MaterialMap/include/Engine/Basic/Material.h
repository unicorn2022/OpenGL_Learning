#pragma once
#include "Utils.h"
#include "Engine/Basic/Shader.h"
#include "Engine/Basic/Texture.h"

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

class BasicMaterial: public Material {
public:
    /** 基础材质
     * \param color 颜色
     */
    BasicMaterial(glm::vec3 color) {
        this->color = color;
    }
    ~BasicMaterial() {}

public:
    /** 使用当前光源进行渲染
     * \param shader 物体使用的着色器程序
     * \note 着色器程序中, 变量命名必须是: `color` 
    */
    void Use(Shader* shader) {
        if (shader == NULL) return;
        shader->SetUniform("color", color);
    }

public:
    glm::vec3 color;
};


class PhongMaterial : public Material {
public:
    /** 冯模型材质
     * \param diffuse 漫反射贴图
     * \param specular 高光贴图
     * \param shininess 反光度
     */
    PhongMaterial(Texture* diffuse, Texture* specular, float shininess) {
        this->diffuse = diffuse;
        this->specular = specular;
        this->shininess = shininess;
    }
    ~PhongMaterial() {}

public:
    /** 使用当前光源进行渲染
     * \param shader 物体使用的着色器程序
     * \note 着色器程序中, 变量命名必须是: `material.diffuse, material.specular, material.shininess` 
    */
    void Use(Shader* shader) {
        if (shader == NULL) return;

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
    float shininess;    // 反光度
};