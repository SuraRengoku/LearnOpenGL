//
//  2dtext.cpp
//  OpenGLdemo
//
//  Created by SHERLOCK on 14.11.23.
//

#include "2dtext.hpp"
#define Default_Width 800;
#define Default_Height 600;

static unsigned const int SCR_WIDTH=Default_Width;
static unsigned const int SCR_HEIGHT=Default_Height;

Camera camera(glm::vec3(0.0f,0.0f,5.0f));
bool firstMouse=true;
float lastX=SCR_WIDTH/2.0f;
float lastY=SCR_HEIGHT/2.0f;

static float deltaTime=0.0f;
static float lastTime=0.0f;

struct Character{
    GLuint TextureID;
    glm::ivec2 Size;
    glm::ivec2 Bearing;
    FT_Long Advance;
};

static std::map<FT_ULong,Character> Characters;

static GLuint VAO,VBO;

void mouse_callback(GLFWwindow* window, double xposIn, double yposIn);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
//void RenderText(Shader &s,std::string text,GLfloat x,GLfloat y,GLfloat scale,glm::vec3 color);

template<typename T>
int RenderText(Shader &shader,T text,GLfloat x,GLfloat y,GLfloat scale,glm::vec3 color){
    FT_Library charft;
    if(FT_Init_FreeType(&charft)){
        cout<<"ERROR::FREETYPE: Could not init FreeType Libaray\n";
        return -1;
    }
    
    FT_Face charface;
    if(FT_New_Face(charft, "/Users/sherlock/Documents/Code/OpenGLdemo/OpenGLdemo/resource/fonts/NotoSansHK-Regular.ttf", 0, &charface)){
        cout<<"ERROR::FREETYPE: Failed to load font\n";
        return -1;
    }
    
    FT_Set_Pixel_Sizes(charface, 0, 48);
    
    GLuint chartexture;
    glGenTextures(1,&chartexture);
    
    shader.use();
    shader.setVec3("textColor", color);
    glActiveTexture(GL_TEXTURE0);
    
    glBindVertexArray(VAO);
//    if constexpr(std::is_same_v<T, std::wstring>)
//        std::wstring::const_iterator wch;
    for(auto wch=text.begin();wch!=text.end();wch++){
        if(FT_Load_Char(charface, *wch, FT_LOAD_RENDER)){
            cout<<"ERROR::getCharFromFreeType:Failed to load Glyph\n";
            return -1;
        }
        glBindTexture(GL_TEXTURE_2D,chartexture);
        glTexImage2D(GL_TEXTURE_2D,0,GL_RED,charface->glyph->bitmap.width,charface->glyph->bitmap.rows,0,GL_RED,GL_UNSIGNED_BYTE,charface->glyph->bitmap.buffer);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
        Character character={
            chartexture,
            glm::ivec2(charface->glyph->bitmap.width,charface->glyph->bitmap.rows),
            glm::ivec2(charface->glyph->bitmap_left,charface->glyph->bitmap_top),
            charface->glyph->advance.x
        };
        Characters.insert(std::pair<FT_ULong,Character>(*wch,character));
        Character ch=Characters[*wch];
        GLfloat xpos=x+ch.Bearing.x*scale;
        GLfloat ypos=y-(ch.Size.y-ch.Bearing.y)*scale;
        GLfloat w=ch.Size.x*scale;
        GLfloat h=ch.Size.y*scale;
        
        GLfloat vertices[6][4]={
            {xpos,ypos+h,0.0f,0.0f},
            {xpos,ypos,0.0f,1.0f},
            {xpos+w,ypos,1.0f,1.0f},
            {xpos,ypos+h,0.0f,0.0f},
            {xpos+w,ypos,1.0f,1.0f},
            {xpos+w,ypos+h,1.0f,0.0f}
        };
        glBindTexture(GL_TEXTURE_2D,ch.TextureID);
        glBindBuffer(GL_ARRAY_BUFFER,VBO);
        glBufferSubData(GL_ARRAY_BUFFER,0,sizeof(vertices),vertices);
        
        glDrawArrays(GL_TRIANGLES,0,6);
        x+=(ch.Advance>>6)*scale;
    }
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D,0);
    return 0;
}

