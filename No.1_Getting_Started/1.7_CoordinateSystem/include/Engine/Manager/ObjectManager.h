#pragma once
#include "ShaderManager.h"
#include "TextureManager.h"
#include "CameraManager.h"
#include "Engine/Object/Cube.h"
#include "Engine/Object/Square.h"


class ObjectManager {
public:
    ObjectManager(ShaderManager* shader_manager, TextureManager* texture_manager){
        glm::vec3 cubePositions[] = {
            glm::vec3( 0.0f,  0.0f,  0.0f), 
            glm::vec3( 2.0f,  5.0f, -15.0f), 
            glm::vec3(-1.5f, -2.2f, -2.5f),  
            glm::vec3(-3.8f, -2.0f, -12.3f),  
            glm::vec3( 2.4f, -0.4f, -3.5f),  
            glm::vec3(-1.7f,  3.0f, -7.5f),  
            glm::vec3( 1.3f, -2.0f, -2.5f),  
            glm::vec3( 1.5f,  2.0f, -2.5f), 
            glm::vec3( 1.5f,  0.2f, -1.5f), 
            glm::vec3(-1.3f,  1.0f, -1.5f)  
        };
        
        for(int i = 0; i < 10; i++) {
            Cube* cube = new Cube(
                shader_manager->basic_cube_shader, 
                {texture_manager->wall_texture, texture_manager->face_texture}
            );
            cube->TransformTranslate(cubePositions[i]);
            cube->TransformRotate(glm::vec3(1.0f, 0.3f, 0.5f), 20 * i);
            objects.push_back(cube);
        }
        
    }

    ~ObjectManager() {
        for (Object* object : objects) 
            delete object;
        objects.clear();
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