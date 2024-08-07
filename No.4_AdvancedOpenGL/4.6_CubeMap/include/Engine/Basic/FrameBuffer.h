#pragma once
#include "Utils.h"
#include "Engine/Basic/Texture.h"
#include "Engine/Manager/MaterialManager.h"
#include "Engine/Object/Square.h"

class FrameBuffer {
public:
    /* 帧缓冲对象 */
    FrameBuffer() {
        CreateFrameBuffer();
        screen = new Square("screen", MaterialManager::GetInstance().post_process_material, NULL);
    }
    ~FrameBuffer() {
        glDeleteRenderbuffers(1, &RBO);
        glDeleteFramebuffers(1, &ID);
        delete color_buffer;
        delete screen;
    }

public:
    /* 将帧缓冲的颜色附件的内容, 绘制到屏幕上 */
    void RenderTick() {
        // 1. 禁用深度测试, 面剔除
        glDisable(GL_DEPTH_TEST);
        glDisable(GL_CULL_FACE);
        glClear(GL_COLOR_BUFFER_BIT);
        
        // 2. 绘制屏幕长方形对象
        color_buffer->Use(0);
        screen->RenderTick(NULL);

        // 3. 重新启用深度测试, 面剔除
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_CULL_FACE);
    }

public:
    /* 帧缓冲ID */
    unsigned int ID;
    /* 颜色附件(纹理) */
    Texture* color_buffer;
    /* 深度模板附件(渲染缓冲对象) ID */
    unsigned int RBO;
    /* 用于最终展示的长方形物体对象 */
    Square* screen;

private:
    void CreateFrameBuffer() {
        /* 1. 生成帧缓冲 */
        glGenFramebuffers(1, &ID);
        glBindFramebuffer(GL_FRAMEBUFFER, ID);

        /* 2. 创建纹理附件, 并将其作为颜色附件附加到帧缓冲上 */
        color_buffer = new Texture(SCR_WIDTH, SCR_HEIGHT);
        glFramebufferTexture2D(
            GL_FRAMEBUFFER,         // 帧缓冲目标
            GL_COLOR_ATTACHMENT0,   // 附件类型
            GL_TEXTURE_2D,          // 附加的纹理类型
            color_buffer->ID,       // 附加的纹理对象
            0                       // mipmap级别
        );

        /* 3. 创建渲染缓冲对象附件, 并将其作为深度和模板附件附加到帧缓冲上 */
        glGenRenderbuffers(1, &RBO);
        glBindRenderbuffer(GL_RENDERBUFFER, RBO);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, SCR_WIDTH, SCR_HEIGHT);
        glFramebufferRenderbuffer(
            GL_FRAMEBUFFER,                 // 帧缓冲目标
            GL_DEPTH_STENCIL_ATTACHMENT,    // 附件类型
            GL_RENDERBUFFER,                // 附加的渲染缓冲对象类型
            RBO                             // 附加的渲染缓冲对象
        );

        /* 4. 检查帧缓冲是否完整 */
        if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
            std::cout << "[ERROR::FrameBuffer.h::CreateFrameBuffer()] 渲染缓冲对象不完整\n";
        
        /* 5. 解除绑定 */
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }
};