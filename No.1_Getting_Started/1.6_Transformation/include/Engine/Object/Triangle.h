#pragma once

#include "Engine/Basic/Object.h"
#include <vector>

class Triangle : public Object {
public:
    Triangle(Shader* shader, std::vector<Texture*> textures) : Object(shader, textures) {
        float vertices[] = {
            -0.5f, -0.5f, 0.0f,
            0.5f, -0.5f, 0.0f,
            0.0f,  0.5f, 0.0f
        };
        /* 1. 绑定顶点数组VAO */
        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);
        /* 2. 传输顶点数据VBO */
        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        /* 3. 指定顶点属性位置 */
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        /* 4. 取消绑定 */
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }

    ~Triangle() {
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
    }

public:
    virtual void RenderTick() {
        /* 绑定着色器、纹理 */
        if (shader != NULL) shader->Use(); 

        /* 绘制 */
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
    }
};