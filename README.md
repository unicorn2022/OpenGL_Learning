[TOC]

# OpenGL_Learning

学习OpenGL，教程地址：https://learnopengl-cn.github.io/

# 对VSCode的配置

## 设置编译工具&构建工具

> ctrl + shift + p > cmake: scan for kits

- 扫描工具包

> ctrl + shift + p > cmake: select a kit

- 设置工具包为：**VS x86_amd64**

## 解决输出乱码问题

> ctrl + , > cmake: output log encoding

- 设置输出日志编码为：**utf-8**

## 解决代码补全问题

- 安装**C/C++**扩展
- 设置扩展的编译器路径为：**D:\Program\VS\Community\VC\Tools\MSVC\14.40.33807\bin\Hostx64\x64\cl.exe**
- 设置扩展的包含路径为：**E:\MyProject\GameEngine\OpenGL_Learning\3rd-party\\\*\***

## 解决终端乱码问题

- 在vscode的终端中，将编码临时修改为utf-8

```bash
chcp 650001
```

