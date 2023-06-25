#version 330 core
layout (location=0) in vec3 aPos;
layout (location=1) in vec3 aNormal;
out vec3 Normal;
out vec3 FragPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat3 normalMatrix;

void main(){
    FragPos=vec3(model*vec4(aPos,1.0f));
    //Normal=aNormal;
    Normal=normalMatrix*aNormal;
    //Normal=mat3(transpose(inverse(model)))*aNormal;//前半部分是法线矩阵
    //矩阵求逆是一项对于着色器开销很大的运算，尽量在CPU上运算完成再通过uniform传入着色器
    gl_Position=projection*view*vec4(FragPos,1.0f);
}
