#pragma once
#include "Engine/Basic/Material.h"

class PostProcessMaterial : public Material {
public:
    /** 轮廓材质
     * \param shader 着色器程序
     */
    PostProcessMaterial(Shader* shader) : Material(shader) {}
    ~PostProcessMaterial() {}

public:
    /* 使用当前材质进行渲染 */
    void Use() {
        shader->Use();
        shader->SetUniform("screen_texture", 0);
        shader->SetUniform("choose_post_process", GlobalValue::GetInstance().GetIntValue("choose_post_process"));
    }
};