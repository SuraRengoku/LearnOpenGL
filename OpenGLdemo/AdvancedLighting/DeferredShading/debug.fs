#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D debugtexture;

void main(){
    vec3 color=texture(debugtexture,TexCoords).rgb;
    FragColor=vec4(color,1.0f);
}
