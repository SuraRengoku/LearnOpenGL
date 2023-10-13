#version 330 core
layout (location=0) in vec3 aPos;
layout (location=1) in vec3 aNormal;
layout (location=2) in vec2 aTexCoords;
layout (location=3) in vec3 aTangent;
layout (location=4) in vec3 aBitangent;

out VS_OUT{
    vec3 FragPos;
    vec2 TexCoords;
    vec3 TangentLightPos;
    vec3 TangentViewPos;
    vec3 TangentFragPos;
} vs_out;

uniform vec3 lightPos;
uniform vec3 viewPos;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;
uniform mat3 normalMatrix;

void main(){
    vec3 T=normalize(normalMatrix*aTangent);
    vec3 B=normalize(normalMatrix*aBitangent);
    vec3 N=normalize(normalMatrix*aNormal);
    mat3 TBN=transpose(mat3(T,B,N));
    gl_Position=projection*view*model*vec4(aPos,1.0f);
    vs_out.FragPos=vec3(model*vec4(aPos,1.0f));
    vs_out.TexCoords=aTexCoords;
    //将其他光相关向量转变到切线空间
    vs_out.TangentLightPos=TBN*lightPos;
    vs_out.TangentViewPos=TBN*viewPos;
    vs_out.TangentFragPos=TBN*vs_out.FragPos;
    //viewPos和lightPos不是对于每个fragment都要更新，且顶点着色器运行次数明显小于片段着色器
}
