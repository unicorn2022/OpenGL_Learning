#pragma once
#include "Engine/Basic/Shader.h"
#include "Engine/Basic/Texture.h"
#include <vector>

class Object {
public:
    virtual void Draw(Shader* shader, std::vector<Texture*> textures) = 0;

protected:
    /* 顶点数组 VAO */
    unsigned int VAO;
    /* 顶点数据 VBO */
    unsigned int VBO;
    /* 索引数据EBO */
    unsigned int EBO;
};