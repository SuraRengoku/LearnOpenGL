#version 330 core
out vec2 FragColor;
in vec2 TexCoords;

uniform sampler2D environmentMap;
uniform float roughness;

const float PI=3.1415925359f;

float RadicalInverse_VdC(uint bits);
vec2 Hammersley(uint i,uint N);
vec3 ImportanceSampleGGX(vec2 Xi,vec3 N, roughness);

vec2 IntegrateBRDF(float NdotV,float roughness);
float GeometrySchlickGGX(float NdotV,float roughness);
float GeometrySchlickSmith(vec3 N,vec3 V,vec3 L,float roughness);

void main(){
    vec2 integratedBRDF=IntegrateBRDF(TexCoords.x,TexCoords.y);
    FragColor=integratedBRDF;
}

float RadicalInverse_VdC(uint bits){
    bits=(bits<<16u)|(bits>>16u);
    bits=((bits&0x55555555u)<<1u)|((bits&0xAAAAAAAAu)>>1u);
    bits=((bits&0x33333333u)<<2u)|((bits&0xCCCCCCCCu)>>2u);
    bits=((bits&0x0F0F0F0Fu)<<4u)|((bits&0xF0F0F0F0u)>>4u);
    bits=((bits&0x00FF00FFu)<<8u)|((bits&0xFF00FF00u)>>8u);
    return float(bits)*2.3283064365386963e-10;
}
vec2 Hammersley(uint i,uint N){
    return vec2(float(i)/float(N),RadicalInverse_VdC(i));
}
vec3 ImportanceSampleGGX(vec2 Xi,vec3 N, roughness){
    float a=roughness*roughness;
    float phi=2.0f*PI*Xi.x;
    float cosTheta=sqrt((1.0f-Xi.y)/(1.0f+(a*a-1.0f)*Xi.y));
    float sinTheta=sqrt(1.0f-cosTheta*cosTheta);
    vec3 H=vec3(cos(phi)*sinTheta,sin(phi)*sinTheta,cosTheta);
    vec3 up=abs(N.z)<0.999?vec3(0.0f,0.0f,1.0f):vec3(1.0f,0.0f,0.0f);
    vec3 tangent=normalize(cross(up,N));
    vec3 bitangen=cross(N,tangent);
    
    vec3 sampleVec=tangent*H.x+bitangent*H.y+N*H.z;
    return normalize(sampleVec);
}

void IntegrateBRDF(float NdotV,float roughness){
    vec3 V=vec3(sqrt(1.0f-NdotV*NdotV),0.0f,NdotV);
    
    float A=0.0f;
    float B=0.0f;
    
    vec3 N=vec3(0.0f,0.0f,1.0f);
    
    const uint SAMPLE_COUNT=1024u;
    for(uint i=0u;i<SAMPLE_COUNT;i++){
        vec2 Xi=Hammersley(i,SAMPLE_COUNT);
        vec3 H=ImportanceSampleGGX(Xi,N,roughness);
        vec3 L=normalize(2.0f*dot(V,H)*H-V);
        
        float NdotL=max(L.z,0.0f);
        float NdotH=max(H.z,0.0f);
        float VdotH=max(dot(V,H),0.0f);
        
        if(NdotL>0.0f){
            float G=GeometrySmith(N,V,L,roughness);
            float G_Vis=(G*VdotH)/(NdotH*NdotV);
            float Fc=pow(1.0f-VdotH,5.0f);
            
            A+=(1.0f-Fc)*G_Vis;
            B+=Fc*G_Vis;
        }
    }
    A/=float(SAMPLE_COUNT);
    B/=float(SAMPLE_COUNT);
    return vec2(A,B);
}
float GeometrySchlickGGX(float NdotV,float roughness){
    float a=roughness;
    float k=(a*a)/2.0f
    
    float nom=NdotV;
    float denom=NdotV*(1.0f-k)+k;
    return nom/denom;
}
float GeometrySchlickSmith(vec3 N,vec3 V,vec3 L,float roughness){
    float NdotV=max(dot(N,V),0.0f);
    float NdotL=max(dot(N,L),0.0f);
    
    float ggx1=GeometrySchlickGGX(NdotV,roughness);
    float ggx2=GeometrySchlickGGX(NdotL,roughness);
    return ggx1*ggx2;
}
