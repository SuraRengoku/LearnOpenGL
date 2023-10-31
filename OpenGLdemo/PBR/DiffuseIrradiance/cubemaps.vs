#version 330 core
layout (location=0) in vec3 aPos;

uniform mat4 projection;
uniform mat4 view;

out vec3 localPos;

void main(){
    localPos=aPos;//直接使用位置值采样
    mat4 rotView=mat4(mat3(view));//去除平移部分
    vec4 clipPos=projection*rotView*vec4(localPos,1.0f);
    gl_Position=clipPos.xyww;
}
