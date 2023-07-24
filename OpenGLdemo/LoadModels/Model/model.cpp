//
//  model.cpp
//  OpenGLdemo
//
//  Created by SHERLOCK on 20.07.23.
//

#include "model.hpp"

void Model::Draw(Shader &shader){
    for(unsigned int i=0;i<this->meshes.size();i++)
        this->meshes[i].Draw(shader);
}

void Model::loadModel(std::string const &path){
    Assimp::Importer importer;
    const aiScene *scene=importer.ReadFile(path, aiProcess_Triangulate|aiProcess_FlipUVs|aiProcess_GenSmoothNormals|aiProcess_CalcTangentSpace);
    //加载scene结构，这是模型文件的根目录，通过它可以检索其他数据元
    //第二个参数是额外计算项
    //aiProcess_Triangulate如果模型不是（全部）由三角形组成，它需要将模型所有的图元形状变换为三角形
    //aiProcess_FlipUVs反转y轴，OpenGL中大部分情况下y轴都是反向的
    //aiProcess_GenNormals如果模型不包含法向量的话，就为每个顶点创建法线
    //aiProcess_SplitLargeMeshes将比较大的网格分割成更小的子网格，如果你的渲染有最大顶点数限制，只能渲染较小的网格，那么它会非常有用
    //aiProcess_OptimizeMeshes和上个选项相反，它会将多个小网格拼接为一个大的网格，减少绘制调用从而进行优化
    if(!scene||scene->mFlags&AI_SCENE_FLAGS_INCOMPLETE||!scene->mRootNode){
        cout<<"ERROR:ASSIMP::"<<importer.GetErrorString()<<"\n";
        return;
    }
    this->modeltype=path.substr(path.find_last_of('.')+1);
    this->directory=path.substr(0,path.find_last_of('/'));
    processNode(scene->mRootNode, scene);
}

void Model::processNode(aiNode *node, const aiScene *scene){
    for(unsigned int i=0;i<node->mNumMeshes;i++){
        aiMesh *mesh=scene->mMeshes[node->mMeshes[i]];
        this->meshes.push_back(processMesh(mesh, scene));
    }
    for(unsigned int i=0;i<node->mNumChildren;i++){
        processNode(node->mChildren[i], scene);
    }
}

Mesh Model::processMesh(aiMesh *mesh, const aiScene *scene){
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<_Texture> _textures;
    for(unsigned int i=0;i<mesh->mNumVertices;i++){
        Vertex vertex;
        //处理顶点位置
        glm::vec3 vector;
        vector.x=mesh->mVertices[i].x;
        vector.y=mesh->mVertices[i].y;
        vector.z=mesh->mVertices[i].z;
        vertex.Position=vector;
        //处理法线
        if(mesh->HasNormals()){
            vector.x=mesh->mNormals[i].x;
            vector.y=mesh->mNormals[i].y;
            vector.z=mesh->mNormals[i].z;
            vertex.Normal=vector;
        }
        //处理纹理坐标
        if(mesh->mTextureCoords[0]){
            //检查是否真的有纹理坐标
            glm::vec2 vector_;
            //assimp允许一个顶点上有8个不同的纹理坐标，目前只用第一个
            vector_.x=mesh->mTextureCoords[0][i].x;
            vector_.y=mesh->mTextureCoords[0][i].y;
            vertex.TexCoords=vector_;
            //tangent
            vector.x=mesh->mTangents[i].x;
            vector.y=mesh->mTangents[i].y;
            vector.z=mesh->mTangents[i].z;
            vertex.Tangent=vector;
            //bitangent
            vector.x=mesh->mBitangents[i].x;
            vector.y=mesh->mBitangents[i].y;
            vector.z=mesh->mBitangents[i].z;
            vertex.Bitangent=vector;
        }
        else
            vertex.TexCoords=glm::vec2(0.0f,0.0f);
        vertices.push_back(vertex);
    }
    //处理索引
    for(unsigned int i=0;i<mesh->mNumFaces;i++){
        aiFace face=mesh->mFaces[i];
        for(unsigned int j=0;j<face.mNumIndices;j++)
            indices.push_back(face.mIndices[j]);
    }
    //处理材质
    if(mesh->mMaterialIndex>=0){
        aiMaterial *material=scene->mMaterials[mesh->mMaterialIndex];
        vector<_Texture> diffuseMaps=loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse",scene);
        _textures.insert(_textures.end(), diffuseMaps.begin(),diffuseMaps.end());
        vector<_Texture> specularMaps=loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular",scene);
        _textures.insert(_textures.end(), specularMaps.begin(),specularMaps.end());
        vector<_Texture> normalMaps=loadMaterialTextures(material, aiTextureType_NORMALS, "texture_normal",scene);
        _textures.insert(_textures.end(), normalMaps.begin(),normalMaps.end());
        vector<_Texture> heightMaps=loadMaterialTextures(material, aiTextureType_HEIGHT, "texture_height",scene);
        _textures.insert(_textures.end(), heightMaps.begin(),heightMaps.end());
    }
    return Mesh(vertices,indices,_textures);
}

std::vector<_Texture> Model::loadMaterialTextures(aiMaterial *material, aiTextureType type, std::string typeName, const aiScene* scene){
    std::vector<_Texture> _textures;
    for(unsigned int i=0;i<material->GetTextureCount(type);i++){
        aiString str;
        material->GetTexture(type, i, &str);
        bool skip=false;
        for(unsigned int j=0;j<textures_loaded.size();j++){
            if(std::strcmp(textures_loaded[j].path.data(), str.C_Str())==0){
                _textures.push_back(textures_loaded[j]);
                skip=true;
                break;
            }
        }
        if(!skip){
            if(this->modeltype=="obj"){
                _Texture _texture;
                _texture.id=TextureFromFile(str.C_Str(),this->directory);
                _texture.type=typeName;
                _texture.path=str.C_Str();
                _textures.push_back(_texture);
                textures_loaded.push_back(_texture);
            }
            else if(this->modeltype=="fbx"){
                _Texture _texture;
                auto filepath=StringUtil::Format("%s/%s",directory.c_str(),str.C_Str());
                auto aitexture=scene->GetEmbeddedTexture(str.C_Str());
                if(aitexture!=nullptr)
                    _texture.id=loadTextureFromAssimp(aitexture, GL_CLAMP, GL_LINEAR, GL_LINEAR);
                else
                    _texture.id=loadTexture(filepath.c_str());
                _texture.type=typeName;
                _texture.path=str.C_Str();
                _textures.push_back(_texture);
                textures_loaded.push_back(_texture);
            }
        }
    }
    return _textures;
}

unsigned int TextureFromFile(const char *path, const string &directory,bool gamma){
    string filename=string(path);
    filename=directory+'/'+filename;
    return loadTexture(filename.c_str());
}

