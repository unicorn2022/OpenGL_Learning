#pragma once

#include "Engine/Basic/Object.h"

class Triangle : public Object {
public:
    Triangle(std::string name, Material* material) : Object(name, material, NULL) {
        RenderInit();
    }

    ~Triangle() {
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
    }

public:
    /** 渲染逻辑
     * \param camera 摄像机
     * \param choose_material 指定材质, 材质仅在基类中使用
    */
    virtual void RenderTick(Camera* camera, Material* choose_material = NULL) {
        this->Object::RenderTick(camera, choose_material);
        if (choose_material == NULL) choose_material = this->material;
        if (choose_material == NULL) return;
        
        /* 绘制 */
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
    }

private:
    void RenderInit() {
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
};