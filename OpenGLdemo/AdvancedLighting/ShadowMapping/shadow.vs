#version 330 core
layout (location=0) in vec3 aPos;
layout (location=1) in vec3 aNormal;
layout (location=2) in vec2 aTexCoords;

out vec2 TexCoords;

out VS_OUT{
    vec3 FragPos;
    vec3 Normal;
    vec2 TexCoords;
    vec4 FragPosLightSpace;
} vs_out;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;
uniform mat4 lightSpaceMatrix;
uniform mat3 normalMatrix;

void main(){
    gl_Position=projection*view*model*vec4(aPos,1.0f);
    vs_out.FragPos=vec3(model*vec4(aPos,1.0f));
    vs_out.Normal=normalMatrix*aNormal;
    vs_out.TexCoords=aTexCoords;
    vs_out.FragPosLightSpace=lightSpaceMatrix*vec4(vs_out.FragPos,1.0f);//将世界空间顶点位置转换为光空间
}
