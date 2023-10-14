#version 330 core
out vec4 FragColor;

in VS_OUT{
    vec3 FragPos;
    vec3 Normal;
    vec2 TexCoords;
} fs_in;

struct Light{
    vec3 Position;
    vec3 Color;
};

uniform Light lights[16];
uniform sampler2D diffuseTexture;
uniform vec3 viewPos;

void main(){
    vec3 color=texture(diffuseTexture,fs_in.TexCoords).rgb;
    vec3 normal=normalize(fs_in.Normal);
    
    vec3 ambient=0.0f*color;
    vec3 lighting=vec3(0.0f);
    for(int i=0;i<16;i++){
        vec3 lightDir=normalize(lights[i].Position-fs_in.FragPos);
        float diff=max(dot(lightDir,normal),0.0f);
        vec3 diffuse=lights[i].Color*diff*color;
        vec3 result=diffuse;
        float dis=length(fs_in.FragPos-lights[i].Position);
        result*=1.0f/(dis*dis);
        lighting+=result;
    }
    FragColor=vec4(ambient+lighting,1.0f);
}
