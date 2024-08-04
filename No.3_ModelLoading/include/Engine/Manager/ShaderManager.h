#pragma once
#include "Engine/Basic/Shader.h"
    
class ShaderManager {
public:
    static ShaderManager& GetInstance(){
        static ShaderManager instance;
        return instance;
    }

private:
    ShaderManager() {
        basic_shader = new Shader("basic");
        phong_light_model_shader = new Shader("phong_light_model");
    }
    ~ShaderManager(){
        delete basic_shader;
        delete phong_light_model_shader;
    }

public:
    Shader* basic_shader;
    Shader* phong_light_model_shader;
};