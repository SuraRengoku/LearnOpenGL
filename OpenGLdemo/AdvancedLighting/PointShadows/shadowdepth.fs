#version 330 core
in vec4 FragPos;

uniform vec3 lightPos;
uniform float far_plane;

void main(){
    float lightDistance=length(FragPos.xyz-lightPos);
    gl_FragDepth=lightDistance/far_plane;//计算深度相对值[0,1]
}
