#pragma once
/* 标准库 */
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

/* OpenGL 库 */
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

/* 图片加载 */
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

/* ASSIMP 模型加载 */
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

/* 窗口信息 */
static const char* SCR_NAME = "LearnOpenGL";
static const int SCR_WIDTH = 800;
static const int SCR_HEIGHT = 800;

/* 相机信息 */
// static const glm::vec3 CAMERA_POSITION = glm::vec3(0.0f, 9.0f, 26.0f);
static const glm::vec3 CAMERA_POSITION = glm::vec3(0.0f, 0.0f, 5.0f);
static const glm::vec3 CAMERA_UP = glm::vec3(0.0f, 1.0f, 0.0f);
static const float CAMERA_ZNEAR = 0.1f;
static const float CAMERA_ZFAR = 100.0f;

/* 颜色信息 */
static const glm::vec4 COLOR_BACKGROUND = glm::vec4(0.1f, 0.1f, 0.1f, 1.0f);
static const glm::vec3 COLOR_BORDER = glm::vec3(1.0f, 0.0f, 0.0f);

/* 后期处理效果个数 */
static const int POST_PROCESS_NUM = 9;

/* 路径信息 */
// 所有章节公用资源
static const std::string root_path = "E:/MyProject/GameEngine/OpenGL_Learning/";
static const std::string resource_path = root_path + "resource/";
static const std::string texture_root_path = resource_path + "texture/";
static const std::string skybox_root_path = resource_path + "skybox/";
static const std::string model_root_path = resource_path + "model/";
// 本小节独享资源
static const std::string chapter_path = "No.4_AdvancedOpenGL/4.6_CubeMap/";
static const std::string shader_root_path = root_path + chapter_path + "shader/";


class Utils {
public:
    /**
     * 从文件中读取内容
     * \param path 文件路径
     * \return 读取到的内容
     */
    static std::string ReadFile(std::string path) {
        std::ifstream file;
        file.exceptions (std::ifstream::failbit | std::ifstream::badbit);
        try {
            // 打开文件
            file.open(path);
            // 读取字符流
            std::stringstream stream;
            stream << file.rdbuf();
            // 关闭文件
            file.close();
            // 字符流 => string
            return stream.str();
        } catch (std::ifstream::failure& e) {
            std::cout << "[ERROR::Utils.h::ReadFile()] 文件 " << path << " 读取失败: " << e.what() << std::endl;
            return "";
        }
    }

    /**
     * 从文件中读取图片
     * \param path 文件路径
     * \return 读取到的stbi图片
     */
    static unsigned char* ReadPicture(std::string path, int& width, int& height, int& channel) {
        // 是否翻转Y轴
        stbi_set_flip_vertically_on_load(false);
        // stbi加载图片
        unsigned char *data =  stbi_load(path.c_str(), &width, &height, &channel, 0);
        if (data == NULL) {
            std::cout << "[ERROR::Utils.h::ReadPicture()] 图片读取失败: " << path << std::endl;
        }
        return data;
    }
};

class GlobalValue {
public:
    static GlobalValue& GetInstance(){
        static GlobalValue instance;
        return instance;
    }

public:
    void SetValue(std::string name, float value, float min = -1e10, float max = 1e10) {
        if (value < min) value = min;
        if (value > max) value = max;
        float_value[name] = value;
    }
    void SetValue(std::string name, int value, int min = -1e10, int max = 1e10) {
        if (value < min) value = min;
        if (value > max) value = max;
        int_value[name] = value;
    }
    float GetFloatValue(std::string name) {
        if (float_value.find(name) == float_value.end())
            float_value[name] = 0;
        return float_value[name];
    }   
    int GetIntValue(std::string name) {
        if (int_value.find(name) == int_value.end())
            int_value[name] = 0;
        return int_value[name];
    }   

private:
    GlobalValue(){}
    std::map<std::string, float> float_value;
    std::map<std::string, int> int_value;
};