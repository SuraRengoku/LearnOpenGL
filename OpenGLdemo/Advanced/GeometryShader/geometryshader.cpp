//
//  geometryshader.cpp
//  OpenGLdemo
//
//  Created by SHERLOCK on 20.09.23.
//

#include "geometryshader.hpp"
#define Default_Width 1200;
#define Default_Height 800;

static unsigned const int SCR_WIDTH=Default_Width;
static unsigned const int SCR_HEIGHT=Default_Height;

Camera camera(glm::vec3(0.0f,0.0f,6.0f));
bool firstMouse=true;
float lastX=SCR_WIDTH/2.0f;
float lastY=SCR_HEIGHT/2.0f;

static float deltaTime=0.0f;
static float lastTime=0.0f;

void mouse_callback(GLFWwindow* window, double xposIn, double yposIn);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

static float points[] = {
    -0.5f,  0.5f, 1.0f, 0.0f, 0.0f, // 左上
     0.5f,  0.5f, 0.0f, 1.0f, 0.0f, // 右上
     0.5f, -0.5f, 0.0f, 0.0f, 1.0f, // 右下
    -0.5f, -0.5f, 1.0f, 1.0f, 0.0f  // 左下
};

int geometryshader(){
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);//设置上下文主要版本号
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);//次要版本号
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
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
    
    Model *nanosuit=new Model("/Users/sherlock/Documents/Code/OpenGLdemo/OpenGLdemo/resource/models/nanosuit/nanosuit.obj");
    
    Shader *shader=new Shader("/Users/sherlock/Documents/Code/OpenGLdemo/OpenGLdemo/Advanced/GeometryShader/vertex1.vs","/Users/sherlock/Documents/Code/OpenGLdemo/OpenGLdemo/Advanced/GeometryShader/geometry1.gs","/Users/sherlock/Documents/Code/OpenGLdemo/OpenGLdemo/Advanced/GeometryShader/fragment1.fs");
    
    Shader *houseshader=new Shader("/Users/sherlock/Documents/Code/OpenGLdemo/OpenGLdemo/Advanced/GeometryShader/vertex1.vs","/Users/sherlock/Documents/Code/OpenGLdemo/OpenGLdemo/Advanced/GeometryShader/geometry2.gs","/Users/sherlock/Documents/Code/OpenGLdemo/OpenGLdemo/Advanced/GeometryShader/fragment1.fs");
    
    Shader *explodemodel=new Shader("/Users/sherlock/Documents/Code/OpenGLdemo/OpenGLdemo/Advanced/GeometryShader/Explodevertex.vs","/Users/sherlock/Documents/Code/OpenGLdemo/OpenGLdemo/Advanced/GeometryShader/Explodegeometry.gs","/Users/sherlock/Documents/Code/OpenGLdemo/OpenGLdemo/Advanced/GeometryShader/Explodefragment.fs");
    
    unsigned int uniformBlockIndex=glGetUniformBlockIndex(explodemodel->ID,"Matrices");
    glUniformBlockBinding(explodemodel->ID,uniformBlockIndex,0);
    unsigned int uboMatrices;
    glGenBuffers(1,&uboMatrices);
    glBindBuffer(GL_UNIFORM_BUFFER,uboMatrices);
    glBufferData(GL_UNIFORM_BUFFER,sizeof(glm::mat4),NULL,GL_STATIC_DRAW);
    glBindBuffer(GL_UNIFORM_BUFFER,0);
    glBindBufferRange(GL_UNIFORM_BUFFER,0,uboMatrices,0,sizeof(glm::mat4));
    
    unsigned int VAO,VBO;
    glGenVertexArrays(1,&VAO);
    glGenBuffers(1,&VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    glBufferData(GL_ARRAY_BUFFER,sizeof(points),&points,GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0,2,GL_FLOAT,GL_FALSE,5*sizeof(GL_FLOAT),(void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,5*sizeof(GL_FLOAT),(void*)(2*sizeof(GL_FLOAT)));
    
    float movevelocity=5.0f;
    
    while(!glfwWindowShouldClose(window)){
        float currentTime=static_cast<float>(glfwGetTime());
        deltaTime=(currentTime-lastTime)*movevelocity;
        lastTime=currentTime;

        processInput(window, mouse_callback, scroll_callback);
        processCameraWSAD(window, camera, deltaTime);
        
        glClearColor(0.1f,0.1f,0.1f,1.0f);
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
        
//        shader->use();
//        houseshader->use();
//        glBindVertexArray(VAO);
//        glDrawArrays(GL_POINTS,0,4);
        
        glm::mat4 projection=glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH/(float)SCR_HEIGHT, 0.1f,100.0f);
        glBindBuffer(GL_UNIFORM_BUFFER,uboMatrices);
        glBufferSubData(GL_UNIFORM_BUFFER,0,sizeof(glm::mat4),glm::value_ptr(projection));
        glBindBuffer(GL_UNIFORM_BUFFER,0);
        glm::mat4 view=camera.GetViewMatrix();
        glm::mat4 model=glm::mat4(1.0f);
        
        explodemodel->use();
        explodemodel->setMat4("view", view);
        explodemodel->setMat4("model", model);
        explodemodel->setFloat("time", static_cast<float>(glfwGetTime()));
        
        nanosuit->Draw(*explodemodel);
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    delete shader;
    shader=nullptr;
    glDeleteBuffers(1,&VBO);
    glDeleteVertexArrays(1,&VAO);
    
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
