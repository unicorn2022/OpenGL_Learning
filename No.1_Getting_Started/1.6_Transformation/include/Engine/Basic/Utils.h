#pragma once
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

static const std::string root_path = "E:/MyProject/GameEngine/OpenGL_Learning/No.1_Getting_Started/1.6_Transformation/";
static const std::string texture_root_path = root_path + "resource/texture/";
static const std::string shader_root_path = root_path + "shader/";

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
        stbi_set_flip_vertically_on_load(true);
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
    float GetValue(std::string name) {
        if (float_value.find(name) == float_value.end())
            float_value[name] = 0;
        return float_value[name];
    }    

private:
    GlobalValue(){}
    std::map<std::string, float> float_value;
};