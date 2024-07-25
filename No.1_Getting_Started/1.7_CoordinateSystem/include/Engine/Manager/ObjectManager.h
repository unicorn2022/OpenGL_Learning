#pragma once
#include "ShaderManager.h"
#include "TextureManager.h"
#include "Engine/Object/Square.h"
#include "Engine/Basic/Camera.h"


class ObjectManager {
public:
    ObjectManager(ShaderManager* shader_manager, TextureManager* texture_manager){
        objects.push_back(new Square(
            shader_manager->basic_3D_shader, 
            {texture_manager->wall_texture, texture_manager->face_texture}
        ));
    }

    ~ObjectManager() {
        for (Object* object : objects) 
            delete object;
        objects.clear();
    }

public:
    void DrawAll(Camera* camera){        
        for (Object* object : objects) {
            object->GameTick();
            object->RenderTick(camera);
        }
    }

private:
    std::vector<Object*> objects;
};