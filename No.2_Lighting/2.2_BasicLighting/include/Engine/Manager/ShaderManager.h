#pragma once
#include "Engine/Basic/Shader.h"
    
class ShaderManager {
public:
    ShaderManager() {
        light_cube_shader = new Shader("light_cube");
        phong_light_model_shader = new Shader("phong_light_model");
    }
    ~ShaderManager(){
        delete light_cube_shader;
        delete phong_light_model_shader;
    }

public:
    Shader* light_cube_shader;
    Shader* phong_light_model_shader;
};