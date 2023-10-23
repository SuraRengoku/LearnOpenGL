#version 330 core
out float FragColor;

in vec2 TexCoords;

uniform sampler2D gPositionDepth;
uniform sampler2D gNormal;
uniform sampler2D texNoise;

uniform vec3 samples[64];//64个随机分布采样点
uniform mat4 projection;

int kernelSize=64;
float radius=1.0f;

const vec2 noiseScale=vec2(1200.0f/4.0f,800.0f/4.0f);
//4是噪声纹理大小
void main(){
    vec3 fragPos=texture(gPositionDepth,TexCoords).xyz;//观察空间下的位置
    vec3 normal=texture(gNormal,TexCoords).rgb;
    //映射噪声纹理到整个屏幕,采用了GL_REPEAT平铺参数
    vec3 randomVec=texture(texNoise,TexCoords*noiseScale).xyz;
    //创建TBN
    vec3 tangent=normalize(randomVec-normal*dot(randomVec,normal));
    vec3 bitangent=cross(normal,tangent);
    mat3 TBN=mat3(tangent,bitangent,normal);
    //样本迭代
    float occlusion=0.0f;
    for(int i=0;i<kernelSize;++i){
        vec3 sample=TBN*samples[i];//切线空间->观察空间
        sample=fragPos+sample*radius;
        vec4 offset=vec4(sample,1.0f);
        offset=projection*offset;//观察空间->视锥体空间
        offset.xyz/=offset.w;//解透视
        offset.xyz=offset.xyz*0.5f+0.5f;
        //采样得到view space中单个片段的深度值
        float sampleDepth=-texture(gPositionDepth,offset.xy).w;
        float rangeCheck=smoothstep(0.0f,1.0f,radius/abs(fragPos.z-sampleDepth));
        occlusion+=(sampleDepth>sample.z?1.0f:0.0f)*rangeCheck;
    }
    FragColor=1.0f-(occlusion/kernelSize);
}

