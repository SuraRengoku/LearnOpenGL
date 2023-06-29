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
    Normal=normalMatrix*aNormal;
    gl_Position=projection*view*vec4(FragPos,1.0f);
}
//该文件同样可以作为光源的顶点着色器，尽管其中有些uniform变量并没有从主程序中接收到参数，但是其会以默认参数运行
