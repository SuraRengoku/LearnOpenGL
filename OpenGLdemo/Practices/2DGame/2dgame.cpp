//
//  2dgame.cpp
//  OpenGLdemo
//
//  Created by SHERLOCK on 21.11.23.
//

#include "2dgame.hpp"
// The Width of the screen
const GLuint SCREEN_WIDTH = 800;
// The height of the screen
const GLuint SCREEN_HEIGHT = 600;


static void key_callback(GLFWwindow* window,int key,int scancode,int action,int mode);

// DeltaTime variables
GLfloat deltaTime = 0.0f;
GLfloat lastFrame = 0.0f;

Game Breakout(SCREEN_WIDTH,SCREEN_HEIGHT);

int _2dgame(){
    GLFWwindow* window=glfw_Init(SCREEN_WIDTH,SCREEN_HEIGHT,"Breakout");
    
    glfwSetKeyCallback(window, key_callback);
    
    glViewport(0,0,SCREEN_WIDTH,SCREEN_HEIGHT);
    glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    
    Breakout.Init();
    
    Breakout.State=GAME_ACTIVE;
    
    while(!glfwWindowShouldClose(window)){
        GLfloat currentTime=glfwGetTime();
        deltaTime=currentTime-lastFrame;
        lastFrame=currentTime;
        glfwPollEvents();
        
        Breakout.ProcessInput(deltaTime);
        Breakout.Update(deltaTime);
        
        glClearColor(0.0f,0.0f,0.0f,1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        Breakout.Render();
        
        glfwSwapBuffers(window);
    }
    ResourceManager::Clear();//call function without object, make sure the function is static
    glfwTerminate();
    return 0;
}

void key_callback(GLFWwindow* window,int key,int scancode,int action,int mode){
    if(key==GLFW_KEY_ESCAPE && action==GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
    if(key>=0 && key<=1024){
        if(action==GLFW_PRESS)
            Breakout.Keys[key]=GL_TRUE;
        else if(action==GLFW_RELEASE)
            Breakout.Keys[key]=GL_FALSE;
    }
}
