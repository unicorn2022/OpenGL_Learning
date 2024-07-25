#pragma once
#include <vector>
#include "ShaderManager.h"
#include "TextureManager.h"
#include "Engine/Object/Square.h"


class ObjectManager {
public:
    ObjectManager(ShaderManager* shader_manager, TextureManager* texture_manager){
        objects.push_back(new Square(shader_manager->basic_texture_shader, {texture_manager->wall_texture, texture_manager->face_texture}));
    }
    ~ObjectManager() {
        for (Object* object : objects) 
            delete object;
        objects.clear();
    }

public:
    void DrawAll(){        
        for (Object* object : objects) {
            object->GameTick();
            object->RenderTick();
        }
    }

private:
    std::vector<Object*> objects;
};