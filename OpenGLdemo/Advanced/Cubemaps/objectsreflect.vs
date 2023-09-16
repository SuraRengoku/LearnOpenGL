#version 330 core
layout (location=0) in vec3 aPos;
layout (location=1) in vec3 aNormal;

out vec3 Normal;
out vec3 Position;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat3 normalmatrix;

void main(){
    Normal=normalmatrix*aNormal;
    Position=vec3(model*vec4(aPos,1.0f));//世界空间中位置向量坐标
    gl_Position=projection*view*model*vec4(aPos,1.0f);
}
