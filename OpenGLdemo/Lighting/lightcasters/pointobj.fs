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
    float diff=max(dot(norm,lightDir),0.0f);
    vec3 diffuse=light.diffuse*diff*texture(material.diffuse,TexCoord).rgb;
    
    vec3 viewDir=normalize(viewPos-FragPos);
    vec3 reflectDir=reflect(-lightDir,norm);
    float spec=pow(max(dot(viewDir,reflectDir),0.0f),material.shininess);
    vec3 specular=light.specular*spec*texture(material.specular,TexCoord).rgb;
    
    float distance_=length(light.position-FragPos);
    float attenuation=1.0f/(light.constant+light.linear*distance_+light.quadratic*pow(distance_,2));
    
    FragColor=vec4((ambient+diffuse+specular)*attenuation,1.0f);
}


