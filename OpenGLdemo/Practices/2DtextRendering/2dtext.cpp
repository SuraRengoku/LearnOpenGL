//
//  2dtext.cpp
//  OpenGLdemo
//
//  Created by SHERLOCK on 14.11.23.
//

#include "2dtext.hpp"
#define Default_Width 1200;
#define Default_Height 800;

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

glm::vec3 TextColor(0.5f,0.2f,0.7f);
static float TextSize=0.3f;
bool text_changed=false;

vector<string> font_paths={
    "resource/fonts/HarmonyOS_Sans_SC_Medium.ttf",
    "resource/fonts/NotoSans-ExtraBold.ttf",
    "resource/fonts/NotoSansArabic-Medium.ttf",
    "resource/fonts/NotoSansCanadianAboriginal-Medium.ttf",
    "resource/fonts/NotoSansCuneiform-Regular.ttf",
    "resource/fonts/NotoSansSymbols2-Regular.ttf",
    "resource/fonts/NotoSerif-Regular.ttf",
    "resource/fonts/NotoSansHK-Regular.ttf",
    "resource/fonts/NotoSansHK-VariableFont_wght.ttf"
};

static std::map<FT_ULong,Character> Characters;

static GLuint VAO,VBO;

void mouse_callback(GLFWwindow* window, double xposIn, double yposIn);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
//void RenderText(Shader &s,std::string text,GLfloat x,GLfloat y,GLfloat scale,glm::vec3 color);

std::u32string u32text_string(U"mashiro-真白-ましろ ❀ ⛅ ✯ ❅\nᕕ(◠ڼ◠)ᕗ Ciallo～(∠・ω< )⌒★ (ᗜ˰ᗜ)\n天动万象 I will have order 𒆚 𒆚 𒆙");
char text_buffer[4096]{"mashiro-真白-ましろ ❀ ⛅ ✯ ❅\nᕕ(◠ڼ◠)ᕗ Ciallo～(∠・ω< )⌒★ (ᗜ˰ᗜ)\n天动万象 I will have order 𒆚 𒆚 𒆙"};
string text_string("mashiro-真白-ましろ ❀ ⛅ ✯ ❅\nᕕ(◠ڼ◠)ᕗ Ciallo～(∠・ω< )⌒★ (ᗜ˰ᗜ)\n天动万象 I will have order 𒆚 𒆚 𒆙");

void bitTrans(char text_buffer[],std::u32string &u32string_text){
    std::string text_string=text_buffer;
    std::wstring_convert<std::codecvt_utf8<char32_t>,char32_t> converter;
    u32string_text=converter.from_bytes(text_string);
}

template<typename T>
int RenderText(Shader &shader,T text,GLfloat x,GLfloat y,GLfloat scale,glm::vec3 color){
    FT_Library charft;
    if(FT_Init_FreeType(&charft)){
        cout<<"ERROR::FREETYPE: Could not init FreeType Libaray\n";
        return -1;
    }
    
    vector<FT_Face> charfaces;
    glPixelStorei(GL_UNPACK_ALIGNMENT,1);
    for(const string &font_path:font_paths){
        FT_Face charface;
        if(FT_New_Face(charft, font_path.c_str(), 0, &charface)){
            cout<<"ERROR:FREETYPE:Failed to load font\n";
            return -1;
        }
        FT_Set_Pixel_Sizes(charface, 0, 60);
        charfaces.push_back(charface);
    }
    
    shader.use();
    shader.setVec3("textColor", color);
    glActiveTexture(GL_TEXTURE0);
    
    glBindVertexArray(VAO);
//    if constexpr(std::is_same_v<T, std::wstring>)
//        std::wstring::const_iterator wch;
    int loop=0;
    for(auto wch=text.begin();wch!=text.end();wch++){
        for(auto charface:charfaces){
            FT_UInt glyphIndex=FT_Get_Char_Index(charface, *wch);
            if(glyphIndex==0){
                loop+=1;
                continue;
            }
            else{
                if(FT_Load_Char(charface, *wch, FT_LOAD_RENDER)){
                    cout<<"ERROR::getCharFromFreeType:Failed to load Glyph\n";
                    return -1;
                }else{
                    GLuint chartexture;
                    glGenTextures(1,&chartexture);
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
                    break;
                }
            }
        }
    }
    for(auto charface:charfaces)
        FT_Done_Face(charface);
    FT_Done_FreeType(charft);
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D,0);
    return 0;
}

