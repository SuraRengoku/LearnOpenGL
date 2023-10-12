#version 330 core
out vec4 FragColor;

in VS_OUT{
    vec3 FragPos;
    vec3 Normal;
    vec2 TexCoords;
} fs_in;

uniform sampler2D diffuseTexture;
uniform samplerCube depthCubeMap;

uniform vec3 lightPos;
uniform vec3 viewPos;

uniform bool shadows;
uniform float far_plane;

const vec3 sampleOffsetDirections[20]=vec3[](
    vec3(1,1,1),vec3(1,-1,1),vec3(-1,-1,1),vec3(-1,1,1),
    vec3(1,1,-1),vec3(1,-1,-1),vec3(-1,-1,-1),vec3(-1,1,-1),
    vec3(1,1,0),vec3(1,-1,0),vec3(-1,-1,0),vec3(-1,1,0),
    vec3(1,0,1),vec3(-1,0,1),vec3(1,0,-1),vec3(-1,0,-1),
    vec3(0,1,1),vec3(0,-1,1),vec3(0,-1,-1),vec3(0,1,-1)
);//每个采样方向向量都指向不同的方向以保证完全包裹计算点
//与PCF算法相比，采样点显著减少

float ShadowCalculation(vec3 fragPos){
    vec3 fragToLight=fragPos-lightPos;
    float closestDepth=texture(depthCubeMap,fragToLight).r;
    //使用方向向量对立方体贴图进行采样，方向向量不需要是单位向量
    closestDepth*=far_plane;
    float currentDepth=length(fragToLight);
    float bias=0.05f;
    int samples=20;
//    float shadow=currentDepth-bias>closestDepth?1.0f:0.0f;
    float shadow=0.0f;
    float viewDistance=length(viewPos-fragPos);
    float diskRadius=(1.0+(viewDistance/far_plane))/25.0;//限制采样范围, 根据观察者位置调整采样范围
    for(int i=0;i<samples;i++){
        float closestDepth=texture(depthCubeMap,fragToLight+sampleOffsetDirections[i]*diskRadius).r;//depth贴图每一个像素只有一个深度通道
        closestDepth*=far_plane;
        if(currentDepth-bias>closestDepth)
            shadow+=1.0f;
    }
    shadow/=float(samples);
    return shadow;
//    return closestDepth;
}

void main(){
    vec3 color=texture(diffuseTexture,fs_in.TexCoords).rgb;
    vec3 normal=normalize(fs_in.Normal);
    vec3 lightColor=vec3(0.3f);
    //ambient
    vec3 ambient=0.3f*color;
    //diffuse
    vec3 lightDir=normalize(lightPos-fs_in.FragPos);
    float diff=max(dot(lightDir,normal),0.0f);
    vec3 diffuse=diff*lightColor;
    //specular
    vec3 viewDir=normalize(viewPos-fs_in.FragPos);
    vec3 reflectDir=reflect(-lightDir,normal);
    float spec=0.0f;
    vec3 halfwayDir=normalize(lightDir+viewDir);
    spec=pow(max(dot(normal,halfwayDir),0.0f),64.0f);
    vec3 specular=spec*lightColor;
    //
    float shadow=shadows?ShadowCalculation(fs_in.FragPos):0.0f;
    vec3 lighting=ambient+((1.0f-shadow)*(diffuse+specular))*color;
    
    FragColor=vec4(lighting,1.0f);
//    float closestDepth=ShadowCalculation(fs_in.FragPos);
//    FragColor=vec4(vec3(closestDepth/far_plane),1.0f);
}
