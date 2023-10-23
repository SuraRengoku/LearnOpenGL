//
//  ssao.cpp
//  OpenGLdemo
//
//  Created by SHERLOCK on 20.10.23.
//

#include "ssao.hpp"
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

int ssao(){
    GLFWwindow* window=glfw_Init(SCR_WIDTH, SCR_HEIGHT, mouse_callback, scroll_callback);

    glEnable(GL_DEPTH_TEST);
    
    Shader* debugshader=new Shader("/Users/sherlock/Documents/Code/OpenGLdemo/OpenGLdemo/AdvancedLighting/SSAO/common.vs","/Users/sherlock/Documents/Code/OpenGLdemo/OpenGLdemo/AdvancedLighting/DeferredShading/debug.fs");
    Shader* shaderGeometryPass=new Shader("/Users/sherlock/Documents/Code/OpenGLdemo/OpenGLdemo/AdvancedLighting/SSAO/gBuffershader.vs", "/Users/sherlock/Documents/Code/OpenGLdemo/OpenGLdemo/AdvancedLighting/SSAO/gBuffershader.fs");
    Shader* shaderLightingPass=new Shader("/Users/sherlock/Documents/Code/OpenGLdemo/OpenGLdemo/AdvancedLighting/SSAO/common.vs", "/Users/sherlock/Documents/Code/OpenGLdemo/OpenGLdemo/AdvancedLighting/SSAO/lighting.fs");
    Shader* shaderSSAO=new Shader("/Users/sherlock/Documents/Code/OpenGLdemo/OpenGLdemo/AdvancedLighting/SSAO/common.vs", "/Users/sherlock/Documents/Code/OpenGLdemo/OpenGLdemo/AdvancedLighting/SSAO/ssaoshader.fs");
    Shader* shaderSSAOBlur=new Shader("/Users/sherlock/Documents/Code/OpenGLdemo/OpenGLdemo/AdvancedLighting/SSAO/common.vs", "/Users/sherlock/Documents/Code/OpenGLdemo/OpenGLdemo/AdvancedLighting/SSAO/blur.fs");
    
    Model* nanosuit=new Model("/Users/sherlock/Documents/Code/OpenGLdemo/OpenGLdemo/resource/models/nanosuit/nanosuit.obj");

    unsigned int gBuffer;
    glGenFramebuffers(1,&gBuffer);
    glBindFramebuffer(GL_FRAMEBUFFER,gBuffer);
    unsigned int gPositionDepth,gNormal,gAlbedoSpec;
    //position and depth value(in the view space)
    glGenTextures(1,&gPositionDepth);
    glBindTexture(GL_TEXTURE_2D,gPositionDepth);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, SCR_WIDTH*2, SCR_HEIGHT*2, 0, GL_RGBA, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    // 保证不会采样到屏幕空间中纹理默认坐标区域之外的深度值
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glFramebufferTexture2D(GL_FRAMEBUFFER,GL_COLOR_ATTACHMENT0,GL_TEXTURE_2D,gPositionDepth,0);
    //normal
    glGenTextures(1, &gNormal);
    glBindTexture(GL_TEXTURE_2D, gNormal);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, SCR_WIDTH*2, SCR_HEIGHT*2, 0, GL_RGB, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, gNormal, 0);
    //ambient
    glGenTextures(1, &gAlbedoSpec);
    glBindTexture(GL_TEXTURE_2D, gAlbedoSpec);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, SCR_WIDTH*2, SCR_HEIGHT*2, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT2, GL_TEXTURE_2D, gAlbedoSpec, 0);
    //rbo非常重要‼️
    unsigned int rboDepth;
    glGenRenderbuffers(1, &rboDepth);
    glBindRenderbuffer(GL_RENDERBUFFER, rboDepth);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, SCR_WIDTH*2, SCR_HEIGHT*2);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, rboDepth);
    //rbo非常重要‼️
    unsigned int attachments[3]={GL_COLOR_ATTACHMENT0,GL_COLOR_ATTACHMENT1,GL_COLOR_ATTACHMENT2};
    glDrawBuffers(3,attachments);
    try{
        if(glCheckFramebufferStatus(GL_FRAMEBUFFER)!=GL_FRAMEBUFFER_COMPLETE)
            throw std::runtime_error("ERROR::FRAMEBUFFER::Framebuffer is not complete!");
    }catch(const std::runtime_error &err){
        cerr<<err.what()<<"\n";
        throw;
    }
    
    //加速差值函数
    auto lerp=[](GLfloat a,GLfloat b,GLfloat c)->GLfloat{
        return a+c*(b-a);
    };//尽可能将所有采样点向真正需要采样的片段靠拢

    //法向半球
    std::uniform_real_distribution<GLfloat> randomFloats(0.0f,1.0f);//随机浮点数[0.0f,1.0f]
    std::default_random_engine generator;
    std::vector<glm::vec3> ssaoKernel;
    for(GLuint i=0;i<64;++i){
        glm::vec3 sample(randomFloats(generator)*2.0f-1.0f,
                         randomFloats(generator)*2.0f-1.0f,
                         randomFloats(generator));//z轴方向范围[0.0f,1.0f];
        sample=glm::normalize(sample);
        sample*=randomFloats(generator);
        GLfloat scale=GLfloat(i)/64.0f;
        sample*=lerp(0.1f, 1.0f, scale*scale);
        ssaoKernel.push_back(sample);
    }//最大64个样本值的采样核心
    
    //随机核心旋转
    std::vector<glm::vec3> ssaoNoise;
    for(GLuint i=0;i<16;i++){
        glm::vec3 noise(randomFloats(generator)*2.0f-1.0f,
                        randomFloats(generator)*2.0f-1.0f,
                        0.0f);
        ssaoNoise.push_back(noise);
    }//沿着切线空间的z轴随机旋转

    //创建一个包换旋转向量的4x4纹理，采用REPEAT方式平铺在几何体上
    GLuint noiseTexture;
    glGenTextures(1,&noiseTexture);
    glBindTexture(GL_TEXTURE_2D,noiseTexture);
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGB16F,4,4,0,GL_RGB,GL_FLOAT,&ssaoNoise[0]);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);

    GLuint ssaoFBO,ssaoColorBuffer;
    glGenFramebuffers(1,&ssaoFBO);
    glBindFramebuffer(GL_FRAMEBUFFER,ssaoFBO);
    glGenTextures(1,&ssaoColorBuffer);
    glBindTexture(GL_TEXTURE_2D,ssaoColorBuffer);
    glTexImage2D(GL_TEXTURE_2D,0,GL_RED,SCR_WIDTH*2,SCR_HEIGHT*2,0,GL_RGB,GL_FLOAT,NULL);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glFramebufferTexture2D(GL_FRAMEBUFFER,GL_COLOR_ATTACHMENT0,GL_TEXTURE_2D,ssaoColorBuffer,0);
    try{
        if(glCheckFramebufferStatus(GL_FRAMEBUFFER)!=GL_FRAMEBUFFER_COMPLETE)
            throw std::runtime_error("ERROR::FRAMEBUFFER::Framebuffer is not complete!");
    }catch(const std::runtime_error &err){
        cerr<<err.what()<<"\n";
        throw;
    }

    GLuint ssaoBlurFBO,ssaoBlurColorBuffer;
    glGenFramebuffers(1,&ssaoBlurFBO);
    glBindFramebuffer(GL_FRAMEBUFFER,ssaoBlurFBO);
    glGenTextures(1,&ssaoBlurColorBuffer);
    glBindTexture(GL_TEXTURE_2D,ssaoBlurColorBuffer);
    glTexImage2D(GL_TEXTURE_2D,0,GL_RED,SCR_WIDTH*2,SCR_HEIGHT*2,0,GL_RGB,GL_FLOAT,NULL);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glFramebufferTexture2D(GL_FRAMEBUFFER,GL_COLOR_ATTACHMENT0,GL_TEXTURE_2D,ssaoBlurColorBuffer,0);
    try{
        if(glCheckFramebufferStatus(GL_FRAMEBUFFER)!=GL_FRAMEBUFFER_COMPLETE)
            throw std::runtime_error("ERROR::FRAMEBUFFER::Framebuffer is not complete!");
    }catch(const std::runtime_error &err){
        cerr<<err.what()<<"\n";
        throw;
    }
    
    glm::vec3 lightPos = glm::vec3(2.0, 4.0, -2.0);
    glm::vec3 lightColor = glm::vec3(1.0, 1.0, 1.0);

    
    shaderGeometryPass->use();
    shaderGeometryPass->setInt("texture_diffuse1", 0);
    shaderGeometryPass->setInt("texture_specular1", 1);
    shaderLightingPass->use();
    shaderLightingPass->setInt("gPosition", 0);
    shaderLightingPass->setInt("gNormal", 1);
    shaderLightingPass->setInt("gAlbedoSpec", 2);
    shaderLightingPass->setInt("ssao", 3);
    shaderSSAO->use();
    shaderSSAO->setInt("gPosition", 0);
    shaderSSAO->setInt("gNormal", 1);
    shaderSSAO->setInt("texNoise", 2);
    shaderSSAOBlur->use();
    shaderSSAOBlur->setInt("ssaoInput", 0);
    
    CubeRender* cube=new CubeRender;
    QuadRender* quad=new QuadRender;

    while (!glfwWindowShouldClose(window)){
        float currentTime = static_cast<float>(glfwGetTime());
        deltaTime = currentTime - lastTime;
        lastTime = currentTime;

        processInput(window,mouse_callback,scroll_callback);
        processCameraWSAD(window, camera, deltaTime);

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        glEnable(GL_DEPTH_TEST);
        
        glBindFramebuffer(GL_FRAMEBUFFER, gBuffer);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 50.0f);
        glm::mat4 view = camera.GetViewMatrix();
        glm::mat4 model = glm::mat4(1.0f);
        shaderGeometryPass->use();
        shaderGeometryPass->setMat4("projection", projection);
        shaderGeometryPass->setMat4("view", view);
            // room cube
        model = glm::mat4(1.0f);
        model=glm::scale(glm::translate(model, glm::vec3(0.0f,-2.0f,0.0f)),glm::vec3(20.0f,1.0f,20.0f));
        shaderGeometryPass->setMat4("model", model);
        shaderGeometryPass->setMat3("normalMatrix", glm::transpose(glm::inverse(glm::mat3(view*model))));
        shaderGeometryPass->setInt("invertedNormals", 0); // invert normals as we're inside the cube
        shaderGeometryPass->setInt("suit", 0);
        cube->render();
        shaderGeometryPass->setInt("invertedNormals", 0);
        shaderGeometryPass->setInt("suit", 1);
            // backpack model on the floor
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 0.5f, 0.0));
        model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0, 0.0, 0.0));
        model = glm::scale(model, glm::vec3(1.0f));
        shaderGeometryPass->setMat4("model", model);
        shaderGeometryPass->setMat3("normalMatrix", glm::transpose(glm::inverse(glm::mat3(view*model))));
        nanosuit->Draw(*shaderGeometryPass);

        glBindFramebuffer(GL_FRAMEBUFFER, ssaoFBO);
        glClear(GL_COLOR_BUFFER_BIT);
        shaderSSAO->use();
        for (unsigned int i = 0; i < 64; ++i)
            shaderSSAO->setVec3("samples[" + std::to_string(i) + "]", ssaoKernel[i]);
        shaderSSAO->setMat4("projection", projection);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, gPositionDepth);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, gNormal);
        glActiveTexture(GL_TEXTURE2);
        glBindTexture(GL_TEXTURE_2D, noiseTexture);
        quad->render();
        
        glBindFramebuffer(GL_FRAMEBUFFER, ssaoBlurFBO);
        glClear(GL_COLOR_BUFFER_BIT);
        shaderSSAOBlur->use();
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, ssaoColorBuffer);
        quad->render();
        
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        shaderLightingPass->use();
        shaderLightingPass->setVec3("viewPos",camera.Position);
        shaderLightingPass->setVec3("light.Position", lightPos);
        shaderLightingPass->setVec3("light.Color", lightColor);
        const float linear    = 0.09f;
        const float quadratic = 0.032f;
        shaderLightingPass->setFloat("light.Linear", linear);
        shaderLightingPass->setFloat("light.Quadratic", quadratic);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, gPositionDepth);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, gNormal);
        glActiveTexture(GL_TEXTURE2);
        glBindTexture(GL_TEXTURE_2D, gAlbedoSpec);
        glActiveTexture(GL_TEXTURE3);
        glBindTexture(GL_TEXTURE_2D, ssaoBlurColorBuffer);
        quad->render();
        
        //debug
        glDisable(GL_DEPTH_TEST);
        glBindFramebuffer(GL_FRAMEBUFFER,0);
        debugshader->use();
        glViewport(0,0,(SCR_WIDTH*2)/4,(SCR_HEIGHT*2)/4);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D,gPositionDepth);
        quad->render();
        glViewport(0,(SCR_HEIGHT*2)/4,(SCR_WIDTH*2)/4,(SCR_HEIGHT*2)/4);
        glBindTexture(GL_TEXTURE_2D,gNormal);
        quad->render();
        glViewport(0,(SCR_HEIGHT*2)/2,(SCR_WIDTH*2)/4,(SCR_HEIGHT*2)/4);
        glBindTexture(GL_TEXTURE_2D,gAlbedoSpec);
        quad->render();
        glViewport((SCR_WIDTH*2)/2,0,(SCR_WIDTH*2)/4,(SCR_HEIGHT*2)/4);
        glBindTexture(GL_TEXTURE_2D,noiseTexture);
        quad->render();
        glViewport((SCR_WIDTH*2)/4,(SCR_HEIGHT*2)/4,(SCR_WIDTH*2)/4,(SCR_HEIGHT*2)/4);
        glBindTexture(GL_TEXTURE_2D,ssaoBlurColorBuffer);
        quad->render();
        glViewport((SCR_WIDTH*2)/4,0,(SCR_WIDTH*2)/4,(SCR_HEIGHT*2)/4);
        glBindTexture(GL_TEXTURE_2D,ssaoColorBuffer);
        quad->render();

        glViewport(0,0,SCR_WIDTH*2,SCR_HEIGHT*2);
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    delete debugshader;
    debugshader=nullptr;
    delete shaderGeometryPass;
    shaderGeometryPass=nullptr;
    delete shaderLightingPass;
    shaderLightingPass=nullptr;
    delete shaderSSAO;
    shaderSSAO=nullptr;
    delete shaderSSAOBlur;
    shaderSSAOBlur=nullptr;
    
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
