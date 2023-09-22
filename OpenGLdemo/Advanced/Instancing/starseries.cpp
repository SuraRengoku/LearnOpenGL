//
//  starseries.cpp
//  OpenGLdemo
//
//  Created by SHERLOCK on 22.09.23.
//

#include "starseries.hpp"
#define Default_Width 1200;
#define Default_Height 800;

static unsigned const int SCR_WIDTH=Default_Width;
static unsigned const int SCR_HEIGHT=Default_Height;

Camera camera(glm::vec3(0.0f,0.0f,155.0f));
bool firstMouse=true;
float lastX=SCR_WIDTH/2.0f;
float lastY=SCR_HEIGHT/2.0f;

static float deltaTime=0.0f;
static float lastTime=0.0f;

void mouse_callback(GLFWwindow* window, double xposIn, double yposIn);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

int starseries(){
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
    
    Shader *shader=new Shader("/Users/sherlock/Documents/Code/OpenGLdemo/OpenGLdemo/Advanced/Instancing/starseries.vs","/Users/sherlock/Documents/Code/OpenGLdemo/OpenGLdemo/Advanced/Instancing/starseries.fs");
        
    Model *planet=new Model("/Users/sherlock/Documents/Code/OpenGLdemo/OpenGLdemo/resource/models/planet/planet.obj");
    Model *rock=new Model("/Users/sherlock/Documents/Code/OpenGLdemo/OpenGLdemo/resource/models/rock/rock.obj");
    
    unsigned int amount=100000;
    glm::mat4 *modelMatrices;
    modelMatrices=new glm::mat4[amount];
    srand(glfwGetTime());//初始化随机种子
    float radius=150.0f;
    float offset=25.0f;
    for(unsigned int i=0;i<amount;i++){
        glm::mat4 model(1.0f);
        float angle=(float)i/(float)amount*360.0f;
        //偏移范围[-offset,offset]
        float displacement=(rand()%(int)(2*offset*100))/100.0f-offset;
        float x=sin(angle)*radius+displacement;
        displacement=(rand()%(int)(2*offset*100))/100.0f-offset;
        float y=displacement*0.4f;//y偏移量较小，形成较扁的行星带
        displacement=(rand()%(int)(2*offset*100))/100.0f-offset;
        float z=cos(angle)*radius+displacement;
        model=glm::translate(model, glm::vec3(x,y,z));
        
        //缩放，[0.05,0.25]
        float scale=(rand()%20)/100.0f+0.05f;
        model=glm::scale(model, glm::vec3(scale));
        
        //旋转
        float rotAngle=(rand()%360);
        model=glm::rotate(model, rotAngle, glm::vec3(0.4f,0.6f,0.8f));
        
        modelMatrices[i]=model;
    }
    
    Shader *instanceshader=new Shader("/Users/sherlock/Documents/Code/OpenGLdemo/OpenGLdemo/Advanced/Instancing/starseries2.vs","/Users/sherlock/Documents/Code/OpenGLdemo/OpenGLdemo/Advanced/Instancing/starseries.fs");

    unsigned int buffer;
    glGenBuffers(1,&buffer);
    glBindBuffer(GL_ARRAY_BUFFER,buffer);
    glBufferData(GL_ARRAY_BUFFER,amount*sizeof(glm::mat4),&modelMatrices[0],GL_STATIC_DRAW);
    
    
    for(unsigned int i=0;i<rock->meshes.size();i++){
        unsigned int VAO=rock->meshes[i].VAO;
        glBindVertexArray(VAO);
        
        //顶点属性
        //顶点属性最大允许的数据大小等于一个vec4,mat4本质上是4个vec4
        //instanceMatrix位置是3，因此矩阵的每一列位置为3,4,5,6
        glEnableVertexAttribArray(3);
        glVertexAttribPointer(3,4,GL_FLOAT,GL_FALSE,sizeof(glm::mat4),(void*)0);
        glEnableVertexAttribArray(4);
        glVertexAttribPointer(4,4,GL_FLOAT,GL_FALSE,sizeof(glm::mat4),(void*)(sizeof(glm::vec4)));
        glEnableVertexAttribArray(5);
        glVertexAttribPointer(5,4,GL_FLOAT,GL_FALSE,sizeof(glm::mat4),(void*)(2*sizeof(glm::vec4)));
        glEnableVertexAttribArray(6);
        glVertexAttribPointer(6,4,GL_FLOAT,GL_FALSE,sizeof(glm::mat4),(void*)(3*sizeof(glm::vec4)));

        glVertexAttribDivisor(3,1);
        glVertexAttribDivisor(4,1);
        glVertexAttribDivisor(5,1);
        glVertexAttribDivisor(6,1);

        glBindVertexArray(0);
    }
    
    
    while(!glfwWindowShouldClose(window)){
        float currentTime=static_cast<float>(glfwGetTime());
        deltaTime=(currentTime-lastTime);
        lastTime=currentTime;

        processInput(window, mouse_callback, scroll_callback);
        processCameraWSAD(window, camera, deltaTime);
        
        glClearColor(0.1f,0.1f,0.1f,1.0f);
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

        glm::mat4 projection=glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH/(float)SCR_HEIGHT, 0.1f, 1000.0f);
        glm::mat4 view=camera.GetViewMatrix();
        glm::mat4 model=glm::scale(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f,-3.0f,0.0f)),glm::vec3(4.0f,4.0f,4.0f));

        
        shader->use();
        shader->setMat4("projection", projection);
        shader->setMat4("view", view);
        shader->setMat4("model", model);
        
        planet->Draw(*shader);
        
        instanceshader->use();
        instanceshader->setMat4("projection", projection);
        instanceshader->setMat4("view", view);
        
//        for(unsigned int i=0;i<amount;i++){
//            shader->setMat4("model", modelMatrices[i]);
//            rock->Draw(*shader);
//        }//未实例化
        instanceshader->setInt("texture_diffuse1", 0);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D,rock->textures_loaded[0].id);
        for(unsigned int i=0;i<rock->meshes.size();i++){
            glBindVertexArray(rock->meshes[i].VAO);
            glDrawElementsInstanced(GL_TRIANGLES,static_cast<unsigned int>(rock->meshes[i].indices.size()),GL_UNSIGNED_INT,0,amount);
            glBindVertexArray(0);
        }
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    delete shader;
    shader=nullptr;
    delete rock;
    rock=nullptr;
    delete planet;
    planet=nullptr;
    
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
