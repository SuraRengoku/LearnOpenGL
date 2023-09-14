#version 330 core
layout (location=0) in vec3 aPos;

out vec3 TexCoords;

uniform mat4 projection;
uniform mat4 view;

void main(){
    TexCoords=aPos;//使用立方体的实际位置向量来对立方体贴图进行采样
    gl_Position=projection*view*vec4(aPos,1.0f);
}

