#version 330 core
layout (location=0) in vec3 position;
layout (location=1) in vec3 normal;
layout (location=2) in vec2 texCoords;

out vec2 TexCoords;

out VS_OUT{
    vec3 FragPos;
    vec3 Normal;
    vec2 TexCoords;
} vs_out;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;
uniform mat3 normalMatrix;

uniform bool reverse_normals;

void main(){
    gl_Position=projection*view*model*vec4(position,1.0f);
    vs_out.FragPos=vec3(model*vec4(position,1.0f));
    if(reverse_normals)
        vs_out.Normal=normalMatrix*(-1*normal);
    else
        vs_out.Normal=normalMatrix*normal;
    vs_out.TexCoords=texCoords;
}
