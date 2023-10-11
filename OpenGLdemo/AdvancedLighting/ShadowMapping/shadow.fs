#version 330 core
out vec4 FragColor;

in VS_OUT{
    vec3 FragPos;
    vec3 Normal;
    vec2 TexCoords;
    vec4 FragPosLightSpace;
} fs_in;

uniform sampler2D diffuseTexture;
uniform sampler2D shadowMap;

uniform vec3 lightPos;
uniform vec3 viewPos;

float ShadowCalculation(vec4 fragPosLightSpace){
    vec3 projCoords=fragPosLightSpace.xyz/fragPosLightSpace.w;
    projCoords=projCoords*0.5f+0.5f;//from [-1,1] to [0,1]
    float closestDepth=texture(shadowMap,projCoords.xy).r;
    //超出深度贴图的区域，纹理函数总会返回一个1.0f的深度值，阴影值自然为0.0
    float currentDepth=projCoords.z;
    vec3 normal=normalize(fs_in.Normal);
    vec3 lightDir=normalize(lightPos-fs_in.FragPos);
    float bias=max(0.05f*(1.0f-dot(normal,lightDir)),0.005);
    //使用偏移量解决阴影失真,但可能造成阴影相对于实际物体位置的偏移,也称之为悬浮
    float shadow=0.0f;
    vec2 texelSize=1.0f/textureSize(shadowMap,0);
    for(int x=-1;x<=1;++x){
        for(int y=-1;y<=1;y++){
            float pcfDepth=texture(shadowMap,projCoords.xy+vec2(x,y)*texelSize).r;
            shadow+=currentDepth-bias>pcfDepth?1.0f:0.0f;
        }
    }//使用percentage-closer filtering，从周围采样再平均
    shadow/=9.0f;
//    float shadow=currentDepth-bias>closestDepth?1.0f:0.0f;
    if(projCoords.z>1.0f)//超出光的正交视锥远平面的坐标，z值总大于1.0f，不矫正则一直处于阴影之中
        shadow=0.0f;
    return shadow;
}

void main(){
    vec3 color=texture(diffuseTexture,fs_in.TexCoords).rgb;
    vec3 normal=normalize(fs_in.Normal);
    vec3 lightColor=vec3(1.0f);
    
    vec3 ambient=0.15*color;
    
    vec3 lightDir=normalize(lightPos-fs_in.FragPos);
    float diff=max(dot(lightDir,normal),0.0f);
    vec3 diffuse=diff*lightColor;
    
    vec3 viewDir=normalize(viewPos-fs_in.FragPos);
    vec3 reflectDir=reflect(-lightDir,normal);
    float spec=0.0;
    vec3 halfwayDir=normalize(lightDir+viewDir);
    spec=pow(max(dot(normal,halfwayDir),0.0f),64.0f);
    vec3 specular=spec*lightColor;
    
    float shadow=ShadowCalculation(fs_in.FragPosLightSpace);
    vec3 lighting=(ambient+(1.0f-shadow)*(diffuse+specular))*color;
    
    FragColor=vec4(lighting,1.0f);
}
