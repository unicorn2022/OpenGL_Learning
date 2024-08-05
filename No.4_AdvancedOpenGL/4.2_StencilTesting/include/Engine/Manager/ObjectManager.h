#pragma once
#include "ShaderManager.h"
#include "TextureManager.h"
#include "CameraManager.h"
#include "LightManager.h"
#include "MaterialManager.h"
#include "Engine/Object/INCLUDE_ALL.h"


class ObjectManager {
public:
    static ObjectManager& GetInstance(){
        static ObjectManager instance;
        return instance;
    }

private:
    ObjectManager(){
        container1 = new Cube("container1", MaterialManager::GetInstance().phong_material, NULL);
        objects.push_back(container1);

        container2 = new Cube("container2", MaterialManager::GetInstance().phong_material, container1);
        objects.push_back(container2);
        container2->TransformTranslate({0.0f, 2.0f, 0.0f});

        nanosuit = new OBJModel("nanosuit", ShaderManager::GetInstance().phong_light_model_shader, container2);
        objects.push_back(nanosuit);
        nanosuit->TransformTranslate({0.0f, 2.0f, 0.0f});
    }

    ~ObjectManager() {
        for (Object* object : objects) 
            delete object;
        objects.clear();
    }

public:
    void GameTick() {
        /* 更改聚光源 */
        LightManager::GetInstance().spot_light->position = CameraManager::GetInstance().main_camera->position;
        LightManager::GetInstance().spot_light->direction = CameraManager::GetInstance().main_camera->front;

        /* 更改模型位置 */
        // container1->TransformRotate({0, 1, 0}, 1);
        // container2->TransformRotate({0, 1, 0}, 1);
        // nanosuit->TransformRotate({0, 1, 0}, 1);

        /* 调用所有物体的 GameTick() */
        for (Object* object : objects) 
            object->GameTick();
    }

    void RenderTick(Material* choose_material = NULL){
        /* 如果是绘制边界, 则将所有物体扩大1.1倍, 绘制完成后再缩小回来 */
        if (choose_material == MaterialManager::GetInstance().border_material) {
            for (Object* object : objects) 
                object->TransformScale(glm::vec3(1.1f));
            for (Object* object : objects) 
                object->RenderTick(CameraManager::GetInstance().main_camera, choose_material);
            for (Object* object : objects) 
                object->TransformScale(glm::vec3(1.0f / 1.1f));
        } 
        else {
            for (Object* object : objects) 
                object->RenderTick(CameraManager::GetInstance().main_camera, choose_material);
        }
        
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
    Object* container1;
    Object* container2;
    Object* nanosuit;
};