#version 330 core
out vec4 FragColor;
in vec3 Normal;
in vec3 FragPos;

struct Material{
    vec3 ambient;//定义环境光下表面反射颜色
    vec3 diffuse;//定义漫反射光下表面颜色
    vec3 specular;//定义高光颜色
    float shininess;//反光度
};

uniform Material material;
uniform vec3 lightColor;
uniform vec3 viewPos;
uniform vec3 lightPos;

void main(){
    vec3 ambient=lightColor*material.ambient;
    
    vec3 norm=normalize(Normal);
    vec3 lightDir=normalize(lightPos-FragPos);
    float diff=max(dot(norm,lightDir),0.0f);
    vec3 diffuse=lightColor*(diff*material.diffuse);
    
    vec3 viewDir=normalize(viewPos-FragPos);
    vec3 reflectDir=reflect(-lightDir,norm);
    float spec=pow(max(dot(viewDir,reflectDir),0.0f),material.shininess);
    vec3 specular=lightColor*(spec*material.specular);
    
    vec3 result=ambient+diffuse+specular;
    FragColor=vec4(result,1.0f);
}
