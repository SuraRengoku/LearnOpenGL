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
    
    while (!glfwWindowShouldClose(window)) {
        <#statements#>
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

