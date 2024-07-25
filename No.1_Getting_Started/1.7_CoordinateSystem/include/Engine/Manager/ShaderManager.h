#pragma once
#include "Engine/Basic/Shader.h"
    
class ShaderManager {
public:
    ShaderManager() {
        basic_shader = new Shader("basic");
        basic_square_shader = new Shader("basic_square");
        basic_square_3D_shader = new Shader("basic_square_3D");
        basic_cube_shader = new Shader("basic_cube");
    }
    ~ShaderManager(){
        delete basic_shader;
        delete basic_square_shader;
        delete basic_square_3D_shader;
        delete basic_cube_shader;
    }

public:
    Shader* basic_shader;
    Shader* basic_square_shader;
    Shader* basic_square_3D_shader;
    Shader* basic_cube_shader;
};