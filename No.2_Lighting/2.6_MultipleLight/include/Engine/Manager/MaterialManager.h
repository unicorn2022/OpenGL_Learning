#pragma once
#include "TextureManager.h"
#include "ShaderManager.h"
#include "Engine/Material/INCLUDE_ALL.h"

class MaterialManager {
public:
    MaterialManager(ShaderManager* shader_manager, TextureManager* texture_manager) {
        light_cube_material = new BasicMaterial(
            shader_manager->basic_shader,
            glm::vec3(1.0f)
        );
        container_material = new PhongMaterial(
            shader_manager->phong_light_model_shader,       // 着色器程序
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