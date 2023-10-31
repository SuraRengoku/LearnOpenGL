#version 330 core
out vec4 FragColor;
in vec2 TexCoords;
in vec3 WorldPos;
in vec3 Normal;

uniform vec3 camPos;
uniform vec3 albedo;
uniform float metallic;//金属度
uniform float roughness;
uniform float ao;

uniform samplerCube irradianceMap;

uniform vec3 lightPositions[4];
uniform vec3 lightColors[4];

const float PI=3.14159265359;

vec3 fresnelSchlick(float cosTheta,vec3 F0,float roughness);
float DistributionGGX(vec3 N,vec3 H,float roughness);//法线分布函数
float GeometrySchlickGGX(float value,float roughness);//几何衰减
float GeometrySmith(vec3 N,vec3 V,vec3 L,float roughness);//史密斯混合

void main(){
    vec3 N=normalize(Normal);//法向量
    vec3 V=normalize(camPos-WorldPos);//view向量
    
    vec3 Lo=vec3(0.0f);//初始辐射率
    
    vec3 F0=vec3(0.04);//基础反射率
    F0=mix(F0,albedo,metallic);
    for(int i=0;i<4;i++){
        vec3 L=normalize(lightPositions[i]-WorldPos);
        vec3 H=normalize(L+V);
        
        float distance=length(L);
        float attenuation=1.0f/(distance*distance);
        vec3 radiance=lightColors[i]*attenuation;
        
        //fresnel
        vec3 F=fresnelSchlick(max(dot(H,V),0.0f),F0,roughness);
        
        //法线分布函数
        float NDF=DistributionGGX(N,H,roughness);
        
        //几何遮蔽衰减
        float G=GeometrySmith(N,V,L,roughness);
        
        //Cook-Torrance BRDF模型
        vec3 nominator=NDF*G*F;
        float denominator=4.0f*max(dot(N,V),0.0f)*max(dot(N,L),0.0f)+0.001;//0.001是避免除零错误
        vec3 specular=nominator/denominator;
        
        //反射能量和折射能量与总辐射能量的守恒
        vec3 kS=F;//反射能量
        vec3 kD=vec3(1.0f)-kS;//折射能量
        kD*=1.0f-metallic;//金属度越高，在折射时被吸收的能量就越多
        
        float NdotL=max(dot(N,L),0.0f);//cosTheta i
        Lo+=(kD*albedo/PI+kS*specular)*radiance*NdotL;
    }
    vec3 kS=fresnelSchlick(max(dot(N,V),0.0f),F0,roughness);
    vec3 kD=1.0f-kS;
    kD*=1.0f-metallic;
    vec3 irradiance=texture(irradianceMap,N).rgb;
    vec3 diffuse=irradiance*albedo;//积分中的光色在此处乘
    vec3 ambient=(kD*diffuse)*ao;//积分中的折射光能量在此处乘
    vec3 color=ambient+Lo;
    
    color=color/(color+vec3(1.0f));//HDR映射
    color=pow(color,vec3(1.0f/2.2f));//伽马矫正
    FragColor=vec4(color,1.0f);
}

vec3 fresnelSchlick(float cosTheta,vec3 F0,float roughness){
    return F0+(max(vec3(1.0f-roughness),F0)-F0)*pow(1.0f-cosTheta,5.0f);
}

float DistributionGGX(vec3 N,vec3 H,float roughness){
    float a=roughness*roughness;
    float a2=a*a;
    float NdotH=max(dot(N,H),0.0f);
    float NdotH2=NdotH*NdotH;
    
    return a2/(PI*pow((NdotH2*(a2-1.0f)+1.0f),2.0f));
}

float GeometrySchlickGGX(float value,float roughness){
    float r=(roughness+1.0f);
    float k=(r*r)/8.0f;
    
    return value/(value*(1-k)+k);
}

float GeometrySmith(vec3 N,vec3 V,vec3 L,float roughness){
    float NdotV=max(dot(N,V),0.0f);
    float NdotL=max(dot(N,L),0.0f);
    
    return GeometrySchlickGGX(NdotV,roughness)*GeometrySchlickGGX(NdotL,roughness);
}

