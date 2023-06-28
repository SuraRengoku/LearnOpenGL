#version 330 core
out vec4 FragColor;

in vec3 FragPos;
in vec3 Normal;
in vec3 LightPos;

uniform vec3 objectColor;
uniform vec3 lightColor;

void main(){
    float ambientStrength=0.1;
    vec3 ambient=ambientStrength*lightColor;
    
    vec3 norm=normalize(Normal);
    vec3 lightDir=normalize(LightPos-FragPos);
    float diff=max(dot(norm,lightDir),0.0f);
    vec3 diffuse=diff*lightColor;
    
    float specularStrength=0.7f;
    vec3 viewDir=normalize(-FragPos);//the viewer is always at (0,0,0) in view-space, so viewDir is (0,0,0)-Position=>-Position
    vec3 reflectDir=reflect(-lightDir,norm);
    float spec=pow(max(dot(viewDir,reflectDir),0.0f),128);
    vec3 specular=specularStrength*spec*lightColor;
    
    vec3 result=(ambient+diffuse+specular)*objectColor;
    FragColor=vec4(result,1.0f);
}
