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

struct Light{
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform Light light;
uniform Material material;
uniform vec3 viewPos;
uniform vec3 lightPos;

void main(){
    vec3 ambient=light.ambient*material.ambient;
    
    vec3 norm=normalize(Normal);
    vec3 lightDir=normalize(light.position-FragPos);
    float diff=max(dot(norm,lightDir),0.0f);
    vec3 diffuse=light.diffuse*(diff*material.diffuse);
    
    vec3 viewDir=normalize(viewPos-FragPos);
    vec3 reflectDir=reflect(-lightDir,norm);
    float spec=pow(max(dot(viewDir,reflectDir),0.0f),material.shininess);
    vec3 specular=light.specular*(spec*material.specular);
    
    vec3 result=ambient+diffuse+specular;
    FragColor=vec4(result,1.0f);
}
