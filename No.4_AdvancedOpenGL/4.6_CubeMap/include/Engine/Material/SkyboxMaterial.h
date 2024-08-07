#pragma once
#include "Engine/Basic/Material.h"

class SkyboxMaterial : public Material {
public:
    /** 轮廓材质
     * \param shader 着色器程序
     * \param skybox_texture 天空盒纹理
     */
    SkyboxMaterial(Shader* shader, TextureCube* skybox_texture) : Material(shader) {
        this->skybox_texture = skybox_texture;
    }
    ~SkyboxMaterial() {}

public:
    /* 使用当前材质进行渲染 */
    void Use() {
        shader->Use();
        skybox_texture->Use(0);
        shader->SetUniform("skybox_texture", 0);
    }

private:
    TextureCube* skybox_texture;
};