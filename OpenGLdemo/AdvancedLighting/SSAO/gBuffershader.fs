#version 330 core
layout (location=0) out vec4 gPositionDepth;
layout (location=1) out vec3 gNormal;
layout (location=2) out vec4 gAlbedoSpec;

in vec2 TexCoords;
in vec3 FragPos;
in vec3 Normal;

uniform sampler2D texture_diffuse1;
uniform sampler2D texture_specular1;
//由于没有给立方体添加高光贴图，导致这里的贴图被设置为float0
uniform bool suit;

const float NEAR=0.1;
const float FAR=50.0f;

float LinearizeDepth(float depth){
    float z=depth*2.0f-1.0f;//from [0,1] to [-1,1], which is NDC
    return (2.0f*NEAR*FAR)/(FAR+NEAR-z*(FAR-NEAR));
    //根据公式Ze=(2.0f*NEAR*FAR)/(Zn*(FAR-NEAR)-(FAR+NEAR)),但是NDC和View Space的z轴方向是相反的，所以需要取负
}

void main(){
    gPositionDepth.xyz=FragPos;
    gPositionDepth.a=LinearizeDepth(gl_FragCoord.z);//提取出来的线性深度是在view Space中的
    //gl_FragCoord是内建变量，会将经过MVP三个矩阵变换的顶点再进行一次解除投影操作
    gNormal=normalize(Normal);
//    gAlbedoSpec.rgb=vec3(0.95f);//漫反射颜色
    if(suit){
        gAlbedoSpec.rgb=texture(texture_diffuse1,TexCoords).rgb;
        gAlbedoSpec.a=texture(texture_specular1,TexCoords).r;
    }else{
//        gAlbedoSpec.rgb=vec3(0.95f);
        gAlbedoSpec.rgb=texture(texture_diffuse1,TexCoords).rgb;
    }
}
