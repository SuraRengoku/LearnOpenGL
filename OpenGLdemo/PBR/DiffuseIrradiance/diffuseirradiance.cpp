//
//  diffuseirradiance.cpp
//  OpenGLdemo
//
//  Created by SHERLOCK on 30.10.23.
//

#include "diffuseirradiance.hpp"
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
//
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void lighting_control(GLFWwindow* window);
//
static bool hdr_=true;
static bool hdrKeyPressed=false;
static bool Reinhard=true;
static bool ReinhardPressed=false;
static bool bloom_=true;
static bool bloomPressed=false;
static float exposure=1.0f;

int diffuseirradiance(){
    GLFWwindow* window=glfw_Init(SCR_WIDTH, SCR_HEIGHT, mouse_callback, scroll_callback);
    
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);//小于等于
    
    glm::vec3 lightPositions[] = {
        glm::vec3(-10.0f,  10.0f, 10.0f),
        glm::vec3( 10.0f,  10.0f, 10.0f),
        glm::vec3(-10.0f, -10.0f, 10.0f),
        glm::vec3( 10.0f, -10.0f, 10.0f),
    };
    glm::vec3 lightColors[] = {
        glm::vec3(300.0f, 300.0f, 300.0f),
        glm::vec3(300.0f, 300.0f, 300.0f),
        glm::vec3(300.0f, 300.0f, 300.0f),
        glm::vec3(300.0f, 300.0f, 300.0f)
    };
    int nrRows = 7;
    int nrColumns = 7;
    float spacing = 2.5;

    GLuint hdrEMap=loadTextureHDR("/Users/sherlock/Documents/Code/OpenGLdemo/OpenGLdemo/resource/newport_loft.hdr");//等距柱状投影图 Equirectangular Map
    
    //将等距柱状投影图转换成立方体贴图
    unsigned int captureFBO,captureRBO,envCubemap;
    glGenFramebuffers(1,&captureFBO);
    glGenRenderbuffers(1,&captureRBO);
    glGenTextures(1,&envCubemap);
    
    glBindFramebuffer(GL_FRAMEBUFFER,captureFBO);
    glBindRenderbuffer(GL_RENDERBUFFER,captureRBO);
    glRenderbufferStorage(GL_RENDERBUFFER,GL_DEPTH_COMPONENT24,512*4,512*4);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER,GL_DEPTH_ATTACHMENT,GL_RENDERBUFFER,captureRBO);
    glBindTexture(GL_TEXTURE_CUBE_MAP,envCubemap);
    for(unsigned int i=0;i<6;i++){
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X+i,0,GL_RGB16F,512*4,512*4,0,GL_RGB,GL_FLOAT,nullptr);
    }//为六个面分配内存
    glTexParameteri(GL_TEXTURE_CUBE_MAP,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP,GL_TEXTURE_WRAP_R,GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    
    glm::mat4 captureProjection=glm::perspective(glm::radians(90.0f), 1.0f, 0.1f, 10.0f);
    glm::mat4 captureViews[]={
        glm::lookAt(glm::vec3(0.0f,0.0f,0.0f), glm::vec3(1.0f,0.0f,0.0f), glm::vec3(0.0f,-1.0f,0.0f)),
        glm::lookAt(glm::vec3(0.0f,0.0f,0.0f), glm::vec3(-1.0f,0.0f,0.0f), glm::vec3(0.0f,-1.0f,0.0f)),
        glm::lookAt(glm::vec3(0.0f,0.0f,0.0f), glm::vec3(0.0f,1.0f,0.0f), glm::vec3(0.0f,0.0f,1.0f)),
        glm::lookAt(glm::vec3(0.0f,0.0f,0.0f), glm::vec3(0.0f,-1.0f,0.0f), glm::vec3(0.0f,0.0f,-1.0f)),
        glm::lookAt(glm::vec3(0.0f,0.0f,0.0f), glm::vec3(0.0f,0.0f,1.0f), glm::vec3(0.0f,-1.0f,0.0f)),
        glm::lookAt(glm::vec3(0.0f,0.0f,0.0f), glm::vec3(0.0f,0.0f,-1.0f), glm::vec3(0.0f,-1.0f,0.0f)),
    };
    
    CubeRender *cube=new CubeRender();
    SphereRender *sphere=new SphereRender(64);
    
    Shader* toCubeMap=new Shader("/Users/sherlock/Documents/Code/OpenGLdemo/OpenGLdemo/PBR/DiffuseIrradiance/toCubeMap.vs","/Users/sherlock/Documents/Code/OpenGLdemo/OpenGLdemo/PBR/DiffuseIrradiance/toCubeMap.fs");
    
    Shader* cubeMap=new Shader("/Users/sherlock/Documents/Code/OpenGLdemo/OpenGLdemo/PBR/DiffuseIrradiance/cubemaps.vs","/Users/sherlock/Documents/Code/OpenGLdemo/OpenGLdemo/PBR/DiffuseIrradiance/cubemaps.fs");
    
    Shader* sphereShader=new Shader("/Users/sherlock/Documents/Code/OpenGLdemo/OpenGLdemo/PBR/lighting/directpbr.vs","/Users/sherlock/Documents/Code/OpenGLdemo/OpenGLdemo/PBR/DiffuseIrradiance/irradiancePBR.fs");
    
    sphereShader->use();
    sphereShader->setInt("irradianceMap", 0);
    
    Shader* irradianceShader=new Shader("/Users/sherlock/Documents/Code/OpenGLdemo/OpenGLdemo/PBR/DiffuseIrradiance/cubemaps.vs","/Users/sherlock/Documents/Code/OpenGLdemo/OpenGLdemo/PBR/DiffuseIrradiance/irradianceMap.fs");
    
    cubeMap->use();
    cubeMap->setInt("environmentMap", 0);
    
    toCubeMap->use();
    toCubeMap->setInt("equirectangularMap", 0);
    toCubeMap->setMat4("projection", captureProjection);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D,hdrEMap);
    
    glViewport(0,0,512*4,512*4);
    glBindFramebuffer(GL_FRAMEBUFFER,captureFBO);
    for(unsigned int i=0;i<6;i++){
        toCubeMap->setMat4("view", captureViews[i]);
        glFramebufferTexture2D(GL_FRAMEBUFFER,GL_COLOR_ATTACHMENT0,GL_TEXTURE_CUBE_MAP_POSITIVE_X+i,envCubemap,0);
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
        cube->render();
    }
    glBindFramebuffer(GL_FRAMEBUFFER,0);
        
    sphereShader->use();
    sphereShader->setVec3("albedo", 0.5f, 0.0f, 0.0f);
    sphereShader->setFloat("ao", 1.0f);
    
    
    glBindFramebuffer(GL_FRAMEBUFFER,captureFBO);
    glBindRenderbuffer(GL_RENDERBUFFER,captureRBO);
    glRenderbufferStorage(GL_RENDERBUFFER,GL_DEPTH_COMPONENT24,32,32);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER,GL_DEPTH_ATTACHMENT,GL_RENDERBUFFER,captureRBO);

    unsigned int irradianceMap;
    glGenTextures(1,&irradianceMap);
    glBindTexture(GL_TEXTURE_CUBE_MAP,irradianceMap);
    for(unsigned int i=0;i<6;i++){
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X+i,0,GL_RGB16F,32,32,0,GL_RGB,GL_FLOAT,nullptr);
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP,GL_TEXTURE_WRAP_R,GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    
    irradianceShader->use();
    irradianceShader->setMat4("projection", captureProjection);
    irradianceShader->setInt("environmentMap", 0);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP,envCubemap);
    
    glViewport(0,0,32,32);
    for(unsigned int i=0;i<6;i++){
        irradianceShader->setMat4("view", captureViews[i]);
        glFramebufferTexture2D(GL_FRAMEBUFFER,GL_COLOR_ATTACHMENT0,GL_TEXTURE_CUBE_MAP_POSITIVE_X+i,irradianceMap,0);
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
        cube->render();
    }
    glBindFramebuffer(GL_FRAMEBUFFER,0);
    
    int scrWidth,scrHeight;
    glfwGetFramebufferSize(window, &scrWidth, &scrHeight);
    glViewport(0,0,scrWidth,scrHeight);
    
    while (!glfwWindowShouldClose(window)) {
        float currentTime = static_cast<float>(glfwGetTime());
        deltaTime = currentTime - lastTime;
        lastTime = currentTime;

        processInput(window,mouse_callback,scroll_callback);
        processCameraWSAD(window, camera, deltaTime);

        glClearColor(0.2f,0.3f,0.3f,1.0f);
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
        
        glm::mat4 projection=glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH/(float)SCR_HEIGHT, 0.1f, 100.0f);
        cubeMap->use();
        cubeMap->setMat4("projection", projection);
        glm::mat4 view=camera.GetViewMatrix();
        cubeMap->setMat4("view", view);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_CUBE_MAP,envCubemap);
