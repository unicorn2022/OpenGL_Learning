#pragma once
#include "Engine/Object/Cube.h"

class Skybox : public Cube {
public:
    /** 天空盒
     * \param name 模型名称
     * \param material 材质
     * \param parent 父对象
     */
    Skybox(std::string name, Material* material, Object* parent) : Cube(name, material, parent) {}

public:
    /** 渲染逻辑
     * \param camera 摄像机
     * \param choose_material 指定材质, 材质仅在基类中使用
    */
    virtual void RenderTick(Camera* camera, Material* choose_material = NULL) {
        /* 在绘制时要更改深度检测为 <=, 并且禁用面剔除 */
        glDepthFunc(GL_LEQUAL);
        glDisable(GL_CULL_FACE);
        /* 绘制物体 */
        this->Cube::RenderTick(camera, choose_material);
        /* 修改回来 */
        glEnable(GL_CULL_FACE);
        glDepthFunc(GL_LESS);
    }
};