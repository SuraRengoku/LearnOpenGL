//
//  instancing.cpp
//  OpenGLdemo
//
//  Created by SHERLOCK on 21.09.23.
//

#include "instancing.hpp"
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

static float quadVertices[] = {
    // 位置          // 颜色
    -0.05f,  0.05f,  1.0f, 0.0f, 0.0f,
     0.05f, -0.05f,  0.0f, 1.0f, 0.0f,
    -0.05f, -0.05f,  0.0f, 0.0f, 1.0f,

    -0.05f,  0.05f,  1.0f, 0.0f, 0.0f,
     0.05f, -0.05f,  0.0f, 1.0f, 0.0f,
     0.05f,  0.05f,  0.0f, 1.0f, 1.0f
};

int instancing(){
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
    
    Shader *quadshader=new Shader("/Users/sherlock/Documents/Code/OpenGLdemo/OpenGLdemo/Advanced/Instancing/quad.vs","/Users/sherlock/Documents/Code/OpenGLdemo/OpenGLdemo/Advanced/Instancing/quad.fs");
    
    Shader *quadshader2=new Shader("/Users/sherlock/Documents/Code/OpenGLdemo/OpenGLdemo/Advanced/Instancing/quad2.vs","/Users/sherlock/Documents/Code/OpenGLdemo/OpenGLdemo/Advanced/Instancing/quad.fs");
    
    glm::vec2 translations[100];//生成偏移数组
    int index=0;
    float offset=0.1f;
    for(int y=-10;y<10;y+=2){
        for(int x=-10;x<10;x+=2){
            glm::vec2 translation;
            translation.x=(float)x/10.0f+offset;
            translation.y=(float)y/10.0f+offset;
            translations[index++]=translation;
        }
    }
    
    unsigned int instanceVBO;
    glGenBuffers(1,&instanceVBO);
    glBindBuffer(GL_ARRAY_BUFFER,instanceVBO);
    glBufferData(GL_ARRAY_BUFFER,sizeof(glm::vec2)*100,&translations[0],GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER,0);
    
    quadshader->use();
    for(unsigned int i=0;i<100;i++){
        std::stringstream ss;
        string index;
        ss<<i;
        index=ss.str();
        quadshader->setVec2(("offsets["+index+"]").c_str(), translations[i]);
    }
    
    unsigned int quadVAO,quadVBO;
    glGenVertexArrays(1,&quadVAO);
    glGenBuffers(1,&quadVBO);
    glBindVertexArray(quadVAO);
    glBindBuffer(GL_ARRAY_BUFFER,quadVBO);
    glBufferData(GL_ARRAY_BUFFER,sizeof(quadVertices),&quadVertices,GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0,2,GL_FLOAT,GL_FALSE,5*sizeof(GL_FLOAT),(void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,5*sizeof(GL_FLOAT),(void*)(3*sizeof(GL_FLOAT)));
    
    glEnableVertexAttribArray(2);
    glBindBuffer(GL_ARRAY_BUFFER,instanceVBO);
    glVertexAttribPointer(2,2,GL_FLOAT,GL_FALSE,2*sizeof(GL_FLOAT),(void*)0);
    glBindBuffer(GL_ARRAY_BUFFER,0);
    //该函数告诉OpenGL什么时候该更新顶点属性的内容至新一组数据
    /**
     @param 顶点属性位置
     @param 属性除数  default-0 0-每次迭代更新 1-每渲染一个新实例时更新 2-每渲染两个新实例时更新
     */
    //处于位置值2的顶点属性是一个实例化数组，每渲染一个新实例时更新
    glVertexAttribDivisor(2,1);
    glBindVertexArray(0);
    
    while(!glfwWindowShouldClose(window)){
        float currentTime=static_cast<float>(glfwGetTime());
        deltaTime=(currentTime-lastTime);
        lastTime=currentTime;

        processInput(window, mouse_callback, scroll_callback);
        processCameraWSAD(window, camera, deltaTime);
        
        glClearColor(0.1f,0.1f,0.1f,1.0f);
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
        
        glBindVertexArray(quadVAO);
//        quadshader->use();
        quadshader2->use();
        //该渲染指令最后的参数表示需要绘制的实例数量
        glDrawArraysInstanced(GL_TRIANGLES,0,6,100);
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glDeleteVertexArrays(1,&quadVAO);
    glDeleteBuffers(1,&quadVBO);
    delete quadshader;
    quadshader=nullptr;
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
