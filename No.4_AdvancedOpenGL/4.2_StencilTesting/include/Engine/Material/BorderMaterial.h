#pragma once
#include "Engine/Basic/Material.h"

class BorderMaterial : public Material {
public:
    /** 轮廓材质
     * \param shader 着色器程序
     */
    BorderMaterial(Shader* shader) : Material(shader) {}
    ~BorderMaterial() {}

public:
    /* 使用当前光源进行渲染 */
    void Use() {
        shader->Use();
        shader->SetUniform("border_color", COLOR_BORDER);
    }
};