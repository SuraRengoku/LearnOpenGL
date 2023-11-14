//
//  specularibl.cpp
//  OpenGLdemo
//
//  Created by SHERLOCK on 31.10.23.
//

#include "specularibl.hpp"
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

static bool hdr_=true;
static bool hdrKeyPressed=false;
static bool Reinhard=true;
static bool ReinhardPressed=false;
static bool bloom_=true;
static bool bloomPressed=false;
static float exposure=1.0f;

int specularibl(){
    GLFWwindow* window=glfw_Init(SCR_WIDTH,SCR_HEIGHT, mouse_callback,scroll_callback);
    
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);//立方体贴图面之间的过滤，消除低分辨率下的接缝感
    
    CubeRender* cube=new CubeRender();
    QuadRender* quad=new QuadRender();
    SphereRender* sphere=new SphereRender(64);
    
    GLuint hdrMap=loadTextureHDR("/Users/sherlock/Documents/Code/OpenGLdemo/OpenGLdemo/resource/newport_loft.hdr");
    
    Shader* toCubeMap=new Shader("/Users/sherlock/Documents/Code/OpenGLdemo/OpenGLdemo/PBR/DiffuseIrradiance/toCubeMap.vs","/Users/sherlock/Documents/Code/OpenGLdemo/OpenGLdemo/PBR/DiffuseIrradiance/toCubeMap.fs");
    
    Shader* cubeMap=new Shader("/Users/sherlock/Documents/Code/OpenGLdemo/OpenGLdemo/PBR/DiffuseIrradiance/cubemaps.vs","/Users/sherlock/Documents/Code/OpenGLdemo/OpenGLdemo/PBR/DiffuseIrradiance/cubemaps.fs");
    cubeMap->use();
    cubeMap->setInt("environmentMap", 0);
    
    Shader* prefilterShader=new Shader("/Users/sherlock/Documents/Code/OpenGLdemo/OpenGLdemo/PBR/DiffuseIrradiance/cubemaps.vs","/Users/sherlock/Documents/Code/OpenGLdemo/OpenGLdemo/PBR/SpecularIBL/prefilter.fs");
    
    Shader* BRDFshader=new Shader("/Users/sherlock/Documents/Code/OpenGLdemo/OpenGLdemo/PBR/SpecularIBL/BRDF.vs","/Users/sherlock/Documents/Code/OpenGLdemo/OpenGLdemo/PBR/SpecularIBL/BRDF.fs");
    
    Shader* pbrShader=new Shader("/Users/sherlock/Documents/Code/OpenGLdemo/OpenGLdemo/PBR/SpecularIBL/pbr.vs","/Users/sherlock/Documents/Code/OpenGLdemo/OpenGLdemo/PBR/SpecularIBL/pbr.fs");
    pbrShader->use();
    pbrShader->setInt("irradianceMap", 0);
    pbrShader->setInt("prefilterMap", 1);
    pbrShader->setInt("brdfLUT", 2);
    pbrShader->setVec3("albedo", 0.5f, 0.0f, 0.0f);
    pbrShader->setFloat("ao", 1.0f);
    
    Shader* irradiance=new Shader("/Users/sherlock/Documents/Code/OpenGLdemo/OpenGLdemo/PBR/DiffuseIrradiance/cubemaps.vs","/Users/sherlock/Documents/Code/OpenGLdemo/OpenGLdemo/PBR/DiffuseIrradiance/irradianceMap.fs");
    
    //lights
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
    int nrRows=7;
    int nrColumns=7;
    float spacing=2.5;
    
    //将等距柱状投影图转换成立方体贴图
    unsigned int captureFBO,captureRBO,envCubemap;
    glGenFramebuffers(1,&captureFBO);
    glGenRenderbuffers(1,&captureRBO);
    glGenTextures(1,&envCubemap);
    glBindFramebuffer(GL_FRAMEBUFFER,captureFBO);
    glBindRenderbuffer(GL_RENDERBUFFER,captureRBO);
    glRenderbufferStorage(GL_RENDERBUFFER,GL_DEPTH_COMPONENT24,512,512);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER,GL_DEPTH_ATTACHMENT,GL_RENDERBUFFER,captureRBO);
    glBindTexture(GL_TEXTURE_CUBE_MAP,envCubemap);
    for(unsigned int i=0;i<6;i++)
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X+i,0,GL_RGB16F,512,512,0,GL_RGB,GL_FLOAT,nullptr);
    glTexParameteri(GL_TEXTURE_CUBE_MAP,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP,GL_TEXTURE_WRAP_R,GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);
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
    
    toCubeMap->use();
    toCubeMap->setInt("equirectangularMap", 0);
    toCubeMap->setMat4("projection", captureProjection);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D,hdrMap);
    
    glViewport(0,0,512,512);
    glBindFramebuffer(GL_FRAMEBUFFER,captureFBO);
    for(unsigned int i=0;i<6;i++){
        toCubeMap->setMat4("view", captureViews[i]);
        glFramebufferTexture2D(GL_FRAMEBUFFER,GL_COLOR_ATTACHMENT0,GL_TEXTURE_CUBE_MAP_POSITIVE_X+i,envCubemap,0);
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
        cube->render();
    }
    glBindTexture(GL_TEXTURE_CUBE_MAP,envCubemap);
    glGenerateMipmap(GL_TEXTURE_CUBE_MAP);
    glBindFramebuffer(GL_FRAMEBUFFER,0);//envCubemap里目前存储有天空盒
    
    unsigned int irradianceMap;
    glGenTextures(1,&irradianceMap);
    glBindTexture(GL_TEXTURE_CUBE_MAP,irradianceMap);
    for(unsigned int i=0;i<6;i++)
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X+i,0,GL_RGB16F,32,32,0,GL_RGB,GL_FLOAT,nullptr);
    glTexParameteri(GL_TEXTURE_CUBE_MAP,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP,GL_TEXTURE_WRAP_R,GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

    glBindFramebuffer(GL_FRAMEBUFFER, captureFBO);
    glBindRenderbuffer(GL_RENDERBUFFER, captureRBO);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, 32, 32);
    
    irradiance->use();
    irradiance->setInt("environmentMap", 0);
    irradiance->setMat4("projection", captureProjection);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP,envCubemap);
    
    glViewport(0,0,32,32);
    glBindFramebuffer(GL_FRAMEBUFFER,captureFBO);
    for(unsigned int i=0;i<6;i++){
        irradiance->setMat4("view", captureViews[i]);
        glFramebufferTexture2D(GL_FRAMEBUFFER,GL_COLOR_ATTACHMENT0,GL_TEXTURE_CUBE_MAP_POSITIVE_X+i,irradianceMap,0);
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
        cube->render();
    }
    glBindFramebuffer(GL_FRAMEBUFFER,0);
    
    //生成预过滤环境贴图
    unsigned int prefilterMap;
    glGenTextures(1,&prefilterMap);
    glBindTexture(GL_TEXTURE_CUBE_MAP,prefilterMap);
    for(unsigned int i=0;i<6;i++)
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X+i,0,GL_RGB16F,512,512,0,GL_RGB,GL_FLOAT,nullptr);
    glTexParameteri(GL_TEXTURE_CUBE_MAP,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP,GL_TEXTURE_WRAP_R,GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);
    //设置为GL_LINEAR_MIPMAP_LINEAR实现三线形过滤
    glTexParameteri(GL_TEXTURE_CUBE_MAP,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glGenerateMipmap(GL_TEXTURE_CUBE_MAP);

    prefilterShader->use();
    prefilterShader->setInt("environmentMap", 0);
    prefilterShader->setMat4("projection", captureProjection);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP,envCubemap);

    glBindFramebuffer(GL_FRAMEBUFFER,captureFBO);
    unsigned int maxMipLevels=7;
    for(unsigned int mip=0;mip<maxMipLevels;mip++){
        unsigned int mipWidth=512*std::pow(0.5f,mip);
        unsigned int mipHeight=512*std::pow(0.5f,mip);//生成mipmap大小
        glBindRenderbuffer(GL_RENDERBUFFER,captureRBO);
        glRenderbufferStorage(GL_RENDERBUFFER,GL_DEPTH_COMPONENT24,mipWidth,mipHeight);
        glViewport(0,0,mipWidth,mipHeight);

        float roughness=(float)mip/(float)(maxMipLevels-1);
        prefilterShader->setFloat("roughness", roughness);
        for(unsigned int i=0;i<6;i++){
            prefilterShader->setMat4("view", captureViews[i]);
            glFramebufferTexture2D(GL_FRAMEBUFFER,GL_COLOR_ATTACHMENT0,GL_TEXTURE_CUBE_MAP_POSITIVE_X+i,prefilterMap,mip);
            glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
            cube->render();
        }
    }
    glBindFramebuffer(GL_FRAMEBUFFER,0);//prefilterMap目前存储有预过滤环境贴图
    
    unsigned int brdfLUTTexture;
    glGenTextures(1,&brdfLUTTexture);
    glBindTexture(GL_TEXTURE_2D,brdfLUTTexture);
    glTexImage2D(GL_TEXTURE_2D,0,GL_RG16F,512,512,0,GL_RG,GL_FLOAT,0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    glBindFramebuffer(GL_FRAMEBUFFER,captureFBO);
    glBindRenderbuffer(GL_RENDERBUFFER,captureRBO);
    glRenderbufferStorage(GL_RENDERBUFFER,GL_DEPTH_COMPONENT24,512,512);
    glFramebufferTexture2D(GL_FRAMEBUFFER,GL_COLOR_ATTACHMENT0,GL_TEXTURE_2D,brdfLUTTexture,0);
    
    glViewport(0,0,512,512);
    BRDFshader->use();
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    quad->render();
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
        glm::mat4 view=camera.GetViewMatrix();
        
        //天空盒
        cubeMap->use();
        cubeMap->setMat4("projection", projection);
        cubeMap->setMat4("view", view);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_CUBE_MAP,prefilterMap);
        cube->render();
        
        pbrShader->use();
        pbrShader->setMat4("projection", projection);
        pbrShader->setMat4("view", view);
        pbrShader->setVec3("camPos", camera.Position);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_CUBE_MAP,irradianceMap);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_CUBE_MAP,prefilterMap);
        glActiveTexture(GL_TEXTURE2);
        glBindTexture(GL_TEXTURE_2D,brdfLUTTexture);
        
        glm::mat4 model=glm::mat4(1.0f);
        for(int row=0;row<nrRows;row++){
            pbrShader->setFloat("metallic", (float)row/(float)nrRows);
            for(int col=0;col<nrColumns;col++){
                pbrShader->setFloat("roughness", glm::clamp((float)col/(float)nrColumns, 0.05f, 1.0f));
                model=glm::mat4(1.0f);
                model=glm::translate(model, glm::vec3((float)(col-(nrColumns/2))*spacing,(float)(row-(nrRows/2))*spacing,-2.0f));
                pbrShader->setMat4("model", model);
                pbrShader->setMat3("normalMatrix", glm::transpose(glm::inverse(glm::mat3(model))));
                sphere->render();
            }
        }
        
        //光源
        for(unsigned int i=0;i<sizeof(lightPositions)/sizeof(lightPositions[0]);i++){
            glm::vec3 newPos=lightPositions[i]+glm::vec3(sin(glfwGetTime()*5.0f)*5.0f,0.0f,0.0f);
            newPos=lightPositions[i];
            pbrShader->setVec3("lightPositions["+std::to_string(i)+"]", newPos);
            pbrShader->setVec3("lightColors["+std::to_string(i)+"]", lightColors[i]);
            model=glm::scale(glm::translate(glm::mat4(1.0f),newPos), glm::vec3(0.5f));
            pbrShader->setMat4("model", model);
            pbrShader->setMat4("normalMatrix", glm::transpose(glm::inverse(glm::mat3(model))));
            sphere->render();
        }
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    delete toCubeMap;
    toCubeMap=nullptr;
    delete cubeMap;
    cubeMap=nullptr;
    delete prefilterShader;
    prefilterShader=nullptr;
    
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

