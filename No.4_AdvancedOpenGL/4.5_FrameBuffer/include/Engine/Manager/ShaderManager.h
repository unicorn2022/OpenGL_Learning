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
        border_shader = new Shader("border");
        post_process_shader = new Shader("post_process");
    }
    ~ShaderManager(){
        delete basic_shader;
        delete phong_light_model_shader;
        delete depth_visualization_shader;
        delete border_shader;
        delete post_process_shader;
    }

public:
    Shader* basic_shader;               // 基础shader
    Shader* phong_light_model_shader;   // Phong 光照模型
    Shader* depth_visualization_shader; // 深度可视化
    Shader* border_shader;              // 轮廓
    Shader* post_process_shader;        // 后处理
};