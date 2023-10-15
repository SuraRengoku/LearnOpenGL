//
//  bloom.cpp
//  OpenGLdemo
//
//  Created by SHERLOCK on 14.10.23.
//

#include "bloom.hpp"
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

void mouse_callback(GLFWwindow* window, double xposIn, double yposIn);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void lighting_control(GLFWwindow* window);

static bool hdr_=true;
static bool hdrKeyPressed=false;
static bool Reinhard=true;
static bool ReinhardPressed=false;
static bool bloom_=true;
static bool bloomPressed=false;
static float exposure=1.0f;

float vertices[] = {
    // back face
    -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f, // bottom-left
     1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f, // top-right
     1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 1.0f, 0.0f, // bottom-right
     1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f, // top-right
    -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f, // bottom-left
    -1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 0.0f, 1.0f, // top-left
    // front face
    -1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 0.0f, // bottom-left
     1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, 0.0f, // bottom-right
     1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, 1.0f, // top-right
     1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, 1.0f, // top-right
    -1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 1.0f, // top-left
    -1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 0.0f, // bottom-left
    // left face
    -1.0f,  1.0f,  1.0f, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-right
    -1.0f,  1.0f, -1.0f, -1.0f,  0.0f,  0.0f, 1.0f, 1.0f, // top-left
    -1.0f, -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-left
    -1.0f, -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-left
    -1.0f, -1.0f,  1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 0.0f, // bottom-right
    -1.0f,  1.0f,  1.0f, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-right
    // right face
     1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-left
     1.0f, -1.0f, -1.0f,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-right
     1.0f,  1.0f, -1.0f,  1.0f,  0.0f,  0.0f, 1.0f, 1.0f, // top-right
     1.0f, -1.0f, -1.0f,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-right
     1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-left
     1.0f, -1.0f,  1.0f,  1.0f,  0.0f,  0.0f, 0.0f, 0.0f, // bottom-left
    // bottom face
    -1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f, // top-right
     1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f, 1.0f, 1.0f, // top-left
     1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f, // bottom-left
     1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f, // bottom-left
    -1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f, 0.0f, 0.0f, // bottom-right
    -1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f, // top-right
    // top face
    -1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f, // top-left
     1.0f,  1.0f , 1.0f,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f, // bottom-right
     1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f, 1.0f, 1.0f, // top-right
     1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f, // bottom-right
    -1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f, // top-left
    -1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f, 0.0f, 0.0f  // bottom-left
};
auto loadCubeBuffer()->GLuint{
    GLuint cubeVAO,cubeVBO;
    glGenVertexArrays(1,&cubeVAO);
    glGenBuffers(1,&cubeVBO);
    glBindVertexArray(cubeVAO);
    glBindBuffer(GL_ARRAY_BUFFER,cubeVBO);
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),&vertices,GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,8*sizeof(GLfloat),(GLvoid*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,8*sizeof(GLfloat),(GLvoid*)(3*sizeof(GLfloat)));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2,2,GL_FLOAT,GL_FALSE,8*sizeof(GLfloat),(GLvoid*)(6*sizeof(GLfloat)));
    glBindVertexArray(0);
    return cubeVAO;
}
void renderCube(GLuint cubeVAO){
    glBindVertexArray(cubeVAO);
    glDrawArrays(GL_TRIANGLES,0,36);
    glBindVertexArray(0);
}

