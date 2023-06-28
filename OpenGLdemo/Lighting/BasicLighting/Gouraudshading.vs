#version 330 core
layout (location=0) in vec3 aPos;
layout (location=1) in vec3 aNormal;

out vec3 LightingColor;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat3 normalMatrix;
uniform vec3 lightPos;
uniform vec3 viewPos;
uniform vec3 lightColor;

void main(){
    vec3 Position=vec3(model*vec4(aPos,1.0f));
    vec3 Normal=normalMatrix*aNormal;
    gl_Position=projection*view*vec4(Position,1.0f);
    
    float ambientStrength=0.1;
    vec3 ambient=ambientStrength*lightColor;
    
    vec3 norm=normalize(Normal);
    vec3 lightDir=normalize(lightPos-Position);
    float diff=max(dot(norm,lightDir),0.0f);
    vec3 diffuse=diff*lightColor;
    
    float specularStrength=0.7f;
    vec3 viewDir=normalize(viewPos-Position);
    vec3 reflectDir=reflect(-lightDir,norm);
    float spec=pow(max(dot(viewDir,reflectDir),0.0f),128);
    vec3 specular=specularStrength*spec*lightColor;
    
    LightingColor=ambient+diffuse+specular;
}
