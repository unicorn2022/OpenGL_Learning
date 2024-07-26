#pragma once
#include "Engine/Basic/Material.h"

class MaterialManager {
public:
    MaterialManager() {
        cube_material = new PhongMaterial(
            glm::vec3(1.0f, 0.5f, 0.31f),   // 环境光
            glm::vec3(1.0f, 0.5f, 0.31f),   // 漫反射
            glm::vec3(0.5f, 0.5f, 0.5f),    // 高光
            32.0f                           // 反光度
        );
    }
    ~MaterialManager(){
        delete cube_material;
    }

public:
    Material* cube_material;
};