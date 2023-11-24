//
//  render.cpp
//  OpenGLdemo
//
//  Created by SHERLOCK on 22.10.23.
//

#include "render.h"

CubeRender::CubeRender(){
    GLuint cubeVAO,cubeVBO;
    glGenVertexArrays(1,&cubeVAO);
    glGenBuffers(1,&cubeVBO);
    glBindVertexArray(cubeVAO);
    glBindBuffer(GL_ARRAY_BUFFER,cubeVBO);
    glBufferData(GL_ARRAY_BUFFER,sizeof(this->vertices),&(this->vertices),GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,8*sizeof(GLfloat),(GLvoid*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,8*sizeof(GLfloat),(GLvoid*)(3*sizeof(GLfloat)));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2,2,GL_FLOAT,GL_FALSE,8*sizeof(GLfloat),(GLvoid*)(6*sizeof(GLfloat)));
    glBindVertexArray(0);
    this->VAO=cubeVAO;
}

void CubeRender::render(){
    glBindVertexArray(this->VAO);
    glDrawArrays(GL_TRIANGLES,0,36);
    glBindVertexArray(0);
}

QuadRender::QuadRender(){
    GLuint quadVAO,quadVBO;
    glGenVertexArrays(1,&quadVAO);
    glGenBuffers(1,&quadVBO);
    glBindVertexArray(quadVAO);
    glBindBuffer(GL_ARRAY_BUFFER,quadVBO);
    glBufferData(GL_ARRAY_BUFFER,sizeof(this->quadVertices),&(this->quadVertices),GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,5*sizeof(GLfloat),(GLvoid*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1,2,GL_FLOAT,GL_FALSE,5*sizeof(GLfloat),(GLvoid*)(3*sizeof(GLfloat)));
    this->VAO=quadVAO;
}

void QuadRender::render(){
    glBindVertexArray(this->VAO);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glBindVertexArray(0);
}

SphereRender::SphereRender(int slice){
    GLuint sphereVAO,sphereVBO,sphereEBO;
    glGenVertexArrays(1,&sphereVAO);
    glGenBuffers(1,&sphereVBO);
    glGenBuffers(1,&sphereEBO);
    
    std::vector<glm::vec3> positions;
    std::vector<glm::vec2> uv;//方位角 u 极角 v
    std::vector<glm::vec3> normals;
    std::vector<unsigned int> indices;

    const unsigned int X_SEGMENTS = 64;
    const unsigned int Y_SEGMENTS = 64;
    const float PI = 3.14159265359f;
    for (unsigned int x = 0; x <= X_SEGMENTS; ++x){
        for (unsigned int y = 0; y <= Y_SEGMENTS; ++y){
            float xSegment = (float)x / (float)X_SEGMENTS;
            float ySegment = (float)y / (float)Y_SEGMENTS;
            float xPos = std::cos(xSegment * 2.0f * PI) * std::sin(ySegment * PI);
            float yPos = std::cos(ySegment * PI);
            float zPos = std::sin(xSegment * 2.0f * PI) * std::sin(ySegment * PI);

            positions.push_back(glm::vec3(xPos, yPos, zPos));
            uv.push_back(glm::vec2(xSegment, ySegment));
            normals.push_back(glm::vec3(xPos, yPos, zPos));
        }
    }

    bool oddRow = false;
    for (unsigned int y = 0; y < Y_SEGMENTS; ++y){
        if (!oddRow){ // even rows: y == 0, y == 2; and so on
            for (unsigned int x = 0; x <= X_SEGMENTS; ++x){
                indices.push_back(y       * (X_SEGMENTS + 1) + x);
                indices.push_back((y + 1) * (X_SEGMENTS + 1) + x);
            }
        }else{
            for (int x = X_SEGMENTS; x >= 0; --x){
                indices.push_back((y + 1) * (X_SEGMENTS + 1) + x);
                indices.push_back(y       * (X_SEGMENTS + 1) + x);
            }
        }
        oddRow = !oddRow;
    }
    this->indexCount = static_cast<unsigned int>(indices.size());

    std::vector<float> data;
    for (unsigned int i = 0; i < positions.size(); ++i)
    {
        data.push_back(positions[i].x);
        data.push_back(positions[i].y);
        data.push_back(positions[i].z);
        if (normals.size() > 0){
            data.push_back(normals[i].x);
            data.push_back(normals[i].y);
            data.push_back(normals[i].z);
        }
        if (uv.size() > 0){
            data.push_back(uv[i].x);
            data.push_back(uv[i].y);
        }
    }
    glBindVertexArray(sphereVAO);
    glBindBuffer(GL_ARRAY_BUFFER,sphereVBO);
    glBufferData(GL_ARRAY_BUFFER,data.size()*sizeof(float),&data[0],GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,sphereEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,indices.size()*sizeof(float),&indices[0],GL_STATIC_DRAW);
    unsigned int stride=(3+2+3)*sizeof(float);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,stride,(void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,stride,(void*)(3*sizeof(float)));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2,2,GL_FLOAT,GL_FALSE,stride,(void*)(6*sizeof(float)));
    this->VAO=sphereVAO;
}

void SphereRender::render(){
    glBindVertexArray(this->VAO);
    glDrawElements(GL_TRIANGLE_STRIP,this->indexCount,GL_UNSIGNED_INT,0);
    glBindVertexArray(0);
}

SpriteRender::SpriteRender(const Shader &shader){
    this->shader=shader;
    GLuint spriteVAO,spriteVBO;
    glGenVertexArrays(1,&spriteVAO);
    glGenBuffers(1,&spriteVBO);
    glBindVertexArray(spriteVAO);
    glBindBuffer(GL_ARRAY_BUFFER,spriteVBO);
    glBufferData(GL_ARRAY_BUFFER,sizeof(this->spriteVertices),this->spriteVertices,GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0,4,GL_FLOAT,GL_FALSE,4*sizeof(GLfloat),(GLvoid*)0);
    glBindBuffer(GL_ARRAY_BUFFER,0);
    glBindVertexArray(0);
    this->VAO=spriteVAO;
}

void SpriteRender::render(){

}

void SpriteRender::DrawSprite(const Texture2D &texture, glm::vec2 position,glm::vec2 size,GLfloat rotate,glm::vec3 color){
    this->shader.use();
    glm::mat4 model=glm::mat4(1.0f);
    model=glm::translate(model,glm::vec3(position,0.0f));
    model=glm::translate(model, glm::vec3(0.5f*size.x,0.5f*size.y,0.0f));//旋转原点移到中心
    model=glm::rotate(model,glm::radians(rotate),glm::vec3(0.0f,0.0f,1.0f));
    model=glm::translate(model, glm::vec3(-0.5f*size.x,-0.5f*size.y,0.0f));
    model=glm::scale(model,glm::vec3(size,1.0f));
    
    this->shader.setMat4("model", model);
    this->shader.setVec3("spriteColor", color);
        
    glBindVertexArray(this->VAO);
    
    glActiveTexture(GL_TEXTURE0);
    texture.Bind();

    glDrawArrays(GL_TRIANGLES,0,6);
    glBindVertexArray(0);
}

//void SpriteRender::setShader(const Shader &shader){
//    this->shader=shader;
//}
