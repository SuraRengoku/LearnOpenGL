////
////  changingColor.cpp
////  OpenGLdemo
////
////  Created by SHERLOCK on 05.06.23.
////
//
//#include "changingColor.hpp"
//
//const unsigned int SCR_WIDTH=800;
//const unsigned int SCR_HEIGHT=600;
//
//static float vertices[] = {
//    -0.9f, -0.5f, 0.0f,  // left
//    -0.0f, -0.5f, 0.0f,  // right
//    -0.45f, 0.5f, 0.0f,  // top
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
//"uniform vec4 ourColor;\n"
//"void main(){\n"
//"   FragColor=ourColor;\n"
//"}\n";
//
//int changingColor(){
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
//    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,sizeof(GL_FLOAT),(void*)0);
//    glEnableVertexAttribArray(0);
//    
//    while(!glfwWindowShouldClose(window)){
//        processInput(window);
//        glClearColor(0.2f,0.3f,0.3f,1.0f);
//        glClear(GL_COLOR_BUFFER_BIT);
//        
//        glUseProgram(shaderProgram);
//        
//        float timeValue=glfwGetTime();
//        float GreenValue=(sin(timeValue)/2.0f+0.5f);
//        int vertexColorLocation=glGetUniformLocation(shaderProgram,"ourColor");
//        glUniform4f(vertexColorLocation,0.0f,GreenValue,0.0f,1.0f);//更新uniform之前要求着色器程序被使用过
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
