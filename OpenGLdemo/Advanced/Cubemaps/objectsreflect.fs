#version 330 core
out vec4 FragColor;

in vec3 Normal;
in vec3 Position;

uniform vec3 cameraPos;
uniform samplerCube skybox;

void main(){
    vec3 I=normalize(Position-cameraPos);//观察点到反射点
    vec3 R=reflect(I,normalize(Normal));//反射点到采样点
    FragColor=vec4(texture(skybox,R).rgb,1.0f);
}
