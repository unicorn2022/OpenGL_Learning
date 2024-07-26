#version 330 core
out vec4 FragColor;

in vec3 Position;
in vec3 Normal;
in vec2 TexCoord;

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

struct Light {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform vec3 view_position;
uniform Material material;
uniform Light light;

void main() {
    // 1. 环境光
    vec3 ambient = light.ambient * material.ambient;

    // 2. 漫反射光
    vec3 normal_dir = normalize(Normal);
    vec3 light_dir = normalize(light.position - Position);
    vec3 diffuse = max(dot(normal_dir, light_dir), 0.0) * light.diffuse * material.diffuse;

    // 3. 高光
    vec3 view_dir = normalize(view_position - Position);
    vec3 reflect_dir = reflect(-light_dir, normal_dir);
    vec3 specular = pow(max(dot(view_dir, reflect_dir), 0.0), material.shininess)  * light.specular * material.specular;

    // 最终颜色
    vec3 color = ambient + diffuse + specular;
    FragColor = vec4(color, 1.0);
}