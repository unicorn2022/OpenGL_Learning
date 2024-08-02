#pragma once
#include "ShaderManager.h"
#include "TextureManager.h"
#include "CameraManager.h"
#include "LightManager.h"
#include "MaterialManager.h"
#include "Engine/Object/Cube.h"


class ObjectManager {
public:
    ObjectManager(CameraManager* camera_manager, ShaderManager* shader_manager, TextureManager* texture_manager, LightManager* light_manager, MaterialManager* material_manager){
        /* 1. 存储 manager 指针*/
        this->camera_manager = camera_manager;
        this->shader_manager = shader_manager;
        this->texture_manager = texture_manager;
        this->light_manager = light_manager;
        this->material_manager = material_manager;
        
        /* 2. 创建物体 */
        Cube* container = new Cube(material_manager->container_material);
        objects.push_back(container);
    }

    ~ObjectManager() {
        for (Object* object : objects) 
            delete object;
        objects.clear();
    }

public:
    void GameTick() {
        /* 更改据光源 */
        light_manager->spot_light->position = camera_manager->main_camera->position;
        light_manager->spot_light->direction = camera_manager->main_camera->front;

        /* 调用所有物体的 GameTick() */
        for (Object* object : objects) {
            light_manager->RenderTick(object->material->shader);
            object->GameTick();
        }
    }

    void RenderTick(){
        /* 调用所有物体的 RenderTick() */
        for (Object* object : objects) 
            object->RenderTick(camera_manager->main_camera);
    }

public:
    void HandleInput(GLFWwindow* window) {
        /* ↑增加mix_rate */
        if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
            float mix_rate = GlobalValue::GetInstance().GetValue("mix_rate");
            mix_rate += 0.01;
            GlobalValue::GetInstance().SetValue("mix_rate", mix_rate, 0.0, 1.0);
        }
        /* ↓减少mix_rate */
        if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
            float mix_rate = GlobalValue::GetInstance().GetValue("mix_rate");
            mix_rate -= 0.01;
            GlobalValue::GetInstance().SetValue("mix_rate", mix_rate, 0.0, 1.0);
        }
    }

private:
    std::vector<Object*> objects;
    CameraManager* camera_manager;
    ShaderManager* shader_manager;
    TextureManager* texture_manager;
    LightManager* light_manager;
    MaterialManager* material_manager;
};