#pragma once

#include "Engine/Basic/Object.h"

class Square : public Object {
public:
    Square(Shader* shader, std::vector<Texture*> textures) : Object(shader, textures) {
        float vertices[] = {
        //     ---- 位置 ----       ---- 颜色 ----     - 纹理坐标 -
            0.5f,  0.5f, 0.0f,    1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // 右上
            0.5f, -0.5f, 0.0f,    0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // 右下
            -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // 左下
            -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // 左上
        };
        unsigned int indices[] = {
            // 注意索引从0开始! 
            // 此例的索引(0,1,2,3)就是顶点数组vertices的下标，
            // 这样可以由下标代表顶点组合成矩形
            0, 1, 3, // 第一个三角形
            1, 2, 3  // 第二个三角形
        };

        /* 1. 绑定顶点数组VAO */
        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);

        /* 2. 传输顶点数据VBO */
        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        
        /* 3. 传输索引数据EBO */
        glGenBuffers(1, &EBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
        
        /* 4. 指定顶点属性位置 */
        // 4.1 位置
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        // 4.2 颜色
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
        // 4.3 纹理坐标
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
        glEnableVertexAttribArray(2);
        
        /* 5. 取消绑定 */
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }

    ~Square() {
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
        glDeleteBuffers(1, &EBO);
    }

public:
    virtual void RenderTick() {
        /* 绑定着色器、纹理 */
        if (shader != NULL) shader->Use();
        for (int i = 0; i < textures.size(); i++)
            textures[i]->Use(i);
        
        /* 纹理对应关系 */
        shader->SetUniform("wall_texture", 0);
        shader->SetUniform("face_texture", 1);
        shader->SetUniform("mix_rate", GlobalValue::GetInstance().GetValue("mix_rate"));

        /* 颜色变化 */
        float time = glfwGetTime();
        float green = (sin(time) / 2.0f) + 0.5f;
        shader->SetUniform("ourColor", 0.0f, green, 0.0f, 1.0f);

        /* 绘制 */
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    }
};