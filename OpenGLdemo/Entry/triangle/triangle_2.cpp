////
////  triangle_2.cpp
////  OpenGLdemo
////
////  Created by SHERLOCK on 05.06.23.
////
//
//#include "triangle_2.hpp"
//
//const unsigned int SCR_WIDTH=800;
//const unsigned int SCR_HEIGHT=600;
//
//static GLfloat vertices[]={
//    -0.5f,0.5f,0.0f,
//    0.5f,0.5f,0.0f,
//    0.0f,0.0f,0.0f
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
//int triangle_2(){
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
//    unsigned int VBOs[2],VAOs[2];
//    glGenVertexArrays(2,VAOs);
//    glGenBuffers(2,VBOs);
//    
//    glBindVertexArray(VAOs[0]);
//    glBindBuffer(GL_ARRAY_BUFFER,VBOs[0]);
//    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);
//    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3*sizeof(GL_FLOAT),(void*)0);
//    glEnableVertexAttribArray(0);
//    
//    glBindVertexArray(VAOs[1]);
//    glBindBuffer(GL_ARRAY_BUFFER,VBOs[1]);
//    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);
//    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,(void*)0);
//    //because the vertex data is tightly packed we can also sepcify 0 as the vertex attribute's stride to let OpenGL figure it out
//    glEnableVertexAttribArray(0);
//    
//    while(!glfwWindowShouldClose(window)){
//        processInput(window);
//        glClearColor(0.1f,0.2f,0.3f,0.5f);
//        glClear(GL_COLOR_BUFFER_BIT);
//        
//        glUseProgram(shaderProgram);
//        glBindVertexArray(VAOs[0]);
//        glDrawArrays(GL_TRIANGLES,0,3);
//        
//        glBindVertexArray(VAOs[1]);
//        glDrawArrays(GL_TRIANGLES,0,3);
//        
//        glfwSwapBuffers(window);
//        glfwPollEvents();
//    }
//    glDeleteProgram(shaderProgram);
//    glDeleteVertexArrays(2,VAOs);
//    glDeleteBuffers(2,VBOs);
//    
//    glfwTerminate();
//    return 0;
//}
