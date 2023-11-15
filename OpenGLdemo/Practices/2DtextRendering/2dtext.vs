#version 330 core
layout (location=0) in vec4 vertex;//包含了顶点和纹理坐标
out vec2 TexCoords;

uniform mat4 projection;

void main(){
    gl_Position=projection*vec4(vertex.xy,0.0f,1.0f);
    TexCoords=vertex.zw;
}
