#version 330 core
out vec4 FragColor;

in vec3 localPos;

uniform samplerCube environmentMap;

void main(){
    vec3 envColor=texture(environmentMap,localPos).rgb;
//    vec3 envColor=textureLod(environmentMap,localPos,4.2).rgb;//最后一个float可以指定mipmap级别
    envColor=pow(envColor/(envColor+vec3(1.0f)),vec3(1.0f/2.2f));
    FragColor=vec4(envColor,1.0f);
}
