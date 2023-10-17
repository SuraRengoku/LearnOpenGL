#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D debugtexture;

void main(){
    float highlight=texture(debugtexture,TexCoords).a;
    FragColor=vec4(highlight,highlight,highlight,1.0f);
}
