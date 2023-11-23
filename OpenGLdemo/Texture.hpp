//
//  Texture.hpp
//  OpenGLdemo
//
//  Created by SHERLOCK on 22.11.23.
//

#ifndef Texture_hpp
#define Texture_hpp

#include "general.h"

class Texture2D{
public:
    GLuint ID;
    GLuint Width,Height;
    GLuint Internal_Format;
    GLuint Image_Format;
    GLuint Wrap_S;
    GLuint Wrap_T;
    GLuint Filter_Min;
    GLuint Filter_Mag;
    Texture2D();
    void Generate(GLuint width,GLuint height,unsigned char* data);
    void Bind() const;
};

#endif /* Texture_hpp */
