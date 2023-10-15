#version 330 core
layout (location=0) out vec4 FragColor;
layout (location=1) out vec4 BrightColor;

in VS_OUT{
    vec3 FragPos;
    vec3 Normal;
    vec2 TexCoords;
} fs_in;

struct Light{
    vec3 Position;
    vec3 Color;
};

uniform Light lights[4];
uniform sampler2D diffuseTexture;
uniform vec3 viewPos;

void main(){
    vec3 color=texture(diffuseTexture,fs_in.TexCoords).rgb;
    vec3 normal=normalize(fs_in.Normal);
    
    vec3 ambient=0.2f*color;
    //计算hdr
    vec3 lighting=vec3(0.0f);
    vec3 viewDir=normalize(viewPos-fs_in.FragPos);
    for(int i=0;i<4;i++){
        vec3 lightDir=normalize(lights[i].Position-fs_in.FragPos);
        float diff=max(dot(lightDir,normal),0.0f);
        vec3 result=lights[i].Color*diff*color;
        float dis=length(lights[i].Position-fs_in.FragPos);
        result*=1.0f/(dis*dis);
        lighting+=result;
    }
    
    FragColor=vec4(ambient+lighting,1.0f);
    float brightness=dot(FragColor.rgb,vec3(0.2126,0.7152,0.0722));
    if(brightness>1.0)
        BrightColor=vec4(FragColor.rgb,1.0f);
    else
        BrightColor=vec4(0.0f,0.0f,0.0f,1.0f);
    //泛光之所以可以和HDR配合的很好是因为HDR中高亮部分的亮度超过1.0，这让泛光很容易分辨图像中哪个部分应该呈现泛光
}
