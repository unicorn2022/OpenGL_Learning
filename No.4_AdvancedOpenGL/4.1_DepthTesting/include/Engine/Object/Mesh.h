#pragma once
#include "Engine/Basic/Object.h"

struct Vertex {
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
};

class Mesh : public Object {
public:
    Mesh(std::string name, Material* material, std::vector<Vertex> vertices, std::vector<unsigned int> indices, Object* parent) 
    : Object(name, material, parent) {
        this->vertices = vertices;
        this->indices  = indices;
        RenderInit();
    }

public:
    virtual void GameTick() {}

    virtual void RenderTick(Camera* camera) {
        this->Object::RenderTick(camera);
        if (material == NULL) return;

        /* 相机参数 */
        Shader* shader = material->shader;
        camera->Use(shader);

        /* Shader变量 */
        shader->SetUniform("view_position", camera->position);
        shader->SetUniform("object_color", glm::vec3(1.0f, 0.5f, 0.31f));

        /* 绘制 */
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }

public:
    std::vector<Vertex> vertices;       // 顶点
    std::vector<unsigned int> indices;  // 索引

private:
    void GameInit(){}

    void RenderInit() {
        /* 1. 绑定顶点数组VAO */
        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);
        
        /* 2. 传输顶点数据VBO */
        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);
        
        /* 3. 传输索引数据EBO */
        glGenBuffers(1, &EBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

        /* 4. 指定顶点属性位置 */
        // 4.1 位置
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
        // 4.2 法线
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
        // 4.3 纹理坐标
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));
        
        /* 5. 取消绑定 */
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
}; 