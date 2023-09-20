////
////  advancedglsl.cpp
////  OpenGLdemo
////
////  Created by SHERLOCK on 20.09.23.
////
//
//#include "advancedglsl.hpp"
//#define Default_Width 1200;
//#define Default_Height 800;
//
//static unsigned const int SCR_WIDTH=Default_Width;
//static unsigned const int SCR_HEIGHT=Default_Height;
//
//Camera camera(glm::vec3(0.0f,0.0f,6.0f));
//bool firstMouse=true;
//float lastX=SCR_WIDTH/2.0f;
//float lastY=SCR_HEIGHT/2.0f;
//
//static float deltaTime=0.0f;
//static float lastTime=0.0f;
//
//void mouse_callback(GLFWwindow* window, double xposIn, double yposIn);
//void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
//
//float cubeVertices[] = {
//        // positions
//    -0.5f, -0.5f, -0.5f,
//     0.5f, -0.5f, -0.5f,
//     0.5f,  0.5f, -0.5f,
//     0.5f,  0.5f, -0.5f,
//    -0.5f,  0.5f, -0.5f,
//    -0.5f, -0.5f, -0.5f,
//
//    -0.5f, -0.5f,  0.5f,
//     0.5f, -0.5f,  0.5f,
//     0.5f,  0.5f,  0.5f,
//     0.5f,  0.5f,  0.5f,
//    -0.5f,  0.5f,  0.5f,
//    -0.5f, -0.5f,  0.5f,
//
//    -0.5f,  0.5f,  0.5f,
//    -0.5f,  0.5f, -0.5f,
//    -0.5f, -0.5f, -0.5f,
//    -0.5f, -0.5f, -0.5f,
//    -0.5f, -0.5f,  0.5f,
//    -0.5f,  0.5f,  0.5f,
//
//     0.5f,  0.5f,  0.5f,
//     0.5f,  0.5f, -0.5f,
//     0.5f, -0.5f, -0.5f,
//     0.5f, -0.5f, -0.5f,
//     0.5f, -0.5f,  0.5f,
//     0.5f,  0.5f,  0.5f,
//
//    -0.5f, -0.5f, -0.5f,
//     0.5f, -0.5f, -0.5f,
//     0.5f, -0.5f,  0.5f,
//     0.5f, -0.5f,  0.5f,
//    -0.5f, -0.5f,  0.5f,
//    -0.5f, -0.5f, -0.5f,
//
//    -0.5f,  0.5f, -0.5f,
//     0.5f,  0.5f, -0.5f,
//     0.5f,  0.5f,  0.5f,
//     0.5f,  0.5f,  0.5f,
//    -0.5f,  0.5f,  0.5f,
//    -0.5f,  0.5f, -0.5f,
//};
//
//int advancedglsl(){
//    glfwInit();
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);//设置上下文主要版本号
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);//次要版本号
//    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//    //GLFW_OPENGL_PROFILE宏用于指定OpenGL上下文的配置文件类型
//    //GLFW_OPENGL_CORE_PROFILE宏用于表示使用核心配置文件
//#ifdef __APPLE__
//    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
//    //启用向前兼容模式，允许在较新的版本中使用较旧的特性
//#endif
//
//    GLFWwindow* window=glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "learnOpenGL", NULL, NULL);
//    try{
//        if(window==nullptr)
//            throw std::runtime_error("window generated unsuccessfully");
//    }catch(std::runtime_error err){
//        cerr<<err.what()<<"\n";
//        glfwTerminate();
//        return -1;
//    }
//
//    glfwMakeContextCurrent(window);
//    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
//    glfwSetCursorPosCallback(window, mouse_callback);
//    glfwSetScrollCallback(window, scroll_callback);
//    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
//
//    try{
//        if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
//            throw std::runtime_error("fail to initialize GLAD");
//    }catch(std::runtime_error err){
//        cerr<<err.what()<<"\n";
//        glfwTerminate();
//        return -1;
//    }
//
//    glEnable(GL_DEPTH_TEST);
//    
//    unsigned int VAO,VBO;
//    glGenVertexArrays(1,&VAO);
//    glGenBuffers(1,&VBO);
//    glBindVertexArray(VAO);
//    glBindBuffer(GL_ARRAY_BUFFER,VBO);
//    glBufferData(GL_ARRAY_BUFFER,sizeof(cubeVertices),&cubeVertices,GL_STATIC_DRAW);
//    glEnableVertexAttribArray(0);
//    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3*sizeof(float),(void*)0);
//    
//    Shader *red=new Shader("/Users/sherlock/Documents/Code/OpenGLdemo/OpenGLdemo/Advanced/AdvancedGLSL/advancedglsl.vs","/Users/sherlock/Documents/Code/OpenGLdemo/OpenGLdemo/Advanced/AdvancedGLSL/red.fs");
//    Shader *green=new Shader("/Users/sherlock/Documents/Code/OpenGLdemo/OpenGLdemo/Advanced/AdvancedGLSL/advancedglsl.vs","/Users/sherlock/Documents/Code/OpenGLdemo/OpenGLdemo/Advanced/AdvancedGLSL/green.fs");
//    Shader *blue=new Shader("/Users/sherlock/Documents/Code/OpenGLdemo/OpenGLdemo/Advanced/AdvancedGLSL/advancedglsl.vs","/Users/sherlock/Documents/Code/OpenGLdemo/OpenGLdemo/Advanced/AdvancedGLSL/blue.fs");
//    Shader *yellow=new Shader("/Users/sherlock/Documents/Code/OpenGLdemo/OpenGLdemo/Advanced/AdvancedGLSL/advancedglsl.vs","/Users/sherlock/Documents/Code/OpenGLdemo/OpenGLdemo/Advanced/AdvancedGLSL/yellow.fs");
//
//    //获取Uniform索引块
//    unsigned int uniformBlockIndexRed=glGetUniformBlockIndex(red->ID,"Matrices");
//    unsigned int uniformBlockIndexGreen=glGetUniformBlockIndex(green->ID,"Matrices");
//    unsigned int uniformBlockIndexBlue=glGetUniformBlockIndex(blue->ID,"Matrices");
//    unsigned int uniformBlockIndexYellow=glGetUniformBlockIndex(yellow->ID,"Matrices");
//    
//    //Matrices在着色器中是0号绑定点
//    glUniformBlockBinding(red->ID,uniformBlockIndexRed,0);
//    glUniformBlockBinding(green->ID,uniformBlockIndexGreen,0);
//    glUniformBlockBinding(blue->ID,uniformBlockIndexBlue,0);
//    glUniformBlockBinding(yellow->ID,uniformBlockIndexYellow,0);
//    
//    //创建Uniform缓冲对象本身
//    unsigned int uboMatrices;
//    glGenBuffers(1,&uboMatrices);
//    glBindBuffer(GL_UNIFORM_BUFFER,uboMatrices);
//    glBufferData(GL_UNIFORM_BUFFER,2*sizeof(glm::mat4),NULL,GL_STATIC_DRAW);//NULL表示分配内存但未填充
//    glBindBuffer(GL_UNIFORM_BUFFER,0);
//    //将缓冲中的特定范围链接到绑定点0 这里是从0到两个mat4的大小
//    glBindBufferRange(GL_UNIFORM_BUFFER,0,uboMatrices,0,2*sizeof(glm::mat4));
//    
//    //填充缓冲
//    glm::mat4 projection=glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH/(float)SCR_HEIGHT, 0.1f, 100.0f);
//    
//    glBindBuffer(GL_UNIFORM_BUFFER,uboMatrices);
//    glBufferSubData(GL_UNIFORM_BUFFER,0,sizeof(glm::mat4),glm::value_ptr(projection));
//    glBindBuffer(GL_UNIFORM_BUFFER,0);
//    //至此四个立方体的投影和观察矩阵都是一样的
//    while (!glfwWindowShouldClose(window)) {
//        float currentTime=static_cast<float>(glfwGetTime());
//        deltaTime=currentTime-lastTime;
//        lastTime=currentTime;
//        
//        processInput(window, mouse_callback, scroll_callback);
//        processCameraWSAD(window, camera, deltaTime);
//        
//        glClearColor(0.1f,0.1f,0.1f,1.0f);
//        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
//        
//        glm::mat4 view=camera.GetViewMatrix();
//        glBindBuffer(GL_UNIFORM_BUFFER,uboMatrices);
//        glBufferSubData(GL_UNIFORM_BUFFER,sizeof(glm::mat4),sizeof(glm::mat4),glm::value_ptr(view));
//        glBindBuffer(GL_UNIFORM_BUFFER,0);
//        
//        glBindVertexArray(VAO);
//        red->use();
//        red->setMat4("model", glm::translate(glm::mat4(1.0f), glm::vec3(-0.75f,0.75f,0.0f)));
//        glDrawArrays(GL_TRIANGLES,0,36);
//        
//        green->use();
//        green->setMat4("model", glm::translate(glm::mat4(1.0f), glm::vec3(0.75f,0.75f,0.0f)));
//        glDrawArrays(GL_TRIANGLES,0,36);
//
//        blue->use();
//        blue->setMat4("model", glm::translate(glm::mat4(1.0f), glm::vec3(-0.75f,-0.75f,0.0f)));
//        glDrawArrays(GL_TRIANGLES,0,36);
//
//        yellow->use();
//        yellow->setMat4("model", glm::translate(glm::mat4(1.0f), glm::vec3(0.75f,-0.75f,0.0f)));
//        glDrawArrays(GL_TRIANGLES,0,36);
//        
//        glfwSwapBuffers(window);
//        glfwPollEvents();
//    }
//    glDeleteVertexArrays(1,&VAO);
//    glDeleteBuffers(1,&VBO);
//    glDeleteBuffers(1,&uboMatrices);
//    delete red;
//    red=nullptr;
//    delete green;
//    green=nullptr;
//    delete blue;
//    blue=nullptr;
//    delete yellow;
//    yellow=nullptr;
//    
//    return 0;
//}
//
//void mouse_callback(GLFWwindow* window, double xposIn, double yposIn){
//    float xpos=static_cast<float>(xposIn);
//    float ypos=static_cast<float>(yposIn);
//    if(firstMouse){
//        lastX=xpos;
//        lastY=ypos;
//        firstMouse=false;
//    }
//    float xoffset=xpos-lastX;
//    float yoffset=lastY-ypos;
//    lastY=ypos;
//    lastX=xpos;
//    camera.ProcessMouseMovement(xoffset, yoffset);
//}
//
//void scroll_callback(GLFWwindow* window, double xoffset, double yoffset){
//    camera.ProcessMouseScroll(yoffset);
//}
