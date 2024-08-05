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
        depth_visualization_shader = new Shader("depth_visualization");
    }
    ~ShaderManager(){
        delete basic_shader;
        delete phong_light_model_shader;
        delete depth_visualization_shader;
    }

public:
    Shader* basic_shader;
    Shader* phong_light_model_shader;
    Shader* depth_visualization_shader;
};