#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D screenTexture;

//uniform sampler2DMS screenTextureMS;
//不还原具有多重采样的纹理图像，直接传入

vec4 Gaussian(){
    const float offset=1.0f/300.0f;
    vec2 offsets[9]=vec2[](
        vec2(-offset,  offset), // 左上
        vec2( 0.0f,    offset), // 正上
        vec2( offset,  offset), // 右上
        vec2(-offset,  0.0f),   // 左
        vec2( 0.0f,    0.0f),   // 中
        vec2( offset,  0.0f),   // 右
        vec2(-offset, -offset), // 左下
        vec2( 0.0f,   -offset), // 正下
        vec2( offset, -offset)  // 右下
    );
    float kernel[9] = float[](
        1.0 / 16, 2.0 / 16, 1.0 / 16,
        2.0 / 16, 4.0 / 16, 2.0 / 16,
        1.0 / 16, 2.0 / 16, 1.0 / 16
    );
    vec3 sampleTex[9];
    for(int i=0;i<9;i++)
        sampleTex[i]=vec3(texture(screenTexture,TexCoords.st+offsets[i]));
    vec3 col=vec3(0.0f);
    for(int j=0;j<9;j++)
        col+=sampleTex[j]*kernel[j];

    return vec4(col,1.0f);
}

void main(){
    FragColor=texture(screenTexture,TexCoords);
    //获取四个样本的颜色值
//    vec4 colorSample0=texelFetch(screenTextureMS,TexCoords,0);
//    vec4 colorSample1=texelFetch(screenTextureMS,TexCoords,1);
//    vec4 colorSample2=texelFetch(screenTextureMS,TexCoords,2);
//    vec4 colorSample3=texelFetch(screenTextureMS,TexCoords,3);
//    FragColor=(colorSample0+colorSample1+colorSample2+colorSample3)/4.0f;
}
