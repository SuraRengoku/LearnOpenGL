#version 330 core
layout (location=0) in vec3 aPos;
layout (location=2) in vec2 aTexCoords;

layout (std140) uniform Matirces{
    mat4 projection;
};

out VS_OUT{
    vec2 texCoords;
} vs_out;

uniform mat4 view;
uniform mat4 model;

void main(){
    vs_out.texCoords=aTexCoords;
    gl_Position=projection*view*model*vec4(aPos,1.0f);
}
