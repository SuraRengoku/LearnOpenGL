//
//  shader.hpp
//  OpenGLdemo
//
//  Created by SHERLOCK on 05.06.23.
//

#ifndef shader_hpp
#define shader_hpp

#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include "general.h"

class Shader{
public:
    unsigned int ID;//程序ID
    //构造器读取并构建着色器
    Shader(const char *vertexPath,const char *fragmentPath);
    Shader(const char *vertexPaht,const char *geometryPath,const char *fragmentPath);
    //使用/激活程序
    void use() const;
    //uniform工具函数
    void setBool(const std::string &name,bool value) const;
    void setInt(const std::string &name,int value) const;
    void setFloat(const std::string &name,float value) const;
    void setVec4f(const std::string &name,float,float,float,float) const;
    void setMat4(const std::string &name,glm::mat4 mat4) const;
    void setMat3(const std::string &name,glm::mat3 mat3) const;
    void setVec3(const std::string &name,float,float,float) const;
    void setVec3(const std::string &name,const glm::vec3 &vec3) const;
};

#endif /* shader_hpp */
