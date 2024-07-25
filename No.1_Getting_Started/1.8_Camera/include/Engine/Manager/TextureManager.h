#pragma once
#include "Engine/Basic/Texture.h"
    
class TextureManager {
public:
    TextureManager() {
        wall_texture = new Texture(texture_root_path + "wall.jpg");
        face_texture = new Texture(texture_root_path + "face.png");
    }
    ~TextureManager(){
        delete wall_texture;
        delete face_texture;
    }
    
public:
    Texture* wall_texture;
    Texture* face_texture;
};