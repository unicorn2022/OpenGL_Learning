#pragma once
#include "ShaderManager.h"
#include "TextureManager.h"
#include "CameraManager.h"
#include "LightManager.h"
#include "MaterialManager.h"
#include "Engine/Object/INCLUDE_ALL.h"

std::vector<glm::vec3> container_position {
    glm::vec3(-1.0f, 0.0f, -1.0f),
    glm::vec3(2.0f, 0.0f, 0.0f)
};

std::vector<glm::vec3> window_position {
    glm::vec3(-1.5f, 0.0f, -0.48f),
    glm::vec3( 1.5f, 0.0f, 0.51f),
    glm::vec3( 0.0f, 0.0f, 0.7f),
    glm::vec3(-0.3f, 0.0f, -2.3f),
    glm::vec3( 0.5f, 0.0f, -0.6f)
};

class ObjectManager {
public:
    static ObjectManager& GetInstance(){
        static ObjectManager instance;
        return instance;
    }

private:
    ObjectManager(){
        /* 2个箱子 */
        for (auto position : container_position) {
            Object* container = new Cube("container", MaterialManager::GetInstance().container_material, NULL);
            container->TransformTranslate(position);
            objects.push_back(container);
        }

        /* 5个窗户 */
        for (auto position : window_position) {
            Object* window = new Square("window", MaterialManager::GetInstance().window_material, NULL);
            window->TransformTranslate(position);
            window->TransformScale(glm::vec3(0.5f));
            transpoart_objects.push_back(window);
        }

        // nanosuit = new OBJModel("nanosuit", ShaderManager::GetInstance().phong_light_model_shader, container);
        // objects.push_back(nanosuit);
        // nanosuit->TransformTranslate({0.0f, 2.0f, 0.0f});
    }

    ~ObjectManager() {
        for (Object* object : objects) delete object;
        objects.clear();
        for (Object* object : transpoart_objects) delete object;
        transpoart_objects.clear();
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
        /* 1. 绘制不透明物体 */
        for (Object* object : objects)
            object->RenderTick(CameraManager::GetInstance().main_camera, choose_material);
        /* 2. 对透明物体按照从远到近排序 */
        std::sort(transpoart_objects.begin(), transpoart_objects.end(), [](Object* &A, Object* &B) {
            float distA = glm::distance(A->GetPosition(), CameraManager::GetInstance().main_camera->position);
            float distB = glm::distance(B->GetPosition(), CameraManager::GetInstance().main_camera->position);
            return distA > distB;
        });
        
        /* 3. 绘制透明物体 */
        // 渲染两面均可见的物体时, 要先禁用面剔除
        glDisable(GL_CULL_FACE);
        for (Object* object : transpoart_objects)
            object->RenderTick(CameraManager::GetInstance().main_camera, choose_material);
        glEnable(GL_CULL_FACE);
    }

public:
    void HandleInput(GLFWwindow* window) {
        /* ↑增加mix_rate */
        if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
            float mix_rate = GlobalValue::GetInstance().GetFloatValue("mix_rate");
            mix_rate += 0.01;
            GlobalValue::GetInstance().SetValue("mix_rate", mix_rate, 0.0, 1.0);
        }
        /* ↓减少mix_rate */
        if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
            float mix_rate = GlobalValue::GetInstance().GetFloatValue("mix_rate");
            mix_rate -= 0.01;
            GlobalValue::GetInstance().SetValue("mix_rate", mix_rate, 0.0, 1.0);
        }
        /* 0~5 选择后处理效果 */
        for (int i = 0; i <= POST_PROCESS_NUM; i++) {
            if (glfwGetKey(window, GLFW_KEY_0 + i) == GLFW_PRESS) 
                GlobalValue::GetInstance().SetValue("choose_post_process", i);
        }
    }

public:
    std::vector<Object*> objects;
    std::vector<Object*> transpoart_objects;
    Object* nanosuit;
};