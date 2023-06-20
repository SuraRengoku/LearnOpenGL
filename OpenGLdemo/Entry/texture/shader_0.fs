#version 330 core
in vec3 ourColor;
in vec2 TexCoord;

out vec4 FragColor;
uniform sampler2D ourTexture1;
uniform sampler2D ourTexture2;

void main(){
    FragColor=mix(texture(ourTexture1,TexCoord),texture(ourTexture2,TexCoord),0.2);
    //texture是内建函数用来采样纹理颜色
    //mix内建函数输出纹理的结合，第三个参数表示第二个纹理的线性插值比例
}