int _2dtext(){
    GLFWwindow* window=glfw_Init(SCR_WIDTH, SCR_HEIGHT, mouse_callback, scroll_callback);
    
    const char *glsl_version="#version 330 core";
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io=ImGui::GetIO();
    (void)io;
    io.ConfigFlags|=ImGuiConfigFlags_NavEnableGamepad;
    io.ConfigFlags|=ImGuiConfigFlags_NavEnableKeyboard;
    ImWchar ranges[]={0x0020,0xffff,0};//Unicode编码范围
    ImWchar ranges1[]={0x06B0,0x06ff,0};
    ImWchar ranges2[] = {0x1550, 0x15DD, 0};
    ImWchar ranges3[] = {static_cast<ImWchar>(0x12199), static_cast<ImWchar>(0x1219A), 0};
    ImWchar ranges4[] = {0x25E0, 0x28ff, 0};
    ImWchar ranges5[] = {0x02E0, 0x02FF, 0};
    ImWchar ranges6[] = {static_cast<ImWchar>(0x0000), static_cast<ImWchar>(0x1df1e), 0};
    ImWchar ranges7[] = {0x20, static_cast<ImWchar>(0x3106c),0};
    ImWchar ranges8[] = {0x20, static_cast<ImWchar>(0x3106c),0};
    
    ImFontConfig config;
    config.MergeMode=true;
    config.PixelSnapH=true;
    io.Fonts->AddFontFromFileTTF("resource/fonts/HarmonyOS_Sans_SC_Medium.ttf", 18.0f,NULL,ranges);
    io.Fonts->AddFontFromFileTTF("resource/fonts/NotoSansArabic-Medium.ttf", 18.0f,&config,ranges1);
    io.Fonts->AddFontFromFileTTF("resource/fonts/NotoSansArabic-Medium.ttf", 18.0f,&config,ranges2);
    io.Fonts->AddFontFromFileTTF("resource/fonts/NotoSansCanadianAboriginal-Medium.ttf", 22.0f,&config,ranges3);
    io.Fonts->AddFontFromFileTTF("resource/fonts/NotoSansCuneiform-Regular.ttf", 22.0f,&config,ranges4);
    io.Fonts->AddFontFromFileTTF("resource/fonts/NotoSansSymbols2-Regular.ttf", 22.0f,&config,ranges5);
    io.Fonts->AddFontFromFileTTF("resource/fonts/NotoSerif-Regular.ttf", 22.0f,&config,ranges6);
    io.Fonts->AddFontFromFileTTF("resource/fonts/NotoSansHK-Regular.ttf", 22.0f,&config,ranges7);
    io.Fonts->AddFontFromFileTTF("resource/fonts/NotoSansHK-VariableFont_wght.ttf", 22.0f,&config,ranges8);
    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);
    
    
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
    
//    glPixelStorei(GL_UNPACK_ALIGNMENT,1);
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
        
    std::wstring s1=L"你好，世界!";
    std::wstring s2=L"(C) LearnOpenGL.com";
    std::wstring s3=L"äöüß !";
    
    bitTrans(text_buffer, u32text_string);
        
    while(!glfwWindowShouldClose(window)){
        processInput(window, mouse_callback, scroll_callback);
        
        glClearColor(0.2f,0.3f,0.3f,1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        ImGui::Begin("Light Settings");
//        imgui_window_focus=ImGui::IsWindowFocused();
        ImGui::PushItemWidth(150);
        ImGui::ColorEdit3("Text Color", (float*)&TextColor);
        ImGui::Text("(%.3f ms)(%.1f fps)",1000.0f/io.Framerate,io.Framerate);
        ImGui::SliderFloat("Text Size", (float*)&TextSize, 0.005f, 1.0f);
        
        ImGui::InputTextMultiline("Input Text", text_buffer, sizeof(text_buffer),ImVec2(-1,ImGui::GetTextLineHeight()*4),ImGuiInputTextFlags_EnterReturnsTrue);//即使修改text_buffer，该函数仍然返回false
                
        bitTrans(text_buffer, u32text_string);//更新文本内容
        
        ImGui::End();
//        RenderText<std::wstring>(*shader, s1, 25.0f,25.0f,1.0f, glm::vec3(0.5f,0.8f,0.2f));//scale直接放大会出现锯齿边缘
//        RenderText<std::string>(*shader, "(C) LearnOpenGL.com", 500.0f, 570.0f, 0.5f, glm::vec3(0.3f,0.7f,0.9f));
        RenderText<std::u32string>(*shader, u32text_string, 200.0f, 250.0f, TextSize, TextColor);
        
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        
        glfwPollEvents();
        glfwSwapBuffers(window);
    }
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
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

