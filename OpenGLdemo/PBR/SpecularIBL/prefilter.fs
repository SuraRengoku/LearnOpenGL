#version 330 core
out vec4 FragColor;
in vec3 localPos;

uniform samplerCube environmentMap;
uniform float roughness;

const float PI=3.1415925359f;

float RadicalInverse_VdC(uint bits);
vec2 Hammersley(uint i,uint N);
vec3 ImportanceSampleGGX(vec2 Xi,vec3 N,float roughness);
float DistributionGGX(vec3 N,vec3 H,float roughness);

float VanDerCorpus(uint n,uint base){
    float invBase=1.0f/float(base);
    float denom=1.0f;
    float result=0.0f;
    for(uint i=0u;i<32u;i++){
        if(n>0u){
            denom=mod(float(n),2.0f);
            result+=denom*invBase;
            invBase=invBase/2.0f;
            n=uint(float(n)/2.0f);
        }
    }
    return result;
}

vec2 HammersleyNoBitOps(uint i,uint N){
    return vec2(float(i)/float(N),VanDerCorpus(i,2u));
}

void main(){
    //假设视角方向（镜面反射方向）等于输出采样方向w_o
    vec3 N=normalize(localPos);//法线方向直接取局部坐标下的位置向量
    //由于cube一直定位在世界坐标的中心，所以不用将其坐标对齐为世界坐标系
    //但是这反射方向等于法线方向就有点诡异......
    vec3 R=N;//反射方向
    vec3 V=R;//视角方向
    
    const uint SAMPLE_COUNT=1024u;
    float totalWeight=0.0f;
    vec3 prefilteredColor=vec3(0.0f);
    for(uint i=0u;i<SAMPLE_COUNT;i++){
        vec2 Xi=Hammersley(i,SAMPLE_COUNT);//随机不重复二维坐标生成
        vec3 H=ImportanceSampleGGX(Xi,N,roughness);//采样向量
        vec3 L=normalize(2.0f*dot(V,H)*H-V);//光照方向
        
        float NdotL=max(dot(N,L),0.0f);
        if(NdotL>0.0f){
            //根据粗糙度和概率密度从立方体贴图的mipmap中取样
            float D=DistributionGGX(N,H,roughness);
            float NdotH=max(dot(N,H),0.0f);
            float HdotV=max(dot(H,V),0.0f);
            float pdf=D*NdotH/(4.0f*HdotV)+0.0001;
            float resolution=512.0f;
            float saTexel=4.0f*PI/(6.0f*resolution*resolution);
            float saSample=1.0f/(float(SAMPLE_COUNT)*pdf+0.0001);
            
            float mipLevel=roughness==0.0f?0.0f:0.5*log2(saSample/saTexel);
            
            prefilteredColor+=textureLod(environmentMap,L,mipLevel).rgb*NdotL;
            totalWeight+=NdotL;
        }
    }
    prefilteredColor=prefilteredColor/totalWeight;
    FragColor=vec4(prefilteredColor,1.0f);
}

/**
 @param bits 32位无符号整数，在进行位运算后可以对空位补0
 @return 在[0,1]范围内的浮点数
 */
float RadicalInverse_VdC(uint bits){
    bits=(bits<<16u)|(bits>>16u);//32位右边部分左移16位，左边部分右移16位
    bits=((bits&0x55555555u)<<1u)|((bits&0xAAAAAAAAu)>>1u);//乘单位掩码移动一位
    bits=((bits&0x33333333u)<<2u)|((bits&0xCCCCCCCCu)>>2u);//乘双位掩码移动两位
    bits=((bits&0x0F0F0F0Fu)<<4u)|((bits&0xF0F0F0F0u)>>4u);//乘四位掩码移动四位
    bits=((bits&0x00FF00FFu)<<8u)|((bits&0xFF00FF00u)>>8u);//乘八位掩码移动八位
    return float(bits)*2.3283064365386963e-10;
    //2.3283064365386963e-10是1/4294967296的浮点表示，换算为1/(2^32)，用于将转化的数map到[0,1)范围内
}//精妙绝伦的位运算 f**king well done!!!

vec2 Hammersley(uint i,uint N){
    return vec2(float(i)/float(N),RadicalInverse_VdC(i));
}

vec3 ImportanceSampleGGX(vec2 Xi,vec3 N,float roughness){
    float a=roughness*roughness;
    
    float phi=2.0f*PI*Xi.x;
    float cosTheta=sqrt((1.0f-Xi.y)/(1.0f+(a*a-1.0f)*Xi.y));
    float sinTheta=sqrt(1.0f-cosTheta*cosTheta);
    //球面坐标至笛卡尔坐标系的映射
    vec3 H=vec3(cos(phi)*sinTheta,sin(phi)*sinTheta,cosTheta);
    //切线空间转换到世界空间
    vec3 up=abs(N.z)<0.999?vec3(0.0f,0.0f,1.0f):vec3(1.0f,0.0f,0.0f);
    vec3 tangent=normalize(cross(up,N));
    vec3 bitangent=cross(N,tangent);
    
    vec3 sampleVec=tangent*H.x+bitangent*H.y+N*H.z;
    return normalize(sampleVec);
}

float DistributionGGX(vec3 N,vec3 H,float roughness){
    float a=roughness*roughness;
    float a2=a*a;
    float NdotH=max(dot(N,H),0.0f);
    float NdotH2=NdotH*NdotH;
    
    float nom=a2;
    float denom=(NdotH2*(a2-1.0f)+1.0f);
    denom=PI*denom*denom;
    
    return nom/denom;
}
