//
//  model.hpp
//  OpenGLdemo
//
//  Created by SHERLOCK on 20.07.23.
//

#ifndef model_hpp
#define model_hpp

#include "mesh.hpp"
//extern TEXTURE_TYPE_MAP ttMap;
//ttMap.insert(pair<texturetype,std::string>("texture_diffuse",diffuseMap));

class Model{
public:
    Model(std::string const &path, bool gamma=false):gammaCorrection(gamma){
        loadModel(path);
    }
    void Draw(Shader &shader);
private:
    std::vector<_Texture> textures_load;
    std::vector<Mesh> meshes;
    std::string directory;
    bool gammaCorrection;
    void loadModel(std::string const &path);
    void processNode(aiNode *node,const aiScene *scene);
    Mesh processMesh(aiMesh *mesh,const aiScene *scene);
    std::vector<_Texture> loadMaterialTexture(aiMaterial *material,aiTextureType type,std::string typeName);
};

//unsigned int TextureFromFile(const char *path, const string &directory);
unsigned int TextureFromFile(const char *path, const string &directory, bool gamma = false);
#endif /* model_hpp */
