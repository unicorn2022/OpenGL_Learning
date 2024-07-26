#pragma once
#include "ShaderManager.h"
#include "TextureManager.h"
#include "CameraManager.h"
#include "LightManager.h"
#include "Engine/Object/Cube.h"
#include "Engine/Object/Square.h"


class ObjectManager {
public:
    ObjectManager(ShaderManager* shader_manager, TextureManager* texture_manager, LightManager* light_manager){
        Cube* point_light_cube = new Cube(shader_manager->light_cube_shader, {});
        point_light_cube->TransformTranslate(light_manager->point_light->light_position);
        point_light_cube->TransformScale(glm::vec3(0.2f));
        objects.push_back(point_light_cube);

        Cube* lighted_cube = new Cube(shader_manager->phong_light_model_shader, {});
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
    void GameTick() {
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