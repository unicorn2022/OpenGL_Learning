#pragma once
#include "Engine/Basic/Shader.h"
#include "Engine/Basic/Texture.h"
#include <vector>

class Object {
public:
    Object(Shader* shader, std::vector<Texture*> textures) {
        this->shader = shader;
        for (Texture* texture : textures) 
            this->textures.push_back(texture);
    }

public:
    /* 游戏逻辑 */
    virtual void GameTick() {}
    /* 渲染逻辑 */
    virtual void RenderTick() = 0;

protected:
    /* 顶点数组 VAO */
    unsigned int VAO;
    /* 顶点数据 VBO */
    unsigned int VBO;
    /* 索引数据EBO */
    unsigned int EBO;
    /* 着色器程序 */
    Shader* shader;
    /* 使用到的纹理贴图 */
    std::vector<Texture*> textures;
};