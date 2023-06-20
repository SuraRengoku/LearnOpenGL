////
////  triangle_1.cpp
////  OpenGLdemo
////
////  Created by SHERLOCK on 05.06.23.
////
//#define GL_SLIENCE_DEPRECATION
//#include "triangle_1.hpp"
//
//const unsigned int SCR_WIDTH=800;
//const unsigned int SCR_HEIGHT=600;
//
//static GLfloat vertices[]={
//    -0.5f,0.5f,0.0f,
//    0.5f,0.5f,0.0f,
//    0.0f,0.0f,0.0f,//share
//    -0.5f,-0.5f,0.0f,
//    0.5f,-0.5f,0.0f
//};
//
//static int indices[]={
//    0,1,2,
//    2,3,4
//};
//
//const char *vertexShaderSource="#version 330 core\n"
//"layout (location=0) in vec3 aPos;\n"
//"void main(){\n"
//"   gl_Position=vec4(aPos.x,aPos.y,aPos.z,1.0f);\n"
//"}\n";
//
//const char *fragmentShaderSource="#version 330 core\n"
//"out vec4 FragColor;\n"
//"void main(){\n"
//"   FragColor=vec4(1.0f,0.5f,0.2f,1.0f);\n"
//"}\n";
//
//int triangle_1(){
//    glfwInit();
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);//for APPLE
//
//    GLFWwindow* window=glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
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
//    unsigned int VBO,EBO,VAO;
//    glGenBuffers(1,&VBO);
//    glGenBuffers(1,&EBO);
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
//    glGenVertexArrays(1,&VAO);
//    glBindVertexArray(VAO);
//    glBindBuffer(GL_ARRAY_BUFFER,VBO);
//    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
//    glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indices),indices,GL_STATIC_DRAW);
//    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3*sizeof(GL_FLOAT),(void*)0);
//    glEnableVertexAttribArray(0);
//
//    while(!glfwWindowShouldClose(window)){
//        processInput(window);
//        glClearColor(0.2f,0.3f,0.3f,1.0f);
//        glClear(GL_COLOR_BUFFER_BIT);
//
//        glUseProgram(shaderProgram);
//        glBindVertexArray(VAO);
//        glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);
//        glfwSwapBuffers(window);
//        glfwPollEvents();
//    }
//    glDeleteVertexArrays(1,&VAO);
//    glDeleteBuffers(1,&VBO);
//    glDeleteBuffers(1,&EBO);
//    glDeleteProgram(shaderProgram);
//
//    glfwTerminate();
//    return 0;
//}