//        glBindTexture(GL_TEXTURE_CUBE_MAP,irradianceMap);//debug辐照贴图
        cube->render();

        sphereShader->use();
        sphereShader->setVec3("camPos", camera.Position);
        sphereShader->setMat4("projection", projection);
        sphereShader->setMat4("view", view);
        
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_CUBE_MAP,irradianceMap);
        
        glm::mat4 model=glm::mat4(1.0f);
        
        for(unsigned int i=0;i<sizeof(lightPositions)/sizeof(lightPositions[0]);i++){
            glm::vec3 newPos=lightPositions[i]+glm::vec3(sin(glfwGetTime()*5.0f)*5.0f,0.0f,0.0f);
            newPos=lightPositions[i];
            sphereShader->setVec3("lightPositions["+std::to_string(i)+"]", newPos);
            sphereShader->setVec3("lightColors["+std::to_string(i)+"]", lightColors[i]);
            model=glm::scale(glm::translate(glm::mat4(1.0f), newPos),glm::vec3(0.5f));
            sphereShader->setMat4("model", model);
            sphereShader->setMat3("normalMatrix",glm::transpose(glm::inverse(glm::mat3(model))));
            sphere->render();
        }
        
        for(int row=0;row<nrRows;row++){
            sphereShader->setFloat("metallic", (float)row/(float)nrRows);
            for(int col=0;col<nrColumns;col++){
                sphereShader->setFloat("roughness", glm::clamp((float)col/(float)nrColumns, 0.05f, 1.0f));
                model=glm::mat4(1.0f);
                model=glm::translate(model, glm::vec3((col-(nrColumns/2))*spacing,(row-(nrRows/2))*spacing,0.0f));
                sphereShader->setMat4("model", model);
                sphereShader->setMat3("normalMatrix", glm::transpose(glm::inverse(glm::mat3(model))));
                sphere->render();
            }
        }
        
        glfwSwapBuffers(window);
        glfwPollEvents();
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
