#verison 330 core
out vec4 FragColor;
in vec2 TexCoords;
in vec3 WorldPos;
in vec3 Normal;

//材质
uniform vec3 albedo;
uniform float metallic;
uniform float roughness;
uniform float ao;

//IBL
uniform samplerCube irradianceMap;
uniform samplerCube prefilterMap;
uniform sampler2D brdfLUT;
//横坐标为NdotV,纵坐标粗糙度

//灯光
uniform vec3 lightPositions[4];
uniform vec3 lightColors[4];

uniform vec3 camPos;

const float PI=3.14159265359;

float DistributionGGX(vec3 N,vec3 H,float roughness);
float GeometrySchlickGGX(float NdotV,float roughness);
float GeometrySmith(vec3 N,vec3 V,vec3 L,float roughness);
vec3 fresnelSchlick(float cosTheta,vec3 F0);
vec3 fresnelSchlickRoughness(float cosTheta,vec3 F0,float roughness);

void main(){
    vec3 N=Normal;
    vec3 V=normalize(camPos-WorldPos);//观察方向
    vec3 R=reflect(-V,N);
    
    vec3 F0=vec3(0.04f);
    F0=mix(F0,albedo,metallic);
    
    vec3 Lo=vec3(0.0f);
    for(int i=0;i<4;i++){
        vec3 L=normalize(lightPosition[i]-WorldPos);//光照方向
        vec3 H=normalize(L+V);
        float distance=length(lightPosition[i]-WorldPos);
        float attenuation=1.0f/(distance*distance);//衰减项
        vec3 radiance=lightColors[i]*attenuation;
        
        //Cook-Torrance BRDF model
        float NDF=DistributionGGX(N,H,roughness);
        float G=GeometrySmith(N,V,L,roughness);
        vec3 F=fresnelSchlick(max(dot(H,V),0.0f),F0);
        
        vec3 numerator=NDF*G*F;
        float denominator=4.0f*max(dot(N,V),0.0f)*max(dot(N,L),0.0f)+0.0001;
        vec3 specular=numerator/denominator;
        
        vec3 kS=F;
        vec3 kD=vec3(1.0f)-kS;//能量守恒
        kD*=1.0f-metallic;//纯金属没有折射
        
        float NdotL=max(dot(N,L),0.0f);
        Lo+=(kD*albedo/PI+specular)*radiance*NdotL;
    }
    
    vec3 F=fresnelSchlickRoughnes(max(dot(N,V),0.0f),F0,roughness);
    vec3 kS=F;
    vec3 kD=vec3(1.0f)-kS;
    kD*=1.0f-metallic;
    //散射
    vec3 irradiance=texture(irradianceMap,N).rgb;
    vec3 diffuse=irradiance*albedo;
    
    const float MAX_REFLECTION_LOD=6.0f;
    vec3 prefilteredColor=textureLod(prefilterMap,R,roughness*MAX_REFLECTION_LOD).rgb;//纹理，坐标，层级
    vec2 brdf=texture(brdfLUT,vec2(max(dot(N,V),0.0f),roughneee)).rg;
    vec3 specular=prefilterColor*(F*brdf.x+brdf.y);
    
    vec3 ambient=(kD*diffuse+specular)*ao;
    vec3 color=ambient+Lo;
    
    color=color/(color+vec3(1.0f));
    color=pow(color,vec3(1.0f/2.2f));
    FragColor=vec4(color,1.0f);
}

float DistributionGGX(vec3 N,vec3 H,float roughness){
    float a=roughness*roughness;
    float a2=a*a;
    float NdotH=max(dot(N,H),0.0f);
    float NdotH2=NdotH*NdotH;
    
    return a2/(PI*pow((NdotH2*(a2-1.0f)+1.0f),2.0f));
}
float GeometrySchlickGGX(float NdotV,float roughness){
    float r=(roughness+1.0f);
    float k=(r*r)/8.0f;
    
    return value/(value*(1-k)+k);
}
float GeometrySmith(vec3 N,vec3 V,vec3 L,float roughness){
    float NdotV=max(dot(N,V),0.0f);
    float NdotL=max(dot(N,L),0.0f);
    
    return GeometrySchlickGGX(NdotV,roughness)*GeometrySchlickGGX(NdotL,roughness);
}
vec3 fresnelSchlick(float cosTheta,vec3 F0){
    return F0+(1.0f-F0)*pow(clamp(1.0f-cosTheta,0.0f,1.0f),5.0f);
    //clamp函数将第一个参数限制在第二个和第三个参数之间
}
vec3 fresnelSchlickRoughness(float cosTheta,vec3 F0,float roughness){
    return F0+(max(vec3(1.0f-roughness),F0)-F0)*pow(clamp(1.0f-cosTheta,0.0f,1.0f),5.0f);
}

