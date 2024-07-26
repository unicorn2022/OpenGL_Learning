#pragma once
#include "Engine/Basic/Shader.h"
    
class ShaderManager {
public:
    ShaderManager() {
        /* 1.basic */
        basic_shader = new Shader("1.basic/basic");
        basic_square_shader = new Shader("1.basic/basic_square");
        basic_square_3D_shader = new Shader("1.basic/basic_square_3D");
        basic_cube_shader = new Shader("1.basic/basic_cube");
        /* 2.light */
        light_shader = new Shader("2.light/light");
        lighted_cube_shader = new Shader("2.light/lighted_cube");
    }
    ~ShaderManager(){
        /* 1.basic */
        delete basic_shader;
        delete basic_square_shader;
        delete basic_square_3D_shader;
        delete basic_cube_shader;
        /* 2.light */
        delete light_shader;
        delete lighted_cube_shader;
    }

public:
    /* 1.basic */
    Shader* basic_shader;
    Shader* basic_square_shader;
    Shader* basic_square_3D_shader;
    Shader* basic_cube_shader;
    /* 2.light */
    Shader* light_shader;
    Shader* lighted_cube_shader;
};