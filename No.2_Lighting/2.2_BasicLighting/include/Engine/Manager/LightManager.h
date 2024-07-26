#pragma once
#include "Engine/Basic/Light.h"

class LightManager {
public:
    LightManager() {
        point_light = new PointLight(glm::vec3(1.2f, 1.0f, 2.0f), glm::vec3(1.0f, 1.0f, 1.0f));
    }
    ~LightManager(){
        delete point_light;
    }

public:
    Light* point_light;
};