//
//  shader.cpp
//  OpenGLdemo
//
//  Created by SHERLOCK on 05.06.23.
//

#include "shader.hpp"

Shader::Shader(const char* vertexPath, const char* fragmentPath){
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;
    vShaderFile.exceptions(std::ifstream::failbit|std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::failbit|std::ifstream::badbit);
    try{
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);
        std::stringstream vShaderStream,fShaderStream;
        vShaderStream<<vShaderFile.rdbuf();
        fShaderStream<<fShaderFile.rdbuf();
        vShaderFile.close();
        fShaderFile.close();
        vertexCode=vShaderStream.str();
        fragmentCode=fShaderStream.str();
    }
    catch(std::ifstream::failure e){
        std::cout<<"ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ"<<"\n";
    }
    const char* vShaderCode=vertexCode.c_str();
    const char* fShaderCode=fragmentCode.c_str();
    
    unsigned int vertex,fragment;
    Test test;
    vertex=glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex,1,&vShaderCode,NULL);
    glCompileShader(vertex);
    test.ShaderTest(vertex, 1);
    fragment=glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment,1,&fShaderCode,NULL);
    glCompileShader(fragment);
    test.ShaderTest(fragment, 0);
    
    this->ID=glCreateProgram();
    glAttachShader(this->ID,vertex);
    glAttachShader(this->ID,fragment);
    glLinkProgram(this->ID);
    test.ProgramTest(this->ID);
    
    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

void Shader::use() const{
    glUseProgram(this->ID);
}

void Shader::setBool(const std::string &name, bool value) const{
    glUniform1i(glGetUniformLocation(this->ID,name.c_str()),(int)value);
}

void Shader::setInt(const std::string &name, int value) const{
    glUniform1i(glGetUniformLocation(this->ID,name.c_str()),value);
}

void Shader::setFloat(const std::string &name, float value) const{
    glUniform1f(glGetUniformLocation(this->ID,name.c_str()),value);
}

void Shader::setVec4f(const std::string &name, float value1, float value2, float value3, float value4) const{
    glUniform4f(glGetUniformLocation(this->ID,name.c_str()),value1,value2,value3,value4);
}

void Shader::setVec3(const std::string &name, float value1, float value2, float value3) const{
    glUniform3f(glGetUniformLocation(this->ID,name.c_str()),value1,value2,value3);
}

void Shader::setVec3(const std::string &name,const glm::vec3 &vec3) const{
    glUniform3fv(glGetUniformLocation(this->ID,name.c_str()),1,&vec3[0]);
}

void Shader::setMat4(const std::string &name, glm::mat4 mat4) const{
    glUniformMatrix4fv(glGetUniformLocation(this->ID,name.c_str()),1,GL_FALSE,glm::value_ptr(mat4));
}

void Shader::setMat3(const std::string &name, glm::mat3 mat3) const{
    glUniformMatrix3fv(glGetUniformLocation(this->ID,name.c_str()),1,GL_FALSE,glm::value_ptr(mat3));
}
