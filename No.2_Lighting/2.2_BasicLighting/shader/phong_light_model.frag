#version 330 core
out vec4 FragColor;

in vec3 Position;
in vec3 Normal;
in vec2 TexCoord;

uniform vec3 view_position;
uniform vec3 object_color;

uniform vec3 light_position;
uniform vec3 light_color;

void main() {
    // 1. 环境光
    float ambient_strenth = 0.1;
    vec3 ambient = ambient_strenth * light_color;

    // 2. 漫反射光
    vec3 normal_dir = normalize(Normal);
    vec3 light_dir = normalize(light_position - Position);
    vec3 diffuse = max(dot(normal_dir, light_dir), 0.0) * light_color;

    // 3. 高光
    float specular_strenth = 0.5;
    vec3 view_dir = normalize(view_position - Position);
    vec3 reflect_dir = reflect(-light_dir, normal_dir);
    vec3 specular = pow(max(dot(view_dir, reflect_dir), 0.0), 32) * specular_strenth * light_color;

    // 最终颜色
    vec3 color = (ambient + diffuse + specular) * object_color;
    FragColor = vec4(color, 1.0);
}