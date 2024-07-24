#pragma once
#include "Engine/Basic/Shader.h"

static const std::string shader_root_path = "E:/MyProject/GameEngine/OpenGL_Learning/No.1_Getting_Started/1.4_Shaders/shader/";
class ShaderManager {
public:
    ShaderManager() {
        basic_shader = new Shader(
            shader_root_path + "basic.vert", 
            shader_root_path + "basic.frag"
        );
    }
    ~ShaderManager(){
        delete basic_shader;
    }

public:
    Shader* GetBasicShader(){
        return basic_shader;
    }

private:
    Shader* basic_shader;
};