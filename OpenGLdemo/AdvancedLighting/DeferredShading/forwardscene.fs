#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D rawscene;
uniform sampler2D bloomscene;
uniform sampler2D deferscene;

uniform bool bloom;
uniform float exposure;

void main(){
    const float gamma=2.2f;
    vec3 deferColor=texture(deferscene,TexCoords).rgb;
    vec3 hdrColor=texture(rawscene,TexCoords).rgb;
    vec3 bloomColor=texture(bloomscene,TexCoords).rgb;
    if(bloom)
        hdrColor+=bloomColor;
    vec3 result=vec3(1.0f)-exp(-hdrColor*exposure);
    result=pow(result,vec3(1.0f/gamma));
    result+=deferColor;
    FragColor=vec4(result,1.0f);
}

