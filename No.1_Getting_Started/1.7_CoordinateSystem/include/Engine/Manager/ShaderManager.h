#pragma once
#include "Engine/Basic/Shader.h"
    
class ShaderManager {
public:
    ShaderManager() {
        basic_shader = new Shader("basic");
        basic_texture_shader = new Shader("basic_texture");
        basic_3D_shader = new Shader("basic_3D");
    }
    ~ShaderManager(){
        delete basic_shader;
        delete basic_texture_shader;
        delete basic_3D_shader;
    }

public:
    Shader* basic_shader;
    Shader* basic_texture_shader;
    Shader* basic_3D_shader;
};