#pragma once
#include "Engine/Basic/Material.h"

class DepthVisualizationMaterial : public Material {
public:
    /** 深度可视化材质
     * \param shader 着色器程序
     */
    DepthVisualizationMaterial(Shader* shader)
    : Material(shader) {}
    ~DepthVisualizationMaterial() {
        
    }

public:
    /** 使用当前光源进行渲染
     * \note 着色器程序中, 变量命名必须是: `material.diffuse, material.specular, material.shininess` 
    */
    void Use() {
        shader->Use();
        shader->SetUniform("z_near", CAMERA_ZNEAR);
        shader->SetUniform("z_far", CAMERA_ZFAR);
    }
};