#pragma once
#include "Engine/Light/INCLUDE_ALL.h"

#define MAX_POINT_LIGHT_COUNT 4
glm::vec3 point_light_positions[MAX_POINT_LIGHT_COUNT] = {
    glm::vec3( 0.7f,  0.2f,  2.0f),
    glm::vec3( 2.3f, -3.3f, -4.0f),
    glm::vec3(-4.0f,  2.0f, -12.0f),
    glm::vec3( 0.0f,  0.0f, -3.0f)
};

class LightManager {
public:
    static LightManager& GetInstance(){
        static LightManager instance;
        return instance;
    }

private:
    LightManager() {
        direct_light = new DirectLight(
            glm::vec3(-0.2f, -1.0f, -0.3f),     // 方向
            glm::vec3(0.05f, 0.05f, 0.05f),     // 环境光
            glm::vec3(0.5f, 0.5f, 0.5f),        // 漫反射
            glm::vec3(1.0f, 1.0f, 1.0f)         // 高光
        );

        for(int i = 0; i < MAX_POINT_LIGHT_COUNT; i++) 
            point_lights[i] = new PointLight(
                point_light_positions[i],           // 位置
                glm::vec3(0.05f, 0.05f, 0.05f),     // 环境光
                glm::vec3(0.8f, 0.8f, 0.8f),        // 漫反射
                glm::vec3(1.0f, 1.0f, 1.0f)         // 高光
            );

        spot_light = new SpotLight(
            point_light_positions[0],           // 位置
            glm::vec3(-0.2f, -1.0f, -0.3f),     // 方向
            glm::vec3(0, 0, 0),                 // 环境光
            glm::vec3(20.0f, 20.0f, 20.0f),     // 漫反射
            glm::vec3(20.0f, 20.0f, 20.0f),     // 高光
            12.5f,                              // 内切角
            15.0f                               // 外切角
        );
    }
    ~LightManager(){
        delete direct_light;
        for(int i = 0; i < MAX_POINT_LIGHT_COUNT; i++) 
            delete point_lights[i];
        delete spot_light;
    }

public:
    void RenderTick(Shader* shader){ 
        direct_light->Use(shader, 0);
        for(int i = 0; i < MAX_POINT_LIGHT_COUNT; i++) 
            point_lights[i]->Use(shader, i);
        spot_light->Use(shader, 0);
    }

public:
    DirectLight* direct_light;
    PointLight* point_lights[MAX_POINT_LIGHT_COUNT];
    SpotLight* spot_light;
};