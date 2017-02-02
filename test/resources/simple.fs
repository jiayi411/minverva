#version 330 core
out vec3 color;
in vec3 fragmentColor;
in vec2 uv;

uniform sampler2D textureSampler;

void main(){
//    color = fragmentColor;
    color = texture( textureSampler, uv ).wyz + fragmentColor;
}
