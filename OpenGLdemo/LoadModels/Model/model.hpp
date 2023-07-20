//
//  model.hpp
//  OpenGLdemo
//
//  Created by SHERLOCK on 20.07.23.
//

#ifndef model_hpp
#define model_hpp

#include "shader.hpp"
#include "mesh.hpp"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

class Model{
public:
    Model(char* path){
        loadModel(path);
    }
    void Draw(Shader &shader);
private:
    std::vector<Mesh> meshes;
    std::string directory;
    void loadModel(std::string path);
    void processNode(aiNode *node,const aiScene *scene);
    Mesh processMesh(aiNode *mesh,const aiScene *scene);
    std::vector<_Texture> loadMaterialTexture(aiMaterial *material,aiTextureType type,std::string typeName);
};

#endif /* model_hpp */
