//
//  ResourManager.hpp
//  OpenGLdemo
//
//  Created by SHERLOCK on 22.11.23.
//

#ifndef ResourManager_hpp
#define ResourManager_hpp

#include <map>
#include <string>
#include "shader.hpp"
#include "Texture.hpp"

class ResourceManager{
public:
    static std::map<std::string,Shader> Shaders;
    static std::map<std::string,Texture2D> Textures;
    static Shader LoadShader(const GLchar *vShaderFile,const GLchar *fShaderFile, const GLchar *gShaderFile, std::string name);
    static Shader GetShader(std::string name);
    static Texture2D LoadTexture(const GLchar *file,GLboolean alpha,std::string name);
    static Texture2D GetTexture(std::string name);
    static void Clear();//de-allocate all loaded resources
private:
    ResourceManager(){}
    static Shader loadShaderFromFile(const GLchar *vShaderFile,const GLchar *fShaderFile, const GLchar *gShaderFile=nullptr);
    static Texture2D loadTextureFromFile(const GLchar *file,GLboolean alpha);
};

#endif /* ResourManager_hpp */
