//
//  mesh.cpp
//  OpenGLdemo
//
//  Created by SHERLOCK on 19.07.23.
//

#include "mesh.hpp"

Mesh::Mesh(vector<Vertex> vertices,vector<unsigned> indices,vector<_Texture> _textures){
    this->vertices=vertices;
    this->indices=indices;
    this->_textures=_textures;
    setupMesh();
}

void Mesh::setupMesh(){
    glGenVertexArrays(1,&VAO);
    glGenBuffers(1,&VBO);
    glGenBuffers(1,&VBO);
    
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    glBufferData(GL_ARRAY_BUFFER,vertices.size()*sizeof(Vertex),&vertices[0],GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,indices.size()*sizeof(unsigned int),&indices[0],GL_STATIC_DRAW);
    
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,sizeof(Vertex),(void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,sizeof(Vertex),(void*)offsetof(Vertex, Normal));
    //预处理指令offsetof返回第二个参数在第一个参数中的offset
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2,2,GL_FLOAT,GL_FALSE,sizeof(Vertex),(void*)offsetof(Vertex, TexCoords));
    glEnableVertexAttribArray(2);
}

void Mesh::Draw(const Shader &shader) const{
    unsigned int diffuseNr=1;
    unsigned int specularNr=1;
    for(unsigned int i=0;i<_textures.size();i++){
        glActiveTexture(GL_TEXTURE0+i);
        string number;
        texturetype name=_textures[i].type;
        if(name==texturetype::diffuseMap)
            number=to_string(diffuseNr++);
        if(name==texturetype::specularMap)
            number=to_string(specularNr++);
        
        shader.setInt(("material."+to_string(name)+number).c_str(), i);
        glBindTexture(GL_TEXTURE_2D,_textures[i].ID);
    }
    glActiveTexture(GL_TEXTURE0);
    
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES,indices.size(),GL_UNSIGNED_INT,0);
    glBindVertexArray(0);
}
