#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D screenTexture;

uniform int effect;

//反相
vec4 Reverse(){
    return vec4(vec3(1.0f-texture(screenTexture,TexCoords)),1.0f);
}

//灰度
vec4 GrayScale(){
    vec4 tempcolor=texture(screenTexture,TexCoords);
    float average=0.2126*tempcolor.r+0.7152*tempcolor.g+0.0722*tempcolor.b;
    return vec4(average,average,average,1.0f);
}

//核效果
vec4 Kernel(){
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
    float kernel[9]=float[](
        -1,-1,-1,
        -1, 9,-1,
        -1,-1,-1
    );
    vec3 sampleTex[9];
    for(int i=0;i<9;i++)
        sampleTex[i]=vec3(texture(screenTexture,TexCoords.st+offsets[i]));
    vec3 col=vec3(0.0f);
    for(int j=0;j<9;j++)
        col+=sampleTex[j]*kernel[j];
    
    return vec4(col,1.0f);
}

//模糊
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

//边缘检测
vec4 Edge(){
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
    float kernel[9]=float[](
        -1,-1,-1,
        -1, 8,-1,
        -1,-1,-1
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
    switch (effect) {
        case 1:
            FragColor=Reverse();
            break;
        case 2:
            FragColor=GrayScale();
            break;
        case 3:
            FragColor=Kernel();
            break;
        case 4:
            FragColor=Gaussian();
            break;
        case 5:
            FragColor=Edge();
            break;
        default:
            vec3 col=texture(screenTexture,TexCoords).rgb;
            FragColor=vec4(col,1.0f);
            break;
    }
}