float quadVertices[] = {
    // Positions        // Texture Coords
    -1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
    -1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
    1.0f, 1.0f, 0.0f, 1.0f, 1.0f,
    1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
};
auto loadQuadBuffer()->GLuint{
    GLuint quadVAO,quadVBO;
    glGenVertexArrays(1,&quadVAO);
    glGenBuffers(1,&quadVBO);
    glBindVertexArray(quadVAO);
    glBindBuffer(GL_ARRAY_BUFFER,quadVBO);
    glBufferData(GL_ARRAY_BUFFER,sizeof(quadVertices),&quadVertices,GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,5*sizeof(GLfloat),(GLvoid*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1,2,GL_FLOAT,GL_FALSE,5*sizeof(GLfloat),(GLvoid*)(3*sizeof(GLfloat)));
    return quadVAO;
}
void renderQuad(GLuint quadVAO){
    glBindVertexArray(quadVAO);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glBindVertexArray(0);
}

int bloom(){
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);//设置上下文主要版本号
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);//次要版本号
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GL_SAMPLES, 4);//四个采样点
    //GLFW_OPENGL_PROFILE宏用于指定OpenGL上下文的配置文件类型
    //GLFW_OPENGL_CORE_PROFILE宏用于表示使用核心配置文件
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    //启用向前兼容模式，允许在较新的版本中使用较旧的特性
#endif

    GLFWwindow* window=glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "learnOpenGL", NULL, NULL);
    try{
        if(window==nullptr)
            throw std::runtime_error("window generated unsuccessfully");
    }catch(std::runtime_error err){
        cerr<<err.what()<<"\n";
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    try{
        if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
            throw std::runtime_error("fail to initialize GLAD");
    }catch(std::runtime_error err){
        cerr<<err.what()<<"\n";
        glfwTerminate();
        return -1;
    }

    glEnable(GL_DEPTH_TEST);
    
    Shader *lightshader=new Shader("/Users/sherlock/Documents/Code/OpenGLdemo/OpenGLdemo/AdvancedLighting/Bloom/frame.vs","/Users/sherlock/Documents/Code/OpenGLdemo/OpenGLdemo/AdvancedLighting/Bloom/lightbox.fs");
    Shader *objectshader=new Shader("/Users/sherlock/Documents/Code/OpenGLdemo/OpenGLdemo/AdvancedLighting/Bloom/frame.vs","/Users/sherlock/Documents/Code/OpenGLdemo/OpenGLdemo/AdvancedLighting/Bloom/frame.fs");
    Shader *blurshader=new Shader("/Users/sherlock/Documents/Code/OpenGLdemo/OpenGLdemo/AdvancedLighting/Bloom/blur.vs","/Users/sherlock/Documents/Code/OpenGLdemo/OpenGLdemo/AdvancedLighting/Bloom/blur.fs");
    Shader *shader=new Shader("/Users/sherlock/Documents/Code/OpenGLdemo/OpenGLdemo/AdvancedLighting/Bloom/scene.vs","/Users/sherlock/Documents/Code/OpenGLdemo/OpenGLdemo/AdvancedLighting/Bloom/scene.fs");
    Shader *subsceneshader=new Shader("/Users/sherlock/Documents/Code/OpenGLdemo/OpenGLdemo/AdvancedLighting/Bloom/scene.vs","/Users/sherlock/Documents/Code/OpenGLdemo/OpenGLdemo/AdvancedLighting/Bloom/subscene.fs");
    
    GLuint woodTexture=loadTexture("/Users/sherlock/Documents/Code/OpenGLdemo/OpenGLdemo/resource/wood.png", true);
    GLuint containerTexture=loadTexture("/Users/sherlock/Documents/Code/OpenGLdemo/OpenGLdemo/resource/container2.png", true);
    
    GLuint framebuffer,colorBuffers[2],rboDepth;
    glGenFramebuffers(1,&framebuffer);
    glGenTextures(2,colorBuffers);
    glBindFramebuffer(GL_FRAMEBUFFER,framebuffer);
    for(GLuint i=0;i<2;i++){
        glBindTexture(GL_TEXTURE_2D,*(colorBuffers+i));
        glTexImage2D(GL_TEXTURE_2D,0,GL_RGB16F,SCR_WIDTH*2,SCR_HEIGHT*2,0,GL_RGBA,GL_FLOAT,NULL);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);
        glFramebufferTexture2D(GL_FRAMEBUFFER,GL_COLOR_ATTACHMENT0+i,GL_TEXTURE_2D,(*colorBuffers+i),0);
    }
    glGenRenderbuffers(1,&rboDepth);
    glBindRenderbuffer(GL_RENDERBUFFER,rboDepth);
    glRenderbufferStorage(GL_RENDERBUFFER,GL_DEPTH_COMPONENT,SCR_WIDTH*2,SCR_HEIGHT*2);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER,GL_DEPTH_ATTACHMENT,GL_RENDERBUFFER,rboDepth);
    //渲染到两个纹理上
    GLuint attachments[2]={GL_COLOR_ATTACHMENT0,GL_COLOR_ATTACHMENT1};
    glDrawBuffers(2,attachments);
    
    try{
        if(glCheckFramebufferStatus(GL_FRAMEBUFFER)!=GL_FRAMEBUFFER_COMPLETE)
            throw std::runtime_error("ERROR::FRAMEBUFFER::Framebuffer is not complete!");
    }catch(const std::runtime_error &err){
        cerr<<err.what()<<"\n";
        throw;
    }
    glBindFramebuffer(GL_FRAMEBUFFER,0);

    GLuint cubeVAO=loadCubeBuffer();
    GLuint quadVAO=loadQuadBuffer();
    
    GLuint pingpongFramebuffer[2],pingpongColorbuffer[2];
    glGenFramebuffers(2,pingpongFramebuffer);
    glGenTextures(2,pingpongColorbuffer);
    for(int i=0;i<2;i++){
        glBindFramebuffer(GL_FRAMEBUFFER,*(pingpongFramebuffer+i));
        glBindTexture(GL_TEXTURE_2D,*(pingpongColorbuffer+i));
        glTexImage2D(GL_TEXTURE_2D,0,GL_RGB16F,SCR_WIDTH*2,SCR_HEIGHT*2,0,GL_RGBA,GL_FLOAT,NULL);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);
        glFramebufferTexture2D(GL_FRAMEBUFFER,GL_COLOR_ATTACHMENT0,GL_TEXTURE_2D,*(pingpongColorbuffer+i),0);
        
        try{
            if(glCheckFramebufferStatus(GL_FRAMEBUFFER)!=GL_FRAMEBUFFER_COMPLETE)
                throw std::runtime_error("ERROR::FRAMEBUFFER::Framebuffer is not complete!");
        }catch(const std::runtime_error &err){
            cerr<<err.what()<<"\n";
            throw;
        }
    }
    
    std::vector<glm::vec3> lightPositions;
    lightPositions.push_back(glm::vec3(0.0f,0.5f,1.5f));
    lightPositions.push_back(glm::vec3(-4.0f,0.5f,-3.0f));
    lightPositions.push_back(glm::vec3(3.0f,0.5f,1.0f));
    lightPositions.push_back(glm::vec3(-0.8f,2.4f,-1.0f));
    std::vector<glm::vec3> lightColors;
    lightColors.push_back(glm::vec3(5.0f,5.0f,5.0f));
    lightColors.push_back(glm::vec3(10.0f,0.0f,0.0f));
    lightColors.push_back(glm::vec3(0.0f,0.0f,15.0f));
    lightColors.push_back(glm::vec3(0.0f,5.0f,0.0f));
    
    blurshader->use();
    blurshader->setInt("image", 0);
    objectshader->use();
    objectshader->setInt("diffuseTexture", 0);
    shader->use();
    shader->setInt("rawscene", 0);
    shader->setInt("bloomscene", 1);
    subsceneshader->use();
    subsceneshader->setInt("subtexture", 0);

    while(!glfwWindowShouldClose(window)){
        GLfloat currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastTime;
        lastTime = currentFrame;

        processInput(window, mouse_callback, scroll_callback);
        processCameraWSAD(window, camera, deltaTime);
        lighting_control(window);

        glEnable(GL_DEPTH_TEST);
        
        glClearColor(0.1f,0.1f,0.1f,1.0f);
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

        glBindFramebuffer(GL_FRAMEBUFFER,framebuffer);
        glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);
        glm::mat4 projection=glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH/(float)SCR_HEIGHT, 0.1f, 100.0f);
        glm::mat4 view=camera.GetViewMatrix();
        glm::mat4 model=glm::mat4(1.0f);
        model=glm::scale(glm::translate(model,glm::vec3(0.0f,-1.0f,0.0f)), glm::vec3(12.5f,0.5f,12.5f));
        objectshader->use();
        objectshader->setMat4("projection", projection);
        objectshader->setMat4("view", view);
        objectshader->setMat4("model", model);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D,woodTexture);
        objectshader->setMat3("normalMatrix", glm::transpose(glm::inverse(glm::mat3(model))));
        objectshader->setVec3("viewPos", camera.Position);
        for(int i=0;i<lightPositions.size();i++){
            objectshader->setVec3("lights["+std::to_string(i)+"].Position",lightPositions[i]);
            objectshader->setVec3("lights["+std::to_string(i)+"].Color",lightColors[i]);
        }
        renderCube(cubeVAO);//ground
        
        glBindTexture(GL_TEXTURE_2D,containerTexture);
        model=glm::scale(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f,1.5f,0.0f)), glm::vec3(0.5f));
        objectshader->setMat4("model", model);
        objectshader->setMat3("normalMatrix", glm::transpose(glm::inverse(glm::mat3(model))));
        renderCube(cubeVAO);//box1
        
        model=glm::scale(glm::translate(glm::mat4(1.0f), glm::vec3(2.0f,0.0f,1.0f)), glm::vec3(0.5f));
        objectshader->setMat4("model", model);
        objectshader->setMat3("normalMatrix", glm::transpose(glm::inverse(glm::mat3(model))));
        renderCube(cubeVAO);//box2

        model=glm::rotate(glm::translate(glm::mat4(1.0f), glm::vec3(-1.0f,-1.0f,2.0f)), glm::radians(60.0f),glm::normalize(glm::vec3(1.0f,0.0f,1.0f)));
        objectshader->setMat4("model", model);
        objectshader->setMat3("normalMatrix", glm::transpose(glm::inverse(glm::mat3(model))));
        renderCube(cubeVAO);//box3

        model=glm::scale(glm::rotate(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f,2.7f,4.0f)), glm::radians(23.0f),glm::normalize(glm::vec3(1.0f,0.0f,1.0f))),glm::vec3(1.25f));
        objectshader->setMat4("model", model);
        objectshader->setMat3("normalMatrix", glm::transpose(glm::inverse(glm::mat3(model))));
        renderCube(cubeVAO);//box4
        
        model=glm::rotate(glm::translate(glm::mat4(1.0f), glm::vec3(-2.0f,1.0f,-3.0f)), glm::radians(124.0f),glm::normalize(glm::vec3(1.0f,0.0f,1.0f)));
        objectshader->setMat4("model", model);
        objectshader->setMat3("normalMatrix", glm::transpose(glm::inverse(glm::mat3(model))));
        renderCube(cubeVAO);//box5
        
        model=glm::scale(glm::translate(glm::mat4(1.0f), glm::vec3(-3.0f,0.0f,0.0f)), glm::vec3(0.5f));
        objectshader->setMat4("model", model);
        objectshader->setMat4("normalMatrix", glm::transpose(glm::inverse(glm::mat3(model))));
        renderCube(cubeVAO);//box6
        
        lightshader->use();
        lightshader->setMat4("projection", projection);
        lightshader->setMat4("view", view);
        for(int i=0;i<lightColors.size();i++){
            lightshader->setVec3("lightColor", lightColors[i]);
            model=glm::scale(glm::translate(glm::mat4(1.0f), lightPositions[i]), glm::vec3(0.25f));
            lightshader->setMat4("model", model);
            lightshader->setMat3("normalMatrix", glm::transpose(glm::inverse(glm::mat3(model))));
            renderCube(cubeVAO);
        }//light*4
        
        //上面步骤结束之后，framebuffer所绑定的两个纹理一个存储映射后上限为1的低光场景，另一个存储超过1的高光场景
        //下面需要对高光场景进行Gaussian模糊
        blurshader->use();
        bool horizontal=true,first_iteration=true;
        unsigned int amount=32;
        for(int i=0;i<amount;i++){
            glBindFramebuffer(GL_FRAMEBUFFER,pingpongFramebuffer[horizontal]);
            blurshader->setBool("horizontal", horizontal);
            glBindTexture(GL_TEXTURE_2D,first_iteration?colorBuffers[1]:pingpongColorbuffer[!horizontal]);
            renderQuad(quadVAO);
            horizontal=!horizontal;
            if(first_iteration)
                first_iteration=false;
        }
        //每张framebuffer的纹理在被渲染之前，其纹理都可以看作空白，被渲染之后，原本的颜色值也会被抹除。首先将先前渲染的高光纹理渲染至其中一个纹理上，在这个渲染过程中，其实每个像素已经进行了水平模糊。这张纹理将用于第二轮渲染，在渲染过程中，又进行了垂直模糊。往返10次
        
        glBindFramebuffer(GL_FRAMEBUFFER,0);
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
        shader->use();
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D,colorBuffers[0]);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D,pingpongColorbuffer[!horizontal]);//!horizontal==true
        shader->setInt("bloom", bloom_);
        shader->setFloat("exposure", exposure);
        renderQuad(quadVAO);
        
        std::cout << "bloom: " << (bloom_ ? "on" : "off") << " | exposure: " << exposure << std::endl;
        
        glDisable(GL_DEPTH_TEST);
        subsceneshader->use();
        glViewport(0,0,(SCR_WIDTH*2)/4,(SCR_HEIGHT*2)/4);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D,pingpongColorbuffer[!horizontal]);
        renderQuad(quadVAO);
        
        glViewport(0,0,SCR_WIDTH*2,SCR_HEIGHT*2);
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    delete shader;
    shader=nullptr;
    delete blurshader;
    blurshader=nullptr;
    delete objectshader;
    objectshader=nullptr;
    delete lightshader;
    lightshader=nullptr;
    glDeleteFramebuffers(2,pingpongFramebuffer);
    glDeleteTextures(2,pingpongColorbuffer);
    glDeleteFramebuffers(1,&framebuffer);
    glDeleteTextures(2,colorBuffers);
    glDeleteRenderbuffers(1,&rboDepth);
    
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

