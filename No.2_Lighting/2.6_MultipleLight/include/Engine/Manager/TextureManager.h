#pragma once
#include "Engine/Basic/Texture.h"
    
class TextureManager {
public:
    TextureManager() {
        wall_texture = new Texture("wall.jpg");
        face_texture = new Texture("face.png");
        container_diffuse_texture = new Texture("container_diffuse.png");
        container_specular_texture = new Texture("container_specular.png");
    }
    ~TextureManager(){
        delete wall_texture;
        delete face_texture;
        delete container_diffuse_texture;
        delete container_specular_texture;
    }
    
public:
    Texture* wall_texture;
    Texture* face_texture;
    Texture* container_diffuse_texture;
    Texture* container_specular_texture;
};