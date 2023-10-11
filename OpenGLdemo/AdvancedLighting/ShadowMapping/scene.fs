#version 330 core
out vec4 FragColor;
in vec2 TexCoords;

uniform sampler2D depthMap;
uniform float near_plane;
uniform float far_plane;

float LinearizeDepth(float depth){
    float z=depth*2.0f-1.0f;//将[0,1]的深度范围转换为设备的[-1,1]
    return (2.0f*near_plane*far_plane)/(far_plane+near_plane-z*(far_plane-near_plane));
}

void main(){
    float depthValue=texture(depthMap,TexCoords).r;
    FragColor=vec4(vec3(LinearizeDepth(depthValue)/far_plane),1.0f);
//    FragColor=vec4(vec3(depthValue),1.0f);
}
