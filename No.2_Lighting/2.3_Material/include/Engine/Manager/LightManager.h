#pragma once
#include "Engine/Basic/Light.h"

class LightManager {
public:
    LightManager() {
        point_light = new PointLight(
            glm::vec3(1.2f, 1.0f, 2.0f),    // 位置
            glm::vec3(0.5f, 0.5f, 0.5f),    // 环境光
            glm::vec3(0.2f, 0.2f, 0.2f),    // 漫反射
            glm::vec3(1.0f, 1.0f, 1.0f)     // 高光
        );
    }
    ~LightManager(){
        delete point_light;
    }

public:
    Light* point_light;
};