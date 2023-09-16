//
//  mesh.hpp
//  OpenGLdemo
//
//  Created by SHERLOCK on 19.07.23.
//

#ifndef mesh_hpp
#define mesh_hpp

#include "shader.hpp"

#define MAX_BONE_INFLUENCE 4

struct Vertex {
    // position
    glm::vec3 Position;
    // normal
    glm::vec3 Normal;
    // texCoords
    glm::vec2 TexCoords;
    // tangent
    glm::vec3 Tangent;
    // bitangent
    glm::vec3 Bitangent;
    //bone indexes which will influence this vertex
    int m_BoneIDs[MAX_BONE_INFLUENCE];
    //weights from each bone
    float m_Weights[MAX_BONE_INFLUENCE];
};

enum textureType{
    diffuse,
    specular,
    normal,
    height
};

typedef std::map<textureType,std::string> TEXTURE_TYEP_MAP;

struct _Texture {
    unsigned int id;
    string type;
    string path;
};

class Mesh {
public:
    // mesh Data
    vector<Vertex>       vertices;
    vector<unsigned int> indices;
    vector<_Texture>      _textures;
    unsigned int VAO;
    // constructor
    Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<_Texture> _textures);
    // render the mesh
    void Draw(const Shader &shader) const;
    void DrawWithTexture(const Shader &shader,unsigned int& texture) const;
private:
    // render data
    unsigned int VBO, EBO;
    // initializes all the buffer objects/arrays
    void setupMesh();
};
#endif
