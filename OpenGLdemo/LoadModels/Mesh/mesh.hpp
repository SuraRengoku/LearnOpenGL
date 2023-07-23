//
//  mesh.hpp
//  OpenGLdemo
//
//  Created by SHERLOCK on 19.07.23.
//

#ifndef mesh_hpp
#define mesh_hpp

#include "shader.hpp"
using namespace std;

#define MAX_BONE_INFLUENCE 4

struct Vertex{
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
    glm::vec3 Tangent;
    glm::vec3 Bitangent;
    int m_BoneIDs[MAX_BONE_INFLUENCE];
    float m_Weights[MAX_BONE_INFLUENCE];
};
//C++结构体有一个很棒的特性，它们的内存布局是连续的(Sequential)。也就是说，如果我们将结构体作为一个数据数组使用，那么它将会以顺序排列结构体的变量，这将会直接转换为我们在数组缓冲中所需要的float（实际上是字节）数组。
enum texturetype{
    diffuseMap,
    specularMap,
    normalMap,
    heightMap
};

typedef std::map<std::string,texturetype> TEXTURE_TYPE_MAP;
//TEXTURE_TYPE_MAP ttMap;

struct _Texture{
    unsigned int ID;
    std::string type;
    std::string path;
};

class Mesh{
public:
    vector<Vertex> vertices;
    vector<unsigned> indices;
    vector<_Texture> _textures;
    Mesh(vector<Vertex> vertices,vector<unsigned int> indices,vector<_Texture> _textures);
    void Draw(const Shader &shader) const;
private:
    unsigned int VBO,VAO,EBO;
    void setupMesh();
};


#endif /* mesh_hpp */
