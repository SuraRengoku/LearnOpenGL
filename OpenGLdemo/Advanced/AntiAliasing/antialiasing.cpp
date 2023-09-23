//
//  antialiasing.cpp
//  OpenGLdemo
//
//  Created by SHERLOCK on 23.09.23.
//

#include "antialiasing.hpp"
#define Default_Width 1200;
#define Default_Height 800;

static unsigned const int SCR_WIDTH=Default_Width;
static unsigned const int SCR_HEIGHT=Default_Height;

Camera camera(glm::vec3(0.0f,0.0f,3.0f));
bool firstMouse=true;
float lastX=SCR_WIDTH/2.0f;
float lastY=SCR_HEIGHT/2.0f;

static float deltaTime=0.0f;
static float lastTime=0.0f;

void mouse_callback(GLFWwindow* window, double xposIn, double yposIn);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

static float cubeVertices[] = {
    // positions
    -0.5f, -0.5f, -0.5f,
     0.5f, -0.5f, -0.5f,
     0.5f,  0.5f, -0.5f,
     0.5f,  0.5f, -0.5f,
    -0.5f,  0.5f, -0.5f,
    -0.5f, -0.5f, -0.5f,

    -0.5f, -0.5f,  0.5f,
     0.5f, -0.5f,  0.5f,
     0.5f,  0.5f,  0.5f,
     0.5f,  0.5f,  0.5f,
    -0.5f,  0.5f,  0.5f,
    -0.5f, -0.5f,  0.5f,

    -0.5f,  0.5f,  0.5f,
    -0.5f,  0.5f, -0.5f,
    -0.5f, -0.5f, -0.5f,
    -0.5f, -0.5f, -0.5f,
    -0.5f, -0.5f,  0.5f,
    -0.5f,  0.5f,  0.5f,

     0.5f,  0.5f,  0.5f,
     0.5f,  0.5f, -0.5f,
     0.5f, -0.5f, -0.5f,
     0.5f, -0.5f, -0.5f,
     0.5f, -0.5f,  0.5f,
     0.5f,  0.5f,  0.5f,

    -0.5f, -0.5f, -0.5f,
     0.5f, -0.5f, -0.5f,
     0.5f, -0.5f,  0.5f,
     0.5f, -0.5f,  0.5f,
    -0.5f, -0.5f,  0.5f,
    -0.5f, -0.5f, -0.5f,

    -0.5f,  0.5f, -0.5f,
     0.5f,  0.5f, -0.5f,
     0.5f,  0.5f,  0.5f,
     0.5f,  0.5f,  0.5f,
    -0.5f,  0.5f,  0.5f,
    -0.5f,  0.5f, -0.5f
};
static float quadVertices[] = {
    // vertex attributes for a quad that fills the entire screen in Normalized Device Coordinates.
    // positions   // texCoords
    -1.0f,  1.0f,  0.0f, 1.0f,
    -1.0f, -1.0f,  0.0f, 0.0f,
     1.0f, -1.0f,  1.0f, 0.0f,

    -1.0f,  1.0f,  0.0f, 1.0f,
     1.0f, -1.0f,  1.0f, 0.0f,
     1.0f,  1.0f,  1.0f, 1.0f
};

