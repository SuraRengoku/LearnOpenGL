#version 330 core
layout (location=0) in vec3 aPos;

out vec3 TexCoords;

uniform mat4 projection;
uniform mat4 view;

void main(){
    TexCoords=aPos;//使用立方体的实际位置向量来对立方体贴图进行采样
    vec4 pos=projection*view*vec4(aPos,1.0f);
    gl_Position=pos.xyww;//将顶点的z分量设置成w，这样每个顶点的深度值就是w/w=1.0f为最大，这将保证天空盒不会复写场景中的其他物体
}

