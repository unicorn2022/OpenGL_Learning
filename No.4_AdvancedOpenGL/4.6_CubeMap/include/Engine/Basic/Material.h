#pragma once
#include "Utils.h"
#include "Engine/Basic/Shader.h"
#include "Engine/Basic/Texture.h"
#include "Engine/Basic/TextureCube.h"

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
