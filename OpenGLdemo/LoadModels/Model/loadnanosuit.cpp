//
//  loadnanosuit.cpp
//  OpenGLdemo
//
//  Created by SHERLOCK on 22.07.23.
//
#include "loadnanosuit.hpp"

static unsigned const int SCR_WIDTH=1200;
static unsigned const int SCR_HEIGHT=800;

void mouse_callback(GLFWwindow* window,double xposIn,double yposIn);
void scroll_callback(GLFWwindow* window,double xoffset,double yoffset);

Camera camera(glm::vec3(0.0f,10.0f,20.0f));
bool firstMouse=true;
float lastX=SCR_WIDTH/2.0f;
float lastY=SCR_HEIGHT/2.0f;

static float deltaTime=0.0f;
static float lastTime=0.0f;

int loadnanosuit(){
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Demo", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    // tell GLFW to capture our mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // tell stb_image.h to flip loaded texture's on the y-axis (before loading model).
//    stbi_set_flip_vertically_on_load(true);
    
    glEnable(GL_DEPTH_TEST);
    
    Shader *shader=new Shader("/Users/sherlock/Documents/Code/OpenGLdemo/OpenGLdemo/LoadModels/Model/nanosuitobj.vs","/Users/sherlock/Documents/Code/OpenGLdemo/OpenGLdemo/LoadModels/Model/nanosuitobj.fs");
    
//    Model *nanosuit=new Model("/Users/sherlock/Documents/Code/OpenGLdemo/OpenGLdemo/LoadModels/models/nanosuit/nanosuit.obj");
//    Model *MawJLaygo=new Model("/Users/sherlock/Documents/Code/OpenGLdemo/OpenGLdemo/LoadModels/models/MawJLaygo.fbx");
    Model *AlienSoldier=new Model("/Users/sherlock/Documents/Code/OpenGLdemo/OpenGLdemo/resource/models/AlienSoldier.fbx");
//    Model *Paladin=new Model("/Users/sherlock/Documents/Code/OpenGLdemo/OpenGLdemo/LoadModels/models/Paladin.fbx");
    
    float movingvelocity=4.0f;
    
    while (!glfwWindowShouldClose(window)) {
        float currentTime=static_cast<float>(glfwGetTime());
        deltaTime=(currentTime-lastTime)*movingvelocity;
        lastTime=currentTime;
        
        processInput(window);
        processCameraWSAD(window, camera, deltaTime);
        
        glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        shader->use();
        glm::mat4 projection=glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH/(float)SCR_HEIGHT, 0.1f, 1000.0f);
        glm::mat4 view=camera.GetViewMatrix();
        shader->setMat4("projection", projection);
        shader->setMat4("view", view);
        glm::mat4 model=glm::scale(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f,0.0f,0.0f)),glm::vec3(1.0f,1.0f,1.0f));
        shader->setMat4("model", model);
        AlienSoldier->Draw(*shader);
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    delete shader;
//    delete nanosuit;
    delete AlienSoldier;
    
    glfwTerminate();
    return 0;
}

void mouse_callback(GLFWwindow* window,double xposIn,double yposIn){
    float xpos=static_cast<float>(xposIn);
    float ypos=static_cast<float>(yposIn);

    if(firstMouse){
        firstMouse=false;
        lastY=ypos;
        lastX=xpos;
    }

    float xoffset=xpos-lastX;
    float yoffset=lastY-ypos;
    lastY=ypos;
    lastX=xpos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow* window,double xoffset,double yoffset){
    camera.ProcessMouseScroll(yoffset);
}
