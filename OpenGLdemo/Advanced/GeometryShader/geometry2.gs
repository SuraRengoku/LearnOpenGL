#version 330 core
layout (points) in;
layout (triangle_strip,max_vertices=5) out;

in VS_OUT{
    vec3 color;
} gs_in[];

out vec3 fColor;

void build_house(vec4 position){
    fColor=gs_in[0].color;//当发射一个顶点的时候，每个顶点将会使用最后在fColor中储存的值，来用于片段着色器的允许，对于房子来说，只需要在发射第一个顶点之前，使用顶点着色器中的颜色填充fColor一次就可以了
    gl_Position=position+vec4(-0.2f,-0.2f,0.0f,0.0f);
    EmitVertex();
    gl_Position=position+vec4( 0.2f,-0.2f,0.0f,0.0f);
    EmitVertex();
    gl_Position=position+vec4(-0.2f, 0.2f,0.0f,0.0f);
    EmitVertex();
    gl_Position=position+vec4( 0.2f, 0.2f,0.0f,0.0f);
    EmitVertex();
    gl_Position=position+vec4( 0.0f, 0.4f,0.0f,0.0f);
    fColor=vec3(1.0f,1.0f,1.0f);
    EmitVertex();
    EndPrimitive();
}

void main(){
    build_house(gl_in[0].gl_Position);
}