void lighting_control(GLFWwindow* window){
    if(glfwGetKey(window,GLFW_KEY_SPACE)==GLFW_PRESS&&!hdrKeyPressed){
        hdr_=!hdr_;
        hdrKeyPressed=true;//保证每次按空格只会生效一次
    }
    if(glfwGetKey(window, GLFW_KEY_SPACE)==GLFW_RELEASE)
        hdrKeyPressed=false;
    if(glfwGetKey(window, GLFW_KEY_H)==GLFW_PRESS&&!ReinhardPressed){
        Reinhard=!Reinhard;
        ReinhardPressed=true;
    }
    if(glfwGetKey(window, GLFW_KEY_H)==GLFW_RELEASE)
        ReinhardPressed=false;
    if(glfwGetKey(window, GLFW_KEY_B)==GLFW_PRESS&&!bloomPressed){
        bloom_=!bloom_;
        bloomPressed=true;
    }
    if(glfwGetKey(window, GLFW_KEY_B)==GLFW_RELEASE)
        bloomPressed=false;
    if(glfwGetKey(window,GLFW_KEY_Q)==GLFW_PRESS){
        if(exposure>0.0f)
            exposure-=0.01f;
        else
            exposure=0.0f;
    }else if(glfwGetKey(window, GLFW_KEY_E)==GLFW_PRESS)
        exposure+=0.01f;
}