int antialiasing(){
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
    
    Shader *shader=new Shader("/Users/sherlock/Documents/Code/OpenGLdemo/OpenGLdemo/Advanced/AntiAliasing/antialiasing.vs","/Users/sherlock/Documents/Code/OpenGLdemo/OpenGLdemo/Advanced/AntiAliasing/antialiasing.fs");
    Shader *screenshader=new Shader("/Users/sherlock/Documents/Code/OpenGLdemo/OpenGLdemo/Advanced/AntiAliasing/screenshader.vs","/Users/sherlock/Documents/Code/OpenGLdemo/OpenGLdemo/Advanced/AntiAliasing/screenshader.fs");
    
    unsigned int cubeVAO,cubeVBO,quadVAO,quadVBO;
    glGenVertexArrays(1,&cubeVAO);
    glGenVertexArrays(1,&quadVAO);
    glGenBuffers(1,&cubeVBO);
    glGenBuffers(1,&quadVBO);
    
    glBindVertexArray(cubeVAO);
    glBindBuffer(GL_ARRAY_BUFFER,cubeVBO);
    glBufferData(GL_ARRAY_BUFFER,sizeof(cubeVertices),&cubeVertices,GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3*sizeof(GL_FLOAT),(void*)0);
    
    glBindVertexArray(quadVAO);
    glBindBuffer(GL_ARRAY_BUFFER,quadVBO);
    glBufferData(GL_ARRAY_BUFFER,sizeof(quadVertices),&quadVertices,GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0,2,GL_FLOAT,GL_FALSE,4*sizeof(GL_FLOAT),(void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1,2,GL_FLOAT,GL_FALSE,4*sizeof(GL_FLOAT),(void*)(2*sizeof(GL_FLOAT)));
    
    unsigned int framebuffer;
    glGenFramebuffers(1,&framebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER,framebuffer);
    unsigned int textureColorbuffer;
    glGenTextures(1,&textureColorbuffer);
    glBindTexture(GL_TEXTURE_2D_MULTISAMPLE,textureColorbuffer);
    /**
     @param GLenum target 纹理目标
     @param GLsizei samples 样本数量
     @param GLenum internalformat 纹理格式
     @param GLsizei width
     @param GLsizei height
     @param GLboolean fixedsamplelocations 固定样本位置
     */
    glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE,4,GL_RGB,SCR_WIDTH,SCR_HEIGHT,GL_TRUE);
    glBindTexture(GL_TEXTURE_2D_MULTISAMPLE,0);
    glFramebufferTexture2D(GL_FRAMEBUFFER,GL_COLOR_ATTACHMENT0,GL_TEXTURE_2D_MULTISAMPLE,textureColorbuffer,0);
//    glBindTexture(GL_TEXTURE_2D,textureColorbuffer);
//    glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,SCR_WIDTH,SCR_HEIGHT,0,GL_RGB,GL_UNSIGNED_BYTE,NULL);
//    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
//    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
//    glFramebufferTexture2D(GL_FRAMEBUFFER,GL_COLOR_ATTACHMENT0,GL_TEXTURE_2D,textureColorbuffer,0);

    unsigned int rbo;
    glGenRenderbuffers(1,&rbo);
    glBindRenderbuffer(GL_RENDERBUFFER,rbo);
    glRenderbufferStorageMultisample(GL_RENDERBUFFER,4,GL_DEPTH24_STENCIL8,SCR_WIDTH,SCR_HEIGHT);
    glBindRenderbuffer(GL_RENDERBUFFER,0);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER,GL_DEPTH_STENCIL_ATTACHMENT,GL_RENDERBUFFER,rbo);
    
    try{
        if(glCheckFramebufferStatus(GL_FRAMEBUFFER)!=GL_FRAMEBUFFER_COMPLETE)
            throw std::runtime_error("ERROR::FRAMEBUFFER:: Framebuffer is not complete!");
    }catch(const std::runtime_error &err){
        cerr<<err.what()<<"\n";
        throw;
    }
    
    // configure second post-processing framebuffer
    unsigned int intermediateFBO;
    glGenFramebuffers(1, &intermediateFBO);
    glBindFramebuffer(GL_FRAMEBUFFER, intermediateFBO);
    // create a color attachment texture
    unsigned int screenTexture;
    glGenTextures(1, &screenTexture);
    glBindTexture(GL_TEXTURE_2D, screenTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, SCR_WIDTH, SCR_HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, screenTexture, 0);    // we only need a color buffer

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        cout << "ERROR::FRAMEBUFFER:: Intermediate framebuffer is not complete!" << endl;
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    
    screenshader->use();
    screenshader->setInt("screenTexture", 0);
    
    while(!glfwWindowShouldClose(window)){
        float currentTime=static_cast<float>(glfwGetTime());
        deltaTime=currentTime-lastTime;
        lastTime=currentTime;

        processInput(window, mouse_callback, scroll_callback);
        processCameraWSAD(window, camera, deltaTime);
        
        glBindFramebuffer(GL_FRAMEBUFFER,framebuffer);
        glEnable(GL_DEPTH_TEST);
        
        glClearColor(0.1f,0.1f,0.1f,1.0f);
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

        shader->use();
        glm::mat4 model = glm::mat4(1.0f);
        glm::mat4 view = camera.GetViewMatrix();
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 1000.0f);
        shader->setMat4("view", view);
        shader->setMat4("projection", projection);
        shader->setMat4("model", model);
        
        glBindVertexArray(cubeVAO);
        glDrawArrays(GL_TRIANGLES,0,36);
        
        glBindFramebuffer(GL_READ_FRAMEBUFFER,framebuffer);
        glBindFramebuffer(GL_DRAW_FRAMEBUFFER,intermediateFBO);
        /**
         @param GLint srcX0, srcY0, srcX1, srcY1
         @param GLint dstX0, dstY0, dstX1, dstY1
         @param GLbitfield mask 指定需要复制的缓冲区
         @param GLenum filter
         */
        glBlitFramebuffer(0,0,SCR_WIDTH,SCR_HEIGHT,0,0,SCR_WIDTH,SCR_HEIGHT,GL_COLOR_BUFFER_BIT,GL_NEAREST);//将一个帧缓冲中的某个区域复制到另一个帧缓冲中，并且将多重采样缓冲还原,这也是为什么在该语句执行后textureColorbuffer和screenTexture都可以作为纹理渲染
        
        //默认帧缓冲，屏幕空间
        glBindFramebuffer(GL_FRAMEBUFFER,0);
        
        glDisable(GL_DEPTH_TEST);
        
        //此时只是绘制四边形，所以需要禁用深度测试
        glClearColor(0.1f,0.1f,0.1f,1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        screenshader->use();
        glBindVertexArray(quadVAO);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D,textureColorbuffer);
        glDrawArrays(GL_TRIANGLES,0,6);
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    delete shader;
    shader=nullptr;
    delete screenshader;
    screenshader=nullptr;
    glDeleteBuffers(1,&cubeVBO);
    glDeleteBuffers(1,&quadVBO);
    glDeleteVertexArrays(1,&cubeVAO);
    glDeleteVertexArrays(1,&quadVAO);
    
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
