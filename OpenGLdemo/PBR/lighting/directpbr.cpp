//
//  directpbr.cpp
//  OpenGLdemo
//
//  Created by SHERLOCK on 27.10.23.
//

#include "directpbr.hpp"
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

int directpbr(){
    GLFWwindow* window=glfw_Init(SCR_WIDTH, SCR_HEIGHT, mouse_callback, scroll_callback);
    
    glEnable(GL_DEPTH_TEST);
    
    Shader *directshader=new Shader("/Users/sherlock/Documents/Code/OpenGLdemo/OpenGLdemo/PBR/lighting/directpbr.vs","/Users/sherlock/Documents/Code/OpenGLdemo/OpenGLdemo/PBR/lighting/directpbr.fs");
    
    directshader->use();
    directshader->setVec3("albedo", 0.5f, 0.0f, 0.0f);
    directshader->setFloat("ao", 1.0f);
    
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
    float spacing=2.5f;
    SphereRender* sphere=new SphereRender(64);
    
    while (!glfwWindowShouldClose(window)) {
        float currentTime = static_cast<float>(glfwGetTime());
        deltaTime = currentTime - lastTime;
        lastTime = currentTime;

        processInput(window,mouse_callback,scroll_callback);
        processCameraWSAD(window, camera, deltaTime);

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glm::mat4 projection=glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH/(float)SCR_HEIGHT, 0.1f, 100.0f);
        glm::mat4 view=camera.GetViewMatrix();
        directshader->setMat4("projection", projection);
        directshader->setMat4("view", view);
        directshader->setVec3("camPos", camera.Position);
        
        glm::mat4 model=glm::mat4(1.0f);
        for(unsigned int i=0;i<sizeof(lightPositions)/sizeof(lightPositions[0]);i++){
            glm::vec3 newPos=lightPositions[i]+glm::vec3(sin(glfwGetTime()*5.0f)*5.0f,0.0f,0.0f);
            newPos=lightPositions[i];
            directshader->setVec3("lightPositions["+std::to_string(i)+"]", newPos);
            directshader->setVec3("lightColors["+std::to_string(i)+"]", lightColors[i]);
            model=glm::scale(glm::translate(glm::mat4(1.0f), newPos),glm::vec3(0.5f));
            directshader->setMat4("model", model);
            directshader->setMat3("normalMatrix",glm::transpose(glm::inverse(glm::mat3(model))));
            sphere->render();
        }
        
        for(int row=0;row<nrRows;row++){
            directshader->setFloat("metallic", (float)row/(float)nrRows);
            for(int col=0;col<nrColumns;col++){
                directshader->setFloat("roughness", glm::clamp((float)col/(float)nrColumns, 0.05f, 1.0f));
                model=glm::mat4(1.0f);
                model=glm::translate(model, glm::vec3((col-(nrColumns/2))*spacing,(row-(nrRows/2))*spacing,0.0f));
                directshader->setMat4("model", model);
                directshader->setMat3("normalMatrix", glm::transpose(glm::inverse(glm::mat3(model))));
                sphere->render();
            }
        }
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    delete directshader;
    directshader=nullptr;
    
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
