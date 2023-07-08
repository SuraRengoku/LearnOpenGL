#version 330 core
out vec4 FragColor;

in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoord;

struct Material{
    sampler2D diffuse;
    sampler2D specular;//使用灰度图可以根据具体亮度实现高光识别
    float shininess;
};

//注意sampler2D是所谓的不透明类型(Opaque Type)，也就是说我们不能将它实例化，只能通过uniform来定义它。如果我们使用除uniform以外的方法（比如函数的参数）实例化这个结构体，GLSL会抛出一些奇怪的错误。这同样也适用于任何封装了不透明类型的结构体。
//环境光颜色在几乎所有情况下都等于漫反射颜色

struct Light {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform Material material;
uniform Light light;
uniform vec3 viewPos;

void main(){
    vec3 ambient=light.ambient*texture(material.diffuse,TexCoord).rgb;
    vec3 norm=normalize(Normal);
    vec3 lightDir=normalize(light.position-FragPos);
    float diff=max(dot(norm,lightDir),0.0f);
    vec3 diffuse=light.diffuse*diff*texture(material.diffuse,TexCoord).rgb;
    
    vec3 viewDir=normalize(viewPos-FragPos);
    vec3 reflectDir=reflect(-lightDir,norm);
    float spec=pow(max(dot(viewDir,reflectDir),0.0f),material.shininess);
    vec3 specular=light.specular*spec*texture(material.specular,TexCoord).rgb;
    
    FragColor=vec4(ambient+diffuse+specular,1.0f);
}
