#version 330 core
out vec3 fragmentColor;
out vec2 uv;

layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec3 vertexColor;
layout(location = 2) in vec2 originalUV;

uniform mat4 mvp;
uniform float time;

void main() {
	gl_Position = mvp * vec4(vertexPosition_modelspace, 1 );
    uv = originalUV + vec2( sin(time), cos(time) );
    fragmentColor = vec3( sin(time), cos(time), sin(time)*cos(time) ) * vertexColor;
}
