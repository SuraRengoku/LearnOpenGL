//
//  mesh.cpp
//  OpenGLdemo
//
//  Created by SHERLOCK on 19.07.23.
//
#include "mesh.hpp"

Mesh::Mesh(vector<Vertex> vertices,vector<unsigned int> indices,vector<_Texture> _textures){
    this->vertices=vertices;
    this->indices=indices;
    this->_textures=_textures;
    setupMesh();
}

void Mesh::setupMesh(){
    glGenVertexArrays(1,&VAO);
    glGenBuffers(1,&VBO);
    glGenBuffers(1,&EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    glBufferData(GL_ARRAY_BUFFER,vertices.size()*sizeof(Vertex),&vertices[0],GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,indices.size()*sizeof(unsigned int),&indices[0],GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,sizeof(Vertex),(void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,sizeof(Vertex),(void*)offsetof(Vertex, Normal));
    //预处理指令offsetof返回第二个参数在第一个参数中的offset
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2,2,GL_FLOAT,GL_FALSE,sizeof(Vertex),(void*)offsetof(Vertex, TexCoords));
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3,3,GL_FLOAT,GL_FALSE,sizeof(Vertex),(void*)offsetof(Vertex, Tangent));
    glEnableVertexAttribArray(4);
    glVertexAttribPointer(4,3,GL_FLOAT,GL_FALSE,sizeof(Vertex),(void*)offsetof(Vertex, Bitangent));
    glEnableVertexAttribArray(5);
    glVertexAttribIPointer(5,4,GL_INT,sizeof(Vertex),(void*)offsetof(Vertex, m_BoneIDs));
    glEnableVertexAttribArray(6);
    glVertexAttribPointer(6,4,GL_FLOAT,GL_FALSE,sizeof(Vertex),(void*)offsetof(Vertex, m_Weights));
    glBindVertexArray(0);
}

void Mesh::Draw(const Shader &shader) const{
    unsigned int diffuseNr=1;
    unsigned int specularNr=1;
    unsigned int normalNr=1;
    unsigned int heightNr=1;
    unsigned int ambientNr=1;
    for(unsigned int i=0;i<_textures.size();i++){
        glActiveTexture(GL_TEXTURE0+i);
        string number;
        string name=_textures[i].type;
        if(name=="texture_diffuse")
            number=std::to_string(diffuseNr++);
        else if(name=="texture_specular")
            number=std::to_string(specularNr++);
        else if(name=="texture_normal")
            number=std::to_string(normalNr++);
        else if(name=="texture_height")
            number=std::to_string(heightNr++);
        else if(name=="texture_reflect")
            number=std::to_string(ambientNr++);
        shader.setInt((name+number).c_str(), i);
        glBindTexture(GL_TEXTURE_2D,_textures[i].id);
    }
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES,static_cast<unsigned int >(indices.size()),GL_UNSIGNED_INT,0);
    glBindVertexArray(0);
    glActiveTexture(GL_TEXTURE0);
}

void Mesh::DrawWithTexture(const Shader &shader, unsigned int &texture) const{

}
