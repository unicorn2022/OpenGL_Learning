#pragma once
#include "Engine/Basic/Material.h"

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