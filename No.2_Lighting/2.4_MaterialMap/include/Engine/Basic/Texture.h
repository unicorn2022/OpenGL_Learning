#pragma once
#include "Utils.h"

class Texture {
public:
    /** 纹理
     * \param file_name 文件名
     */
    Texture(std::string file_name) {
        std::string path = texture_root_path + file_name;
        /* 1. 绑定纹理ID */
        glGenTextures(1, &ID);
        glBindTexture(GL_TEXTURE_2D, ID);
        /* 2. 为当前绑定的纹理对象设置环绕、过滤方式 */
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);       // S轴环绕方式: 重复
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);       // T轴环绕方式: 重复
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);   // 缩小过滤方式: 线性
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);   // 放大过滤方式: 线性
        /* 3. 加载并生成纹理 */
        int width, height, channel;
        unsigned char *data = Utils::ReadPicture(path, width, height, channel);
        if (data != NULL) {
            if (channel == 1) 
                glTexImage2D(
                    GL_TEXTURE_2D,      // 纹理目标
                    0,                  // MIPMAP级别
                    GL_R8,              // 将纹理存储为何种形式
                    width, height,      // 宽高
                    0,                  // 总是0
                    GL_R8,              // 源图像通道数
                    GL_UNSIGNED_BYTE,   // 源图像数据类型
                    data                // 源图像数据
                );
            else if (channel == 2)
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RG, width, height, 0, GL_RG, GL_UNSIGNED_BYTE, data);
            else if (channel == 3)
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            else if (channel == 4)
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
            stbi_image_free(data);
        }
    }
    ~Texture() {
        glDeleteTextures(1, &ID);
    }

public:
    void Use(int index) {
        glActiveTexture(GL_TEXTURE0 + index);
        glBindTexture(GL_TEXTURE_2D, ID);
    }

protected:
    /* 纹理ID */
    unsigned int ID;
};