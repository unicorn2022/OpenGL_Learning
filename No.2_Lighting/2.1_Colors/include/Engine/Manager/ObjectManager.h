#pragma once
#include "ShaderManager.h"
#include "TextureManager.h"
#include "CameraManager.h"
#include "Engine/Object/Cube.h"
#include "Engine/Object/Square.h"


class ObjectManager {
public:
    ObjectManager(ShaderManager* shader_manager, TextureManager* texture_manager){
        Cube* light = new Cube(shader_manager->light_shader, {});
        light->TransformTranslate(glm::vec3(1.2f, 1.0f, 2.0f));
        light->TransformScale(glm::vec3(0.2f));
        objects.push_back(light);

        Cube* lighted_cube = new Cube(shader_manager->lighted_cube_shader, {});
        objects.push_back(lighted_cube);

        GlobalValue::GetInstance().SetValue("light_color.x", 1.0f);
        GlobalValue::GetInstance().SetValue("light_color.y", 1.0f);
        GlobalValue::GetInstance().SetValue("light_color.z", 1.0f);
        GlobalValue::GetInstance().SetValue("object_color.x", 1.0f);
        GlobalValue::GetInstance().SetValue("object_color.y", 0.5f);
        GlobalValue::GetInstance().SetValue("object_color.z", 0.31f);
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

    void RenderTick(CameraManager* camera_manager){        
        for (Object* object : objects) {
            object->GameTick();
            object->RenderTick(camera_manager->main_camera);
        }
    }

private:
    std::vector<Object*> objects;
};