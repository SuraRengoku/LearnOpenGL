////
////  shadersApplication.cpp
////  OpenGLdemo
////
////  Created by SHERLOCK on 05.06.23.
////
//
//#include "shadersApplication.hpp"
//
//const unsigned int SCR_WIDTH=800;
//const unsigned int SCR_HEIGHT=600;
//
//float vertices[] = {
//    // 位置              // 颜色
//     0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // 右下
//    -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // 左下
//     0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // 顶部
//};
//
//int shadersApplication(){
//    glfwInit();
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
//
//    GLFWwindow* window=glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "learnOpenGL", NULL, NULL);
//    if(window==nullptr){
//        cout<<"fail to create GLFW window"<<"\n";
//        glfwTerminate();
//        return -1;
//    }
//    glfwMakeContextCurrent(window);
//    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
//        cout<<"fail to initialize GLAD"<<"\n";
//        return -1;
//    }
//    glViewport(0,0,SCR_WIDTH,SCR_HEIGHT);
//    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
//
//    Shader *shader=new Shader("/Users/sherlock/Documents/Code/OpenGLdemo/OpenGLdemo/shader/shader.vs","/Users/sherlock/Documents/Code/OpenGLdemo/OpenGLdemo/shader/shader.fs");
//
//    unsigned int VBO,VAO;
//    glGenVertexArrays(1,&VAO);
//    glGenBuffers(1,&VBO);
//    glBindVertexArray(VAO);
//    glBindBuffer(GL_ARRAY_BUFFER,VBO);
//    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_DYNAMIC_DRAW);
//    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,6*sizeof(GL_FLOAT),(void*)0);
//    glEnableVertexAttribArray(0);
//    glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,6*sizeof(GL_FLOAT),(void*)(3*sizeof(GL_FLOAT)));
//    glEnableVertexAttribArray(1);
//
//    while (!glfwWindowShouldClose(window)) {
//        processInput(window);
//        glClearColor(0.2f,0.3f,0.3f,1.0f);
//        glClear(GL_COLOR_BUFFER_BIT);
//
//        shader->use();
//        float timevalue=glfwGetTime();
//        float RedValue=(sin(timevalue)/2.0f+0.5f);
//        float GreenValue=(sin(timevalue+100)/2.0f+0.5f);
//        float BlueValue=(sin(timevalue-100)/2.0f+0.5f);
//        float xOffset=(sin(timevalue)/2.0f);
//        float yOffset=(cos(timevalue)/2.0f);
//        shader->setFloat("rOffset", RedValue);
//        shader->setFloat("gOffset", GreenValue);
//        shader->setFloat("bOffset", BlueValue);
//        shader->setFloat("xOffset", xOffset);
//        shader->setFloat("yOffset", yOffset);
//        glBindVertexArray(VAO);
//        glDrawArrays(GL_TRIANGLES,0,3);
//
//        glfwSwapBuffers(window);
//        glfwPollEvents();
//    }
//    glDeleteBuffers(1,&VBO);
//    glDeleteVertexArrays(1,&VAO);
//    delete shader;
//
//    glfwTerminate();
//    return 0;
//}
