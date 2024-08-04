#pragma once
#include "TextureManager.h"
#include "ShaderManager.h"
#include "Engine/Material/INCLUDE_ALL.h"

class MaterialManager {
public:
    static MaterialManager& GetInstance(){
        static MaterialManager instance;
        return instance;
    }

    void AddOBJMaterial(Material* material) {
        obj_model_materials.push_back(material);
    }

private:
    MaterialManager() {
        light_cube_material = new BasicMaterial(
            ShaderManager::GetInstance().basic_shader,
            glm::vec3(1.0f)
        );
        container_material = new PhongMaterial(
            ShaderManager::GetInstance().phong_light_model_shader,       // 着色器程序
            TextureManager::GetInstance().container_diffuse_texture,     // 漫反射
            TextureManager::GetInstance().container_specular_texture,    // 高光
            32.0f                                           // 反光度
        );
    }
    ~MaterialManager(){
        delete light_cube_material;
        delete container_material;
        for (auto material : obj_model_materials) 
            delete material;
        obj_model_materials.clear();
    }

public:
    Material* light_cube_material;
    Material* container_material;
    std::vector<Material*> obj_model_materials;
};