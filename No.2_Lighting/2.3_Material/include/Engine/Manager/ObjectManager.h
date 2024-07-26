#pragma once
#include "ShaderManager.h"
#include "TextureManager.h"
#include "CameraManager.h"
#include "LightManager.h"
#include "MaterialManager.h"
#include "Engine/Object/Cube.h"


class ObjectManager {
public:
    ObjectManager(ShaderManager* shader_manager, TextureManager* texture_manager, LightManager* light_manager, MaterialManager* material_manager){
        Cube* point_light_cube = new Cube(shader_manager->light_cube_shader, {}, NULL);
        point_light_cube->TransformTranslate(light_manager->point_light->position);
        point_light_cube->TransformScale(glm::vec3(0.2f));
        objects.push_back(point_light_cube);

        Cube* lighted_cube = new Cube(shader_manager->phong_light_model_shader, {}, material_manager->cube_material);
        objects.push_back(lighted_cube);
    }

    ~ObjectManager() {
        for (Object* object : objects) 
            delete object;
        objects.clear();
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

public:
    void GameTick(CameraManager* camera_manager, LightManager* light_manager) {
        /* 更改光照颜色 */
        glm::vec3 lightColor;
        lightColor.x = static_cast<float>(sin(glfwGetTime() * 2.0));
        lightColor.y = static_cast<float>(sin(glfwGetTime() * 0.7));
        lightColor.z = static_cast<float>(sin(glfwGetTime() * 1.3));
        glm::vec3 diffuseColor = lightColor   * glm::vec3(0.5f); // decrease the influence
        glm::vec3 ambientColor = diffuseColor * glm::vec3(0.2f); // low influence
        light_manager->point_light->diffuse = diffuseColor;
        light_manager->point_light->ambient = ambientColor;


        for (Object* object : objects) {
            object->GameTick();
        }
    }

    void RenderTick(CameraManager* camera_manager, LightManager* light_manager){  
        for (Object* object : objects) {
            object->GameTick();
            object->RenderTick(camera_manager->main_camera, light_manager->point_light);
        }
    }

private:
    std::vector<Object*> objects;
};