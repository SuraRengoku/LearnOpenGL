#version 330 core
in vec2 TexCoords;
out vec4 FragColor;
uniform sampler2D texture1;

uniform float near;
uniform float far;

float LinearizeDepth(float depth){
    float z=depth*2.0f-1.0f;
    return (2.0f*near*far)/(near+far-z*(far-near));
}

void main(){
    float depth=LinearizeDepth(gl_FragCoord.z)/far;
    FragColor=vec4(vec3(depth),1.0f);
}