int _2dtext(){
    GLFWwindow* window=glfw_Init(SCR_WIDTH, SCR_HEIGHT, mouse_callback, scroll_callback);
//    FT_Library ft;
//    if(FT_Init_FreeType(&ft))
//        cout<<"ERROR::FREETYPE: Could not init FreeType Libaray\n";
//    FT_Face face;//将字体加载为一个FreeType称之为面Face的东西
//    if(FT_New_Face(ft, "/Users/sherlock/Documents/Code/OpenGLdemo/OpenGLdemo/resource/fonts/NotoSerif-Regular.ttf", 0, &face))
//        cout<<"ERROR::FREETYPE: Failed to load font\n";
    
    /**
        width   face->glyph->bitmap.width   位图像素宽度
        height  face->glyph->bitmap.rows  位图像素高度
        bearingX    face->glyph->bitmap_left    位图相对于原点的水平位置
        bearingY    face->glyph->bitmap_top    位图相对于原点的垂直距离
        advance     face->glyph->advance.x     水平预留值，原点到下一个字形原点的水平距离(1/64像素)
     */
        
    //定义字体大小 width height
//    FT_Set_Pixel_Sizes(face, 0, 48);
    //将宽度值设为0表示要从字体面通过给定的高度中动态计算出字形的宽度
    
    glPixelStorei(GL_UNPACK_ALIGNMENT,1);
//    for(GLubyte c=0;c<128;c++){
//        if(FT_Load_Char(face, c, FT_LOAD_RENDER)){//激活字形
//            cout<<"ERRO::FREETYPE: Failed to load Glyph\n";
//            continue;
//        }
//        GLuint texture;
//        glGenTextures(1,&texture);
//        glBindTexture(GL_TEXTURE_2D,texture);
//        glTexImage2D(GL_TEXTURE_2D,0,GL_RED,face->glyph->bitmap.width,face->glyph->bitmap.rows,0,GL_RED,GL_UNSIGNED_BYTE,face->glyph->bitmap.buffer);
//        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
//        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);
//        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
//        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
//        Character character={
//            texture,
//            glm::ivec2(face->glyph->bitmap.width,face->glyph->bitmap.rows),
//            glm::ivec2(face->glyph->bitmap_left,face->glyph->bitmap_top),
//            face->glyph->advance.x
//        };
//        Characters.insert(std::pair<GLchar,Character>(c,character));
//    }//遍历ASCII中全部128字符并获取对应字符字形
//    FT_Done_Face(face);
//    FT_Done_FreeType(ft);//清理资源
    
    glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    
    Shader* shader=new Shader("/Users/sherlock/Documents/Code/OpenGLdemo/OpenGLdemo/Practices/2DtextRendering/2dtext.vs","/Users/sherlock/Documents/Code/OpenGLdemo/OpenGLdemo/Practices/2DtextRendering/2dtext.fs");

    glm::mat4 projection=glm::ortho(0.0f,800.0f,0.0f,600.0f);
    shader->use();
    shader->setMat4("projection", projection);
    
    glGenVertexArrays(1,&VAO);
    glGenBuffers(1,&VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    glBufferData(GL_ARRAY_BUFFER,sizeof(GLfloat)*6*4,NULL,GL_DYNAMIC_DRAW);//每个2D四边形需要六个顶点，每个顶点由4float向量组成
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0,4,GL_FLOAT,GL_FALSE,4*sizeof(GLfloat),0);
    glBindBuffer(GL_ARRAY_BUFFER,0);
    glBindVertexArray(0);
        
    std::wstring s1=L"this is a text: 你好，世界!";
    std::wstring s2=L"(C) LearnOpenGL.com";
    std::wstring s3=L"this ia a text: äöüß !";
    
    while(!glfwWindowShouldClose(window)){
        processInput(window, mouse_callback, scroll_callback);
        
        glClearColor(0.2f,0.3f,0.3f,1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        RenderText<std::wstring>(*shader, s1, 25.0f,25.0f,1.0f, glm::vec3(0.5f,0.8f,0.2f));
        RenderText<std::string>(*shader, "(C) LearnOpenGL.com", 500.0f, 570.0f, 0.5f, glm::vec3(0.3f,0.7f,0.9f));
        
        glfwPollEvents();
        glfwSwapBuffers(window);
    }
    glfwTerminate();
    return 0;
}

void mouse_callback(GLFWwindow* window, double xposIn, double yposIn){
    float xpos=static_cast<float>(xposIn);
    float ypos=static_cast<float>(yposIn);
    if(firstMouse){
        lastX=xpos;
        lastY=ypos;
        firstMouse=false;
    }
    float xoffset=xpos-lastX;
    float yoffset=lastY-ypos;
    lastY=ypos;
    lastX=xpos;
    camera.ProcessMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset){
    camera.ProcessMouseScroll(yoffset);
}

//void RenderText(Shader &s,std::string text,GLfloat x,GLfloat y,GLfloat scale,glm::vec3 color){
//    s.use();
//    glUniform3f(glGetUniformLocation(s.ID,"textColor"),color.x,color.y,color.z);
//    glActiveTexture(GL_TEXTURE0);
//    glBindVertexArray(VAO);
//
//    std::string::const_iterator c;
//    //遍历字符
//    for(c=text.begin();c!=text.end();c++){
//        Character ch=Characters[*c];
//        GLfloat xpos=x+ch.Bearing.x*scale;
//        GLfloat ypos=y-(ch.Size.y-ch.Bearing.y)*scale;
//        GLfloat w=ch.Size.x*scale;
//        GLfloat h=ch.Size.y*scale;
//
//        GLfloat vertices[6][4]={
//            {xpos,ypos+h,0.0f,0.0f},
//            {xpos,ypos,0.0f,1.0f},
//            {xpos+w,ypos,1.0f,1.0f},
//            {xpos,ypos+h,0.0f,0.0f},
//            {xpos+w,ypos,1.0f,1.0f},
//            {xpos+w,ypos+h,1.0f,0.0f}
//        };
//        glBindTexture(GL_TEXTURE_2D,ch.TextureID);
//        glBindBuffer(GL_ARRAY_BUFFER,VBO);
//        glBufferSubData(GL_ARRAY_BUFFER,0,sizeof(vertices),vertices);
//        glBindBuffer(GL_ARRAY_BUFFER,0);
//
//        glDrawArrays(GL_TRIANGLES,0,6);
//        x+=(ch.Advance>>6)*scale;//偏移2^6=64来获取单位为像素的值
//    }
//    glBindVertexArray(0);
//    glBindTexture(GL_TEXTURE_2D,0);
//}
