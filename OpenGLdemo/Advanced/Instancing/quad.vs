#version 330 core
layout (location=0) in vec2 aPos;
layout (location=1) in vec3 aColor;

out vec3 fColor;

uniform vec2 offsets[100];

void main(){
    vec2 offset=offsets[gl_InstanceID];
    //gl_InstanceID是内建变量，在实例化渲染调用时，它会从0开始，在每个实例被渲染时递增1
    gl_Position=vec4(aPos+offset,0.0f,1.0f);
    fColor=aColor;
}
