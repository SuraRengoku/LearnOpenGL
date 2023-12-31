////
////  model.hpp
////  OpenGLdemo
////
////  Created by SHERLOCK on 20.07.23.
////
//
#ifndef model_hpp
#define model_hpp

#include "mesh.hpp"

//unsigned int TextureFromFile(const char *path, const string &directory, bool gamma = false);

class Model
{
public:
    // model data
    vector<_Texture> textures_loaded;    // stores all the textures loaded so far, optimization to make sure textures aren't loaded more than once.
    vector<Mesh>    meshes;
    string directory;
    string modeltype;
    bool gammaCorrection;
    // constructor, expects a filepath to a 3D model.
    Model(string const &path, bool gamma=false):gammaCorrection(gamma){
        loadModel(path);
    }
    // draws the model, and thus all its meshes
    void Draw(Shader &shader);

private:
    // loads a model with supported ASSIMP extensions from file and stores the resulting meshes in the meshes vector.
    void loadModel(string const &path);
    // processes a node in a recursive fashion. Processes each individual mesh located at the node and repeats this process on its children nodes (if any).
    void processNode(aiNode *node, const aiScene *scene);

    Mesh processMesh(aiMesh *mesh, const aiScene *scene);

    // checks all material textures of a given type and loads the textures if they're not loaded yet.
    // the required info is returned as a Texture struct.
    vector<_Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, string typeName, const aiScene* scene);
};

unsigned int TextureFromFile(const char *path, const string &directory, bool gamma = false);

#endif
