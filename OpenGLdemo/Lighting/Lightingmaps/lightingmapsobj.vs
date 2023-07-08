#version 330 core
layout (location=0) in vec3 aPos;
layout (location=1) in vec3 aNormal;
layout (location=2) in vec2 aTexCoord;

out vec3 Normal;
out vec3 FragPos;
out vec2 TexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat3 normalMatrix;

void main(){
    Normal=normalMatrix*aNormal;
    FragPos=vec3(model*vec4(aPos,1.0f));//世界坐标下片段的位置
    gl_Position=projection*view*vec4(FragPos,1.0f);
    TexCoord=aTexCoord;
}
