#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D gPositionDepth;
uniform sampler2D gNormal;
uniform sampler2D gAlbedoSpec;
uniform sampler2D ssaoblur;

struct Light{
    vec3 Position;
    vec3 Color;
    float Linear;
    float Quadratic;
    float Radius;
};
uniform Light light;
//uniform vec3 viewPos;

void main(){
    vec3 FragPos=texture(gPositionDepth,TexCoords).rgb;
    vec3 Normal=texture(gNormal,TexCoords).rgb;
    vec3 Diffuse=texture(gAlbedoSpec,TexCoords).rgb;
//    float Specular=texture(gAlbedoSpec,TexCoords).a;
    vec3 Specular=Diffuse;
    float AmbientOcclusion=texture(ssaoblur,TexCoords).r;

    //Blinn-Phong
    vec3 ambient=vec3(0.3f*AmbientOcclusion);//加上遮蔽因子
//    vec3 lighting=ambient;
    vec3 lighting=Diffuse*0.1f;
//    vec3 viewDir=normalize(viewPos-FragPos);
    vec3 viewDir=normalize(-FragPos);
    vec3 lightDir=normalize(light.Position-FragPos);
    vec3 diffuse=max(dot(Normal,lightDir),0.0f)*Diffuse*light.Color;
    vec3 halfwayDir=normalize(lightDir+viewDir);
    float spec=pow(max(dot(Normal,halfwayDir),0.0f),16.0f);
    vec3 specular=light.Color*spec*Specular;
    float dist=length(light.Position-FragPos);
    float attenuation=1.0f/(1.0f+light.Linear*dist+light.Quadratic*dist*dist);
    diffuse*=attenuation;
    specular*=attenuation;
    lighting+=diffuse+specular;
    lighting=lighting/(lighting+vec3(1.0f));//Reinhard Mapping
    FragColor=vec4(lighting+ambient,1.0f);
}


