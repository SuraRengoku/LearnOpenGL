#version 330 core
out vec4 FragColor;

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoord;

struct Material{
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};

struct Light{
    vec3 position;
    vec3 direction;
    float cutOff;//聚光灯内切角
    float outerCutOff;//聚光灯外切角
    
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    
    float constant;
    float linear;
    float quadratic;
};

uniform vec3 viewPos;
uniform Material material;
uniform Light light;

void main(){
    vec3 ambient=light.ambient*texture(material.diffuse,TexCoord).rgb;
    
    vec3 norm=normalize(Normal);
    vec3 lightDir=normalize(light.position-FragPos);
    
    float distance_=length(light.position-FragPos);
    float attenuation=1.0f/(light.constant+light.linear*distance_+light.quadratic*pow(distance_,2));
    
    float theta=dot(lightDir,normalize(-light.direction));
    float epsilon=light.cutOff-light.outerCutOff;
    float intensity=clamp((theta-light.outerCutOff)/epsilon,0.0f,1.0f);//clamp函数约束计算值在[0.0f,1.0f]之间
    
    float diff=max(dot(norm,lightDir),0.0f);
    vec3 diffuse=intensity*light.diffuse*diff*texture(material.diffuse,TexCoord).rgb;
    vec3 viewDir=normalize(viewPos-FragPos);
    vec3 reflectDir=reflect(-lightDir,norm);
    float spec=2*pow(max(dot(viewDir,reflectDir),0.0f),material.shininess);
    vec3 specular=intensity*light.specular*spec*texture(material.specular,TexCoord).rgb;
        
    FragColor=vec4((ambient+diffuse+specular)*attenuation,1.0f);
}
