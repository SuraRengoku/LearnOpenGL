#version 330 core
layout (triangles) in;//输入1个三角形
layout (triangle_strip,max_vertices=18) out;//输出6个三角形

uniform mat4 shadowMatrices[6];

out vec4 FragPos;

void main(){
    for(int face=0;face<6;++face){
        gl_Layer=face;//内建变量
        for(int i=0;i<3;++i){
            FragPos=gl_in[i].gl_Position;
            gl_Position=shadowMatrices[face]*FragPos;//将每个世界空间顶点转变到相关的光空间
            EmitVertex();
        }
        EndPrimitive();
    }
}
