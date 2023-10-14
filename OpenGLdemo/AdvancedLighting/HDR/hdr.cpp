//
//  hdr.cpp
//  OpenGLdemo
//
//  Created by SHERLOCK on 13.10.23.
//

#include "hdr.hpp"
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
static float exposure=1.0f;

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

int hdr(){
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

    GLuint cubeVAO=loadCubeBuffer();
    GLuint quadVAO=loadQuadBuffer();

    Shader *shader=new Shader("/Users/sherlock/Documents/Code/OpenGLdemo/OpenGLdemo/AdvancedLighting/HDR/scene.vs","/Users/sherlock/Documents/Code/OpenGLdemo/OpenGLdemo/AdvancedLighting/HDR/scene.fs");
    Shader *hdrshader=new Shader("/Users/sherlock/Documents/Code/OpenGLdemo/OpenGLdemo/AdvancedLighting/HDR/hdr.vs","/Users/sherlock/Documents/Code/OpenGLdemo/OpenGLdemo/AdvancedLighting/HDR/hdr.fs");

    GLuint woodTexture=loadTexture("/Users/sherlock/Documents/Code/OpenGLdemo/OpenGLdemo/resource/wood.png", true);

    unsigned int frameBuffer,colorBuffer,rbo;
    glGenFramebuffers(1,&frameBuffer);
    glGenTextures(1,&colorBuffer);
    glGenRenderbuffers(1,&rbo);

    glBindTexture(GL_TEXTURE_2D,colorBuffer);
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGB16F,SCR_WIDTH,SCR_HEIGHT,0,GL_RGBA,GL_FLOAT,NULL);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

    glBindRenderbuffer(GL_RENDERBUFFER,rbo);
    glRenderbufferStorage(GL_RENDERBUFFER,GL_DEPTH_COMPONENT,SCR_WIDTH,SCR_HEIGHT);

    glBindFramebuffer(GL_FRAMEBUFFER,frameBuffer);
    glFramebufferTexture2D(GL_FRAMEBUFFER,GL_COLOR_ATTACHMENT0,GL_TEXTURE_2D,colorBuffer,0);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER,GL_DEPTH_ATTACHMENT,GL_RENDERBUFFER,rbo);

    try{
        if(glCheckFramebufferStatus(GL_FRAMEBUFFER)!=GL_FRAMEBUFFER_COMPLETE)
            throw std::runtime_error("ERROR::FRAMEBUFFER::Framebuffer is not complete!");
    }catch(const std::runtime_error &err){
        cerr<<err.what()<<"\n";
        throw;
    }
    glBindFramebuffer(GL_FRAMEBUFFER,0);

    std::vector<glm::vec3> lightPositions;
    lightPositions.push_back(glm::vec3(0.0f,0.0f,49.5f));
    lightPositions.push_back(glm::vec3(-1.4f,-1.9f,9.0f));
    lightPositions.push_back(glm::vec3(0.0f,-1.8f,4.0f));
    lightPositions.push_back(glm::vec3(0.8f,-1.7f,6.0f));

    std::vector<glm::vec3> lightColors;
    lightColors.push_back(glm::vec3(200.0f,200.0f,200.0f));
    lightColors.push_back(glm::vec3(0.1f,0.0f,0.0f));
    lightColors.push_back(glm::vec3(0.0f,0.0f,0.2f));
    lightColors.push_back(glm::vec3(0.0f,0.1f,0.0f));

    hdrshader->use();
    hdrshader->setInt("diffuseTexture", 0);
    shader->use();
    shader->setInt("hdrBuffer", 0);

    while (!glfwWindowShouldClose(window)) {
        GLfloat currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastTime;
        lastTime = currentFrame;

        processInput(window, mouse_callback, scroll_callback);
        processCameraWSAD(window, camera, deltaTime);
        lighting_control(window);

        glClearColor(0.1f,0.1f,0.1f,1.0f);
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

        hdrshader->use();
        glBindFramebuffer(GL_FRAMEBUFFER,frameBuffer);
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
        glm::mat4 view=camera.GetViewMatrix();
        glm::mat4 projection=glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH/(float)SCR_HEIGHT, 0.1f, 100.0f);
        glm::mat4 model=glm::scale(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f,0.0f,25.0f)), glm::vec3(2.5f,2.5f,27.5f));
        glm::mat3 normalMatrix=glm::transpose(glm::inverse(glm::mat3(model)));
        for(unsigned int i=0;i<lightPositions.size();i++){
            hdrshader->setVec3("lights["+std::to_string(i)+"].Position", lightPositions[i]);
            hdrshader->setVec3("lights["+std::to_string(i)+"].Color", lightColors[i]);
        }
        hdrshader->setMat4("projection", projection);
        hdrshader->setMat4("view", view);
        hdrshader->setMat4("model", model);
        hdrshader->setVec3("viewPos", camera.Position);
        hdrshader->setMat3("normalMatrix", normalMatrix);
        hdrshader->setBool("inverse_normals", true);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D,woodTexture);
        renderCube(cubeVAO);

        glBindFramebuffer(GL_FRAMEBUFFER,0);
        glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);
        shader->use();
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D,colorBuffer);
        shader->setBool("hdr", hdr_);
        shader->setBool("Reinhard", Reinhard);
        shader->setFloat("exposure", exposure);
        renderQuad(quadVAO);

        cout<<"hdr:"<<(hdr_?"on":"off")<<" | exposure "<<exposure<<"\n";
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    delete shader;
    shader=nullptr;
    delete hdrshader;
    hdrshader=nullptr;

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
    if(glfwGetKey(window,GLFW_KEY_Q)==GLFW_PRESS){
        if(exposure>0.0f)
            exposure-=0.01f;
        else
            exposure=0.0f;
    }else if(glfwGetKey(window, GLFW_KEY_E)==GLFW_PRESS)
        exposure+=0.01f;
}


