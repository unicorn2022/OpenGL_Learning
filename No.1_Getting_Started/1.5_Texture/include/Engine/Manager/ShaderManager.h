#pragma once
#include "Engine/Basic/Shader.h"
    
class ShaderManager {
public:
    ShaderManager() {
        basic_shader = new Shader(
            shader_root_path + "basic.vert", 
            shader_root_path + "basic.frag"
        );
        basic_texture_shader = new Shader(
            shader_root_path + "basic_texture.vert", 
            shader_root_path + "basic_texture.frag"
        );
    }
    ~ShaderManager(){
        delete basic_shader;
        delete basic_texture_shader;
    }

public:
    Shader* basic_shader;
    Shader* basic_texture_shader;
};