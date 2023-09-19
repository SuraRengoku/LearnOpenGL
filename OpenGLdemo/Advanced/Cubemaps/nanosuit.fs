#version 330 core
out vec4 FragColor;

in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;

struct Light{
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform sampler2D texture_diffuse1;
uniform sampler2D texture_specular1;
uniform sampler2D texture_reflect1;
uniform samplerCube skybox;
uniform Light light;
uniform vec3 cameraPos;
uniform float shininess;
uniform float refractratio;
uniform int mode;//default/reflect/refract

vec4 defa(){
    vec4 diffuse=texture(texture_diffuse1,TexCoord);
    vec4 specular=texture(texture_specular1,TexCoord);
    return diffuse+specular;
}

vec4 refl(){
    vec3 Iref=normalize(FragPos-cameraPos);
    vec3 Rref=reflect(Iref,normalize(Normal));
    return vec4(texture(skybox,Rref).rgb,1.0f);
}

vec4 refr(){
    vec3 Irefr=normalize(FragPos-cameraPos);
    vec3 Rrefr=refract(Irefr,normalize(Normal),refractratio);
    return vec4(texture(skybox,Rrefr).rgb,1.0f);
}

vec4 reflmap(){
    vec3 ambient=light.ambient*texture(texture_diffuse1,TexCoord).rgb;
    vec3 norm=normalize(Normal);
    vec3 lightDir=normalize(light.position-FragPos);
    float diff=max(dot(norm,lightDir),0.0f);
    vec3 diffuse=light.diffuse*diff*texture(texture_diffuse1,TexCoord).rgb;
    vec3 viewDir=normalize(cameraPos-FragPos);
    vec3 reflectDir=reflect(-lightDir,norm);
    float spec=pow(max(dot(viewDir,reflectDir),0.0f),shininess);
    vec3 specular=light.specular*spec*texture(texture_specular1,TexCoord).rgb;
    
    vec3 R=reflect(-viewDir,norm);
    vec3 reflection=vec3(texture(texture_reflect1,TexCoord))*vec3(texture(skybox,R).rgb);
    return vec4(ambient+diffuse+specular+reflection,1.0f);
//    return vec4(ambient+diffuse+specular,1.0f);
}

void main(){
    switch (mode) {
        case 1:
            FragColor=refl();
            break;
        case 2:
            FragColor=refr();
            break;
        case 3:
            FragColor=reflmap();
            break;
        default:
            FragColor=defa();
            break;
   }
}
