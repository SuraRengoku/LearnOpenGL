////
////  moreAttributes.cpp
////  OpenGLdemo
////
////  Created by SHERLOCK on 05.06.23.
////
//
//#include "moreAttributes.hpp"
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
//const char *vertexShaderSource="#version 330 core\n"
//"layout (location=0) in vec3 aPos;\n"
//"layout (location=1) in vec3 aColor;\n"
//"out vec3 ourColor;\n"
//"void main(){\n"
//"   gl_Position=vec4(aPos,1.0f);\n"
//"   ourColor=aColor;\n"
//"}\n";
//
//const char *vertexShaderSource_1="#version 330 core\n"
//"layout (location=0) in vec3 aPos;\n"
//"layout (location=1) in vec3 aColor;\n"
//"out vec3 ourColor;\n"
//"void main(){\n"
//"   gl_Position=vec4(-aPos.x,-aPos.y,aPos.z,1.0f);\n"
//"   ourColor=aColor;\n"
//"}\n";
//
//const char *vertexShaderSource_2="#version 330 core\n"
//"layout (location=0) in vec3 aPos;\n"
//"layout (location=1) in vec3 aColor;\n"
//"out vec3 ourColor;\n"
//"uniform float xOffset;\n"
//"void main(){\n"
//"   gl_Position=vec4(aPos.x+xOffset,aPos.y,aPos.z,1.0f);\n"
//"   ourColor=aColor;\n"
//"}\n";
//
//const char *fragmentShaderSource="#version 330 core\n"
//"out vec4 FragColor;\n"
//"in vec3 ourColor;\n"
//"void main(){\n"
//"   FragColor=vec4(ourColor,1.0f);\n"
//"}\n";
//
//int moreAttributes(){
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
//    Test test;
//    unsigned int vertexShader=glCreateShader(GL_VERTEX_SHADER);
//    glShaderSource(vertexShader,1,&vertexShaderSource,NULL);
//    glCompileShader(vertexShader);
//    test.ShaderTest(vertexShader, 1);
//    
//    unsigned int fragmentShader=glCreateShader(GL_FRAGMENT_SHADER);
//    glShaderSource(fragmentShader,1,&fragmentShaderSource,NULL);
//    glCompileShader(fragmentShader);
//    test.ShaderTest(fragmentShader, 0);
//    
//    unsigned int shaderProgram=glCreateProgram();
//    glAttachShader(shaderProgram,vertexShader);
//    glAttachShader(shaderProgram,fragmentShader);
//    glLinkProgram(shaderProgram);
//    test.ProgramTest(shaderProgram);
//    
//    glDeleteShader(vertexShader);
//    glDeleteShader(fragmentShader);
//    
//    unsigned VBO,VAO;
//    glGenVertexArrays(1,&VAO);
//    glGenBuffers(1,&VBO);
//    glBindVertexArray(VAO);
//    glBindBuffer(GL_ARRAY_BUFFER,VBO);
//    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);
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
//        glUseProgram(shaderProgram);
//        glBindVertexArray(VAO);
//        glDrawArrays(GL_TRIANGLES,0,3);
//        
//        glfwSwapBuffers(window);
//        glfwPollEvents();
//    }
//    glDeleteProgram(shaderProgram);
//    glDeleteBuffers(1,&VBO);
//    glDeleteVertexArrays(1,&VAO);
//    
//    glfwTerminate();
//    return 0;
//}
