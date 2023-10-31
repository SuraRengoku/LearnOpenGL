#version 330 core
out vec4 FragColor;

in vec3 localPos;

uniform samplerCube environmentMap;

const float PI=3.14159265359f;

vec3 irradianceIntegral(vec3 normal){
    vec3 irradiance=vec3(0.0f);
    
    vec3 up=vec3(0.0f,1.0f,0.0f);
    vec3 right=normalize(cross(up,normal));
    up=normalize(cross(normal,right));
    
    float sampleDelta=0.025f;
    float nrSamples=0.0f;
    for(float phi=0.0f;phi<2.0f*PI;phi+=sampleDelta){
        for(float theta=0.0f;theta<0.5f*PI;theta+=sampleDelta){
            vec3 tangentSample=vec3(sin(theta)*cos(phi),sin(theta)*sin(phi),cos(theta));//(x,z,y)
            vec3 sampleVec=tangentSample.x*right+tangentSample.y*up+tangentSample.z*normal;//
            irradiance+=texture(environmentMap,sampleVec).rgb*cos(theta)*sin(theta);
            nrSamples++;
        }
    }
    return PI*irradiance*(1.0f/float(nrSamples));
}

void main(){
    //半球像素指向即是采样方向
    vec3 normal=normalize(localPos);
    
    vec3 irradiance=irradianceIntegral(normal);
    FragColor=vec4(irradiance,1.0f);
}
