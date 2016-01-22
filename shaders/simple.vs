#version 330 core

layout(location = 0) in vec4 vertexPosition_modelspace;
layout(location = 1) in vec2 uv;


uniform mat4 MVP;
out vec2 uvFrag;

void main() {
    gl_Position = MVP * vertexPosition_modelspace;
    uvFrag = uv;
}