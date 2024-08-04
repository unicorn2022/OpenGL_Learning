#pragma once
#include "Engine/Basic/Texture.h"
    
class TextureManager {
public:
    static TextureManager& GetInstance(){
        static TextureManager instance;
        return instance;
    }
    
    Texture* AddOBJTexture(std::string root_directory, std::string file_name) {
        /* 已经加载过该纹理 */
        std::string path = root_directory + file_name;
        for (auto texture : obj_model_texture) 
            if (texture->path == path) return texture;
        
        /* 创建新纹理 */
        Texture* texture = new Texture(root_directory, file_name);
        obj_model_texture.push_back(texture);
        return texture;
    }

private:
    TextureManager() {
        wall_texture = new Texture(texture_root_path, "wall", "jpg");
        face_texture = new Texture(texture_root_path, "face", "png");
        container_diffuse_texture = new Texture(texture_root_path, "container_diffuse", "png");
        container_specular_texture = new Texture(texture_root_path, "container_specular", "png");
    }
    ~TextureManager(){
        delete wall_texture;
        delete face_texture;
        delete container_diffuse_texture;
        delete container_specular_texture;
        for (auto texture : obj_model_texture)
            delete texture;
        obj_model_texture.clear();
    }
    
public:
    Texture* wall_texture;
    Texture* face_texture;
    Texture* container_diffuse_texture;
    Texture* container_specular_texture;
    std::vector<Texture*> obj_model_texture;
};