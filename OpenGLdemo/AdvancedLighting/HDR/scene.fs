#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D hdrBuffer;
uniform bool hdr;
uniform bool Reinhard;
uniform float exposure;

void main(){
    const float gamma=2.2f;
    vec3 hdrColor=texture(hdrBuffer,TexCoords).rgb;
    
    if(hdr){
        vec3 mapped;
        if(Reinhard){
            //Reinhard Tone Mapping
            mapped=hdrColor/(hdrColor+vec3(1.0f));
        }else{
            //Exposure Tone Mapping
            mapped=vec3(1.0f)-exp(-hdrColor*exposure);
        }
        mapped=pow(mapped,vec3(1.0f/gamma));
        FragColor=vec4(mapped,1.0f);
    }else{
        vec3 result=pow(hdrColor,vec3(1.0f/gamma));
        FragColor=vec4(result,1.0f);
    }
}
