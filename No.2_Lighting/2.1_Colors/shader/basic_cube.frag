#version 330 core
out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D wall_texture;
uniform sampler2D face_texture;
uniform float mix_rate;

void main() {
    FragColor = mix(texture(wall_texture, TexCoord), texture(face_texture, TexCoord), mix_rate);
}