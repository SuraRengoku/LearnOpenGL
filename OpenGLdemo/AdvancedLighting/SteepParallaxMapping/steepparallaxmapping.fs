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

uniform float height_scale;//缩放参数，缺失该参数会导致时差过于强烈

vec2 ParallaxMapping(vec2 texCoords,vec3 viewDir){
    const float minLayers=8;
    const float maxLayers=32;
    float numlayers=mix(maxLayers,minLayers,abs(dot(vec3(0.0f,0.0f,1.0f),viewDir)));//分层数,垂直观看时采用更少的样本
    float layerDepth=1.0f/numlayers;//每层深度
    float currentLayerDepth=0.0f;
    vec2 P=viewDir.xy*height_scale;
    vec2 deltaTexCoords=P/numlayers;
    
    vec2 currentTexCoords=texCoords;
    float currentDepthMapValue=texture(displaceMap,currentTexCoords).r;
    while(currentDepthMapValue>currentLayerDepth){
        currentLayerDepth+=layerDepth;
        currentTexCoords-=deltaTexCoords;
        currentDepthMapValue=texture(displaceMap,currentTexCoords).r;
    }
    //Parallax Occlusion Mapping 视差遮蔽映射
    vec2 preTexCoords=currentTexCoords+deltaTexCoords;
    float afterDepth=currentLayerDepth-currentDepthMapValue;
    float beforeDepth=texture(displaceMap,preTexCoords).r-currentLayerDepth+layerDepth;
    float weight=afterDepth/(afterDepth+beforeDepth);
    vec2 finalTexCoords=currentTexCoords*(1.0f-weight)+preTexCoords*weight;//大权重*小坐标
    return finalTexCoords;
}

void main(){
    //计算偏移后的纹理采样坐标
    vec3 viewDir=normalize(fs_in.TangentViewPos-fs_in.TangentFragPos);
    vec2 texCoords=ParallaxMapping(fs_in.TexCoords,viewDir);
    if(texCoords.x>1.0f||texCoords.y>1.0f||texCoords.x<0.0f||texCoords.y<0.0f)
        discard;//边缘的纹理坐标偏移会导致小范围的失真，直接丢弃
    
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
