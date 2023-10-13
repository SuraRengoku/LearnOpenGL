#version 330 core
out vec4 FragColor;

in VS_OUT{
    vec3 FragPos;
    vec2 TexCoords;
    vec3 TangentLightPos;
    vec3 TangentViewPos;
    vec3 TangentFragPos;
} fs_in;

uniform sampler2D diffuseMap;
uniform sampler2D normalMap;
uniform sampler2D displaceMap;

uniform float height_scale;

vec2 ParallaxMapping(vec2 texCoords,vec3 viewDir){
    float height=texture(displaceMap,texCoords).r;
    vec2 p=viewDir.xy/viewDir.z*(height*height_scale);
    return texCoords-p;
}

void main(){
    //计算偏移后的纹理采样坐标
    vec3 viewDir=normalize(fs_in.TangentViewPos-fs_in.TangentFragPos);
    vec2 texCoords=ParallaxMapping(fs_in.TexCoords,viewDir);
    
    vec3 normal=texture(normalMap,texCoords).rgb;
    normal=normalize(normal*2.0f-1.0f);
    vec3 color=texture(diffuseMap,texCoords).rgb;
    vec3 ambient=0.1f*color;
    vec3 lightDir=normalize(fs_in.TangentLightPos-fs_in.TangentFragPos);
    float diff=max(dot(lightDir,normal),0.0f);
    vec3 diffuse=diff*color;
    vec3 reflectDir=reflect(-lightDir,normal);
    vec3 halfwayDir=normalize(lightDir+viewDir);
    float spec=pow(max(dot(normal,halfwayDir),0.0f),32.0f);
    vec3 specular=vec3(0.2f)*spec;
    
    FragColor=vec4(ambient+diffuse+specular,1.0f);
}
