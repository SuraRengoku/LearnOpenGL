#version 330 core
out vec4 FragColor;

in vec3 localPos;

uniform samplerCube environmentMap;

void main(){
    vec3 envColor=texture(environmentMap,localPos).rgb;
    envColor=pow(envColor/(envColor+vec3(1.0f)),vec3(1.0f/2.2f));
    FragColor=vec4(envColor,1.0f);
}
