#pragma once
#include "TextureManager.h"
#include "ShaderManager.h"
#include "Engine/Material/INCLUDE_ALL.h"

class MaterialManager {
public:
    static MaterialManager& GetInstance(){
        static MaterialManager instance;
        return instance;
    }

    void AddOBJMaterial(Material* material) {
        obj_model_materials.push_back(material);
    }

private:
    MaterialManager() {
        /* 通用材质 */
        basic_material = new BasicMaterial(
            ShaderManager::GetInstance().basic_shader,
            glm::vec3(1.0f)
        );
        depth_visualization_material = new DepthVisualizationMaterial(
            ShaderManager::GetInstance().depth_visualization_shader
        );
        border_material = new BorderMaterial( 
            ShaderManager::GetInstance().border_shader
        );

        /* 特定材质 */
        container_material = new PhongMaterial(
            ShaderManager::GetInstance().phong_light_model_shader,       // 着色器程序
            TextureManager::GetInstance().container_diffuse_texture,     // 漫反射
            TextureManager::GetInstance().container_specular_texture,    // 高光
            32.0f                                                        // 反光度
        );
        window_material = new PhongMaterial(
            ShaderManager::GetInstance().phong_light_model_shader,
            TextureManager::GetInstance().window_texture,
            TextureManager::GetInstance().window_texture,
            32.0f
        );

        /* 帧缓冲材质 */
        post_process_material = new PostProcessMaterial(
            ShaderManager::GetInstance().post_process_shader
        );
        skybox_material = new SkyboxMaterial(
            ShaderManager::GetInstance().skybox_shader,
            TextureManager::GetInstance().skybox_texture
        );
    }
    ~MaterialManager(){
        /* 通用材质 */
        delete basic_material;
        delete depth_visualization_material;
        delete border_material;

        /* 特定材质 */
        delete container_material;
        delete window_material;
        for (auto material : obj_model_materials) delete material;
        obj_model_materials.clear();
        
        /* 帧缓冲材质 */
        delete post_process_material;
        delete skybox_material;
    }

public:
    /* 通用材质 */
    Material* basic_material;               // (通用) 基础材质
    Material* depth_visualization_material; // (通用) 深度可视化材质
    Material* border_material;              // (通用) 轮廓材质
    /* 特定材质 */
    Material* container_material;               // 箱子的材质
    Material* window_material;                  // 窗口的材质
    std::vector<Material*> obj_model_materials; // OBJ模型的材质
    /* 帧缓冲材质 */
    Material* post_process_material;// 后处理材质
    Material* skybox_material;      // 天空盒材质
};