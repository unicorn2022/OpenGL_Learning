#pragma once
#include "Engine/Basic/Shader.h"
#include "Engine/Basic/Texture.h"
#include "Engine/Basic/Camera.h"

class Object {
public:
    Object(Shader* shader, std::vector<Texture*> textures) {
        this->shader = shader;
        for (Texture* texture : textures) 
            this->textures.push_back(texture);
        this->model_transform_translate = glm::mat4(1.0f);
        this->model_transform_rotate = glm::mat4(1.0f);
        this->model_transform_scale = glm::mat4(1.0f);
    }

public:
    /* 游戏逻辑 */
    virtual void GameTick() {}
    /* 渲染逻辑 */
    virtual void RenderTick(Camera* camera) {
        if (shader == NULL) return;

        /* 绑定着色器、纹理 */
        shader->Use();
        for (int i = 0; i < textures.size(); i++)
            textures[i]->Use(i);
        
        /* 变换矩阵 */
        shader->SetUniform("model_transform", model_transform_translate * model_transform_rotate * model_transform_scale);
    }

protected:
    /** 平移物体
     * \param direction 平移向量
     */
    void TransformTranslate(glm::vec3 direction) {
        model_transform_translate = glm::translate(model_transform_translate, direction);
    }
    
    /** 旋转物体
     * \param axis 旋转轴
     * \param angle 旋转角度(角度值)
     */
    void TransformRotate(glm::vec3 axis, float angle) {
        model_transform_rotate = glm::rotate(model_transform_rotate, glm::radians(angle), axis);
    }
    
    /** 缩放物体
     * \param rate 缩放倍率
     */
    void TransformScale(glm::vec3 rate) {
        model_transform_scale = glm::scale(model_transform_scale, rate);
    }

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
    
private:
    /* 模型变换矩阵 */ 
    glm::mat4 model_transform_translate;
    glm::mat4 model_transform_rotate;
    glm::mat4 model_transform_scale;
};