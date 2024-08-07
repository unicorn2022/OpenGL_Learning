#pragma once
#include "Engine/Basic/Texture.h"
#include "Engine/Basic/TextureCube.h"
    
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
        grass_texture = new Texture(texture_root_path, "grass", "png");
        window_texture = new Texture(texture_root_path, "window", "png");

        container_diffuse_texture = new Texture(texture_root_path, "container_diffuse", "png");
        container_specular_texture = new Texture(texture_root_path, "container_specular", "png");

        std::string skybox_file_name[6] = {"right", "left", "top", "bottom", "front", "back"};
        skybox_texture = new TextureCube(skybox_root_path, skybox_file_name, "jpg");
    }
    ~TextureManager(){
        delete wall_texture;
        delete face_texture;
        delete grass_texture;
        delete window_texture;
        delete container_diffuse_texture;
        delete container_specular_texture;
        for (auto texture : obj_model_texture)
            delete texture;
        obj_model_texture.clear();
        delete skybox_texture;
    }
    
public:
    Texture* wall_texture;
    Texture* face_texture;
    Texture* grass_texture;
    Texture* window_texture;
    Texture* container_diffuse_texture;
    Texture* container_specular_texture;
    std::vector<Texture*> obj_model_texture;
    TextureCube* skybox_texture;
};