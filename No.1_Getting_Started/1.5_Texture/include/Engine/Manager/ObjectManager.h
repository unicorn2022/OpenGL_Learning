#pragma once
#include <vector>
#include "ShaderManager.h"
#include "TextureManager.h"
#include "Engine/Object/Square.h"


class ObjectManager {
public:
    ObjectManager(){
        objects.push_back(new Square());
    }
    ~ObjectManager() {
        for (Object* object : objects) {
            delete object;
        }
    }

public:
    void DrawAllByBasicShader(ShaderManager* shader_manager){
        std::vector<Texture*> textures;
        for (Object* object : objects) {
            object->Draw(shader_manager->basic_shader, textures);
        }
    }
    
    void DrawAllByBasicTextureShader(ShaderManager* shader_manager, TextureManager* texture_manager){
        std::vector<Texture*> textures;
        textures.push_back(texture_manager->wall_texture);
        textures.push_back(texture_manager->face_texture);
        
        for (Object* object : objects) {
            object->Draw(shader_manager->basic_texture_shader, textures);
        }
    }

private:
    std::vector<Object*> objects;
};