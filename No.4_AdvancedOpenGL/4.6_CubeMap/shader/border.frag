#version 330 core

/* 输入输出变量 */
out vec4 FragColor;

/* uniform 全局变量 */
uniform vec3 border_color;


void main() {
    FragColor = vec4(border_color, 1.0);
}