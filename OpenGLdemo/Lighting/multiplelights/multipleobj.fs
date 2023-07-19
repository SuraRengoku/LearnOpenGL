#version 330 core
out vec4 FragColor;

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoord;

uniform vec3 viewPos;

struct Material{
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
    sampler2D emission;
};
uniform Material material;

struct DirLight{
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
uniform DirLight dirlight;
vec3 calDirLight(DirLight dirlight,vec3 normal,vec3 viewDir);

struct PointLight{
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float constant;
    float linear;
    float quadratic;
};
#define Num_PointLights 4
uniform PointLight pointlight[Num_PointLights];
vec3 calPointLight(PointLight pointlight,vec3 normal,vec3 FragPos,vec3 viewDir);

struct SpotLight{
    vec3 position;
    vec3 direction;
    float cutOff;
    float outerCutOff;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float constant;
    float linear;
    float quadratic;
};
uniform SpotLight spotlight;
vec3 calSpotLight(SpotLight spotlight,vec3 normal,vec3 FragPos, vec3 viewDir);

void main(){
    vec3 normal=normalize(Normal);
    vec3 viewDir=normalize(viewPos-FragPos);

    vec3 result=calDirLight(dirlight,normal,viewDir);
    for(int i=0;i<Num_PointLights;i++){
        result+=calPointLight(pointlight[i],normal,FragPos,viewDir);
    }
    result+=calSpotLight(spotlight,normal,FragPos,viewDir);
    
    FragColor=vec4(result,1.0f);
}

vec3 calDirLight(DirLight dirlight,vec3 normal,vec3 viewDir){
    vec3 lightDir=normalize(-dirlight.direction);
    float diff=max(dot(normal,lightDir),0.0f);
    vec3 reflectDir=reflect(-lightDir,normal);
    float spec=pow(max(dot(viewDir,reflectDir),0.0f),material.shininess);
    
    vec3 ambient=dirlight.ambient*texture(material.diffuse,TexCoord).rgb;
    vec3 diffuse=dirlight.diffuse*diff*texture(material.diffuse,TexCoord).rgb;
    vec3 specular=dirlight.specular*spec*texture(material.specular,TexCoord).rgb;
    return (ambient+diffuse+specular);
}

vec3 calPointLight(PointLight pointlight,vec3 normal,vec3 FragPos,vec3 viewDir){
    vec3 lightDir=normalize(pointlight.position-FragPos);
    float diff=max(dot(normal,lightDir),0.0f);
    vec3 reflectDir=reflect(-lightDir,normal);
    float spec=pow(max(dot(viewDir,reflectDir),0.0f),material.shininess);
    float distance_=length(pointlight.position-FragPos);
    float attenuation=1.0f/(pointlight.constant+pointlight.linear*distance_+pointlight.quadratic*pow(distance_,2));
    
    vec3 ambient=pointlight.ambient*texture(material.diffuse,TexCoord).rgb;
    vec3 diffuse=pointlight.diffuse*diff*texture(material.diffuse,TexCoord).rgb;
    vec3 specular=pointlight.specular*spec*texture(material.specular,TexCoord).rgb;
    return attenuation*(ambient+diffuse+specular);
}

vec3 calSpotLight(SpotLight spotlight,vec3 normal,vec3 FragPos, vec3 viewDir){
    vec3 lightDir=normalize(spotlight.position-FragPos);
    float distance_=length(spotlight.position-FragPos);
    float attenuation=1.0f/(spotlight.constant+spotlight.linear*distance_+spotlight.quadratic*pow(distance_,2));
    float theta=dot(lightDir,normalize(-spotlight.direction));
    float epsilon=spotlight.cutOff-spotlight.outerCutOff;
    float intensity=clamp((theta-spotlight.outerCutOff)/epsilon,0.0f,1.0f);
    float diff=max(dot(normal,lightDir),0.0f);
    vec3 reflectDir=reflect(-lightDir,normal);
    float spec=2*pow(max(dot(viewDir,reflectDir),0.0f),material.shininess);
    
    vec3 ambient=intensity*spotlight.ambient*texture(material.diffuse,TexCoord).rgb;
    vec3 diffuse=intensity*spotlight.diffuse*diff*texture(material.diffuse,TexCoord).rgb;
    vec3 specular=intensity*spotlight.specular*spec*texture(material.specular,TexCoord).rgb;
    return attenuation*(ambient+diffuse+specular);
}
