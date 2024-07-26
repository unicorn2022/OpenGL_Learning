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
        // 2.1 灯光
        Cube* point_light_cube = new Cube(shader_manager->light_cube_shader, material_manager->light_cube_material);
        point_light_cube->TransformTranslate(light_manager->point_light->position);
        point_light_cube->TransformScale(glm::vec3(0.2f));
        objects.push_back(point_light_cube);
        // 2.2 盒子
        Cube* container = new Cube(shader_manager->phong_light_model_shader, material_manager->container_material);
        objects.push_back(container);
    }

    ~ObjectManager() {
        for (Object* object : objects) 
            delete object;
        objects.clear();
    }

public:
    void GameTick() {
        /* 更改光照颜色 */
        glm::vec3 lightColor;
        lightColor.x = static_cast<float>(sin(glfwGetTime() * 2.0));
        lightColor.y = static_cast<float>(sin(glfwGetTime() * 0.7));
        lightColor.z = static_cast<float>(sin(glfwGetTime() * 1.3));
        glm::vec3 diffuseColor = lightColor   * glm::vec3(1.5f);
        glm::vec3 ambientColor = diffuseColor * glm::vec3(0.2f);
        light_manager->point_light->diffuse = diffuseColor;
        light_manager->point_light->ambient = ambientColor;
        dynamic_cast<BasicMaterial*>(material_manager->light_cube_material)->color = diffuseColor;
        
        /* 调用所有物体的 GameTick() */
        for (Object* object : objects) {
            object->GameTick();
        }
    }

    void RenderTick(){  
        /* 调用所有物体的 RenderTick() */
        for (Object* object : objects) 
            object->RenderTick(camera_manager->main_camera, light_manager->point_light);
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