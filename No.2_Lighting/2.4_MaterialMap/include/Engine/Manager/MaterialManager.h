#pragma once
#include "TextureManager.h"
#include "Engine/Basic/Material.h"

class MaterialManager {
public:
    MaterialManager(TextureManager* texture_manager) {
        light_cube_material = new BasicMaterial(glm::vec3(1.0f));
        container_material = new PhongMaterial(
            texture_manager->container_diffuse_texture,     // 漫反射
            texture_manager->container_specular_texture,    // 高光
            32.0f                                           // 反光度
        );
    }
    ~MaterialManager(){
        delete light_cube_material;
        delete container_material;
    }

public:
    Material* light_cube_material;
    Material* container_material;
};