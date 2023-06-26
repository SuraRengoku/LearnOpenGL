//
//  execise1.cpp
//  OpenGLdemo
//
//  Created by SHERLOCK on 26.06.23.
//
#define STB_IMAGE_IMPLEMENTATION
#include "movelight.hpp"

void mouse_callback(GLFWwindow* window, double xposIn, double yposIn);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

const unsigned int SCR_WIDTH=1200;
const unsigned int SCR_HEIGHT=800;

static GLfloat vertices[]={
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
     0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,

    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
     0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
};

Camera camera(glm::vec3(0.0f,0.0f,6.0f));
bool firstMouse=true;
float lastX=SCR_WIDTH/2.0f;
float lastY=SCR_HEIGHT/2.0f;

static float deltaTime=0.0f;
static float lastTime=0.0f;

//glm::vec3 lightPos(1.2f,1.0f,2.0f);

int movelight(){
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT,GL_TRUE);
//    const char* glsl_version="#version 330 core";
#endif

    GLFWwindow *window=glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "learnOpenGL", NULL, NULL);
    if(window==nullptr){
        cout<<"fail to load GLFW window\n";
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        cout<<"fail to initialize GLAD\n";
        glfwTerminate();
        return -1;
    }

    glEnable(GL_DEPTH_TEST);

    Shader *objshader=new Shader("/Users/sherlock/Documents/Code/OpenGLdemo/OpenGLdemo/Lighting/BasicLighting/basiclighting.vs","/Users/sherlock/Documents/Code/OpenGLdemo/OpenGLdemo/Lighting/BasicLighting/basicobject.fs");
    Shader *lightshader=new Shader("/Users/sherlock/Documents/Code/OpenGLdemo/OpenGLdemo/Lighting/BasicLighting/basiclighting.vs","/Users/sherlock/Documents/Code/OpenGLdemo/OpenGLdemo/Lighting/BasicLighting/basiclight.fs");

    unsigned VBO,objVAO,lightVAO;
    glGenBuffers(1,&VBO);
    glGenVertexArrays(1,&objVAO);
    glGenVertexArrays(1,&lightVAO);

    glBindVertexArray(objVAO);
    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,6*sizeof(GL_FLOAT),(void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,6*sizeof(GL_FLOAT),(void*)(3*sizeof(GL_FLOAT)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(lightVAO);
    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,6*sizeof(GL_FLOAT),(void*)0);
    glEnableVertexAttribArray(0);

    while(!glfwWindowShouldClose(window)){
        float currentTime=static_cast<float>(glfwGetTime());
        deltaTime=currentTime-lastTime;//计算帧间时
        lastTime=currentTime;

        processInput(window);
        processCameraWSAD(window, camera, deltaTime);
        glClearColor(0.1f,0.1f,0.1f,1.0f);
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

        glm::mat4 projection=glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH/(float)SCR_HEIGHT, 0.1f, 100.0f);
        
        float x=cos(sin(currentTime)*2);
        float y=sin(sin(currentTime)*2);
        float z=cos(currentTime)*2;
        glm::vec3 lightPos=glm::vec3(x,y,z);
        
        
        lightshader->use();
        lightshader->setMat4("projection", projection);
        glm::mat4 view=camera.GetViewMatrix();
        lightshader->setMat4("view", view);
        glm::mat4 lightmodel=glm::mat4(1.0f);
        lightmodel=glm::scale(glm::translate(lightmodel, lightPos),glm::vec3(0.2f));
        lightshader->setMat4("model", lightmodel);
        glBindVertexArray(lightVAO);
        glDrawArrays(GL_TRIANGLES,0,36);
        
        
        objshader->use();
        objshader->setVec3("lightPos", lightPos);
        objshader->setVec3("viewPos", camera.Position);
        objshader->setMat4("projection", projection);
        objshader->setVec3("objectColor", 1.0f, 0.5f, 0.31f);
        objshader->setVec3("lightColor", 1.0f, 1.0f, 1.0f);
        objshader->setMat4("view", view);
        glm::mat4 objmodel=glm::mat4(1.0f);
        objshader->setMat4("model", objmodel);
        glm::mat4 normalMatrix=glm::mat3(glm::transpose(glm::inverse(objmodel)));
        objshader->setMat3("normalMatrix", normalMatrix);
        glBindVertexArray(objVAO);
        glDrawArrays(GL_TRIANGLES,0,36);
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    delete lightshader;
    delete objshader;
    glDeleteBuffers(1,&VBO);
    glDeleteVertexArrays(1,&objVAO);
    glDeleteVertexArrays(1,&lightVAO);

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
    lastX=xpos;
    lastY=ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset){
    camera.ProcessMouseScroll(yoffset);
}
