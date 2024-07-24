#pragma once
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

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
            std::cout << "[ERROR::Utils.h::ReadFile()] 文件读取失败: " << e.what() << std::endl;
            return "";
        }
    }
};