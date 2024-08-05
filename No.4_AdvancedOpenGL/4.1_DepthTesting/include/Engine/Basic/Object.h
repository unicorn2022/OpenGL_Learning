#pragma once
#include "Engine/Basic/Camera.h"
#include "Engine/Basic/Light.h"
#include "Engine/Basic/Material.h"

class Object {
public:
    /** 游戏中的对象
     * \param name 名称
     * \param material 材质
     * \param parent 父对象
     */
    Object(std::string name, Material* material, Object* parent) {
        this->name = name;
        this->material = material;
        this->model_transform_translate = glm::mat4(1.0f);
        this->model_transform_rotate = glm::mat4(1.0f);
        this->model_transform_scale = glm::mat4(1.0f);
        this->parent = parent;
    }

public:
    /* 游戏逻辑 */
    virtual void GameTick() {}
    /* 渲染逻辑(基类): 绑定着色器、纹理、模型变换矩阵 */
    virtual void RenderTick(Camera* camera) {
        if (material == NULL) return;
        material->Use();

        /* 绑定模型变换矩阵 */
        // 1. 计算局部变换
        glm::mat4 local_transform = model_transform_translate * model_transform_rotate * model_transform_scale;
        // 2. 计算坐标系变换 (只计算平移)
        glm::mat4 global_transform = glm::mat4(1.0f);
        Object* prt = parent;
        int cnt = 0;
        while(prt != NULL) {
            global_transform = prt->model_transform_translate * prt->model_transform_rotate * global_transform;
            prt = prt->parent;
        }
        // 3. 先局部变换, 然后坐标系变换
        material->shader->SetUniform("model_transform", global_transform * local_transform);
    }

public:
    /** 平移物体
     * \param direction 平移向量
     */
    virtual void TransformTranslate(glm::vec3 direction) {
        model_transform_translate = glm::translate(model_transform_translate, direction);
    }
    
    /** 旋转物体
     * \param axis 旋转轴
     * \param angle 旋转角度(角度值)
     */
    virtual void TransformRotate(glm::vec3 axis, float angle) {
        model_transform_rotate = glm::rotate(model_transform_rotate, glm::radians(angle), axis);
    }
    
    /** 缩放物体
     * \param rate 缩放倍率
     */
    virtual void TransformScale(glm::vec3 rate) {
        model_transform_scale = glm::scale(model_transform_scale, rate);
    }

public:
    /* 顶点数组 VAO */
    unsigned int VAO;
    /* 顶点数据 VBO */
    unsigned int VBO;
    /* 索引数据EBO */
    unsigned int EBO;
    /* 材质 */
    Material* material;
    
public:
    /* 模型变换矩阵 */
    glm::mat4 model_transform_translate;
    glm::mat4 model_transform_rotate;
    glm::mat4 model_transform_scale;
    Object* parent;
    std::string name;

private:
    virtual void GameInit() {}
    virtual void RenderInit() {}
};