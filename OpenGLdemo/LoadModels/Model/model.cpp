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

void Model::loadModel(std::string path){
    Assimp::Importer importer;
    const aiScene *scene=importer.ReadFile(path, aiProcess_Triangulate|aiProcess_FlipUVs);
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
    this->directory=path.substr(0,path.find_last_of('/'));
    processNode(scene->mRootNode, scene);
}

