//
//  ResourManager.cpp
//  OpenGLdemo
//
//  Created by SHERLOCK on 22.11.23.
//

#include "ResourManager.hpp"

std::map<std::string,Texture2D> ResourceManager::Textures;
std::map<std::string,Shader> ResourceManager::Shaders;

Shader ResourceManager::LoadShader(const GLchar *vShaderFile, const GLchar *fShaderFile, const GLchar *gShaderFile, std::string name){
//    Shaders[name]=loadShaderFromFile(vShaderFile, fShaderFile, gShaderFile);
    Shaders.insert(std::make_pair(name, loadShaderFromFile(vShaderFile, fShaderFile,gShaderFile)));
    return Shaders[name];
}

Shader ResourceManager::GetShader(std::string name){
    return Shaders[name];
}

Texture2D ResourceManager::LoadTexture(const GLchar *file, GLboolean alpha, std::string name){
    Textures[name]=loadTextureFromFile(file, alpha);
    return Textures[name];
}

Texture2D ResourceManager::GetTexture(std::string name){
    return Textures[name];
}

void ResourceManager::Clear(){
    for(auto shader:Shaders)
        glDeleteProgram(shader.second.ID);
    for(auto texture:Textures)
        glDeleteTextures(1,&texture.second.ID);
}

Shader ResourceManager::loadShaderFromFile(const GLchar *vShaderFile, const GLchar *fShaderFile,const GLchar *gShaderFile){
    std::string vertexCode;
    std::string fragmentCode;
    std::string geometryCode;
    try{
        std::ifstream vertexShaderFile(vShaderFile);
        std::ifstream fragmentShaderFile(fShaderFile);
        std::stringstream vShaderStream,fShaderStream;
        vShaderStream<<vertexShaderFile.rdbuf();
        fShaderStream<<fragmentShaderFile.rdbuf();
        vertexShaderFile.close();
        fragmentShaderFile.close();
        vertexCode=vShaderStream.str();
        fragmentCode=fShaderStream.str();
        if(gShaderFile!=nullptr){
            std::ifstream geometryShaderFile(gShaderFile);
            std::stringstream gShaderStream;
            gShaderStream<<geometryShaderFile.rdbuf();
            geometryShaderFile.close();
            geometryCode=gShaderStream.str();
        }
    }catch(std::exception e){
        cout<<"ERROR:SHADER:Failed to read shader files\n";
    }
    const GLchar *vShaderCode=vertexCode.c_str();
    const GLchar *fShaderCode=fragmentCode.c_str();
    const GLchar *gShaderCode=geometryCode.c_str();
    if(gShaderFile!=nullptr){
        Shader shader(vShaderFile,fShaderFile,gShaderFile);
        return shader;
    }
    Shader shader(vShaderFile,fShaderFile);
    return shader;
}

Texture2D ResourceManager::loadTextureFromFile(const GLchar *file, GLboolean alpha){
    Texture2D texture;
    if(alpha){
        texture.Internal_Format=GL_RGBA;
        texture.Image_Format=GL_RGBA;
    }
    int width,height,nrChannels;
    unsigned char* image=stbi_load(file, &width, &height, &nrChannels, 0);
    texture.Generate(width, height, image);
    stbi_image_free(image);
    return texture;
}
