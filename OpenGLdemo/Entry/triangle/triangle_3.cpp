////
////  triangle_3.cpp
////  OpenGLdemo
////
////  Created by SHERLOCK on 05.06.23.
////
//#define GL_SILENCE_DEPRECATION
//#include "triangle_3.hpp"
//
//const unsigned int SCR_WIDTH=800;
//const unsigned int SCR_HEIGHT=600;
//
//static float firstTriangle[] = {
//    -0.9f, -0.5f, 0.0f,  // left
//    -0.0f, -0.5f, 0.0f,  // right
//    -0.45f, 0.5f, 0.0f,  // top
//};
//static float secondTriangle[] = {
//    0.0f, -0.5f, 0.0f,  // left
//    0.9f, -0.5f, 0.0f,  // right
//    0.45f, 0.5f, 0.0f   // top
//};
//
//const char *vertexShaderSource="#version 330 core\n"
//"layout (location=0) in vec3 aPos;\n"
//"void main(){\n"
//"   gl_Position=vec4(aPos.x,aPos.y,aPos.z,1.0f);\n"
//"}\n";
//
//const char *fragmentShaderSourceOrange="#version 330 core\n"
//"out vec4 FragColor;\n"
//"void main(){\n"
//"   FragColor=vec4(1.0f,0.5f,0.2f,1.0f);\n"
//"}\n";
//
//const char *fragmentShaderSourceYellow="#version 330 core\n"
//"out vec4 FragColor;\n"
//"void main(){\n"
//"   FragColor=vec4(1.0f,1.0f,0.0f,1.0f);\n"
//"}\n";
//
//int triangle_3(){
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
//    unsigned int fragmentShaderOrange=glCreateShader(GL_FRAGMENT_SHADER);
//    glShaderSource(fragmentShaderOrange,1,&fragmentShaderSourceOrange,NULL);
//    glCompileShader(fragmentShaderOrange);
//    test.ShaderTest(fragmentShaderOrange, 0);
//    
//    unsigned int fragmentShaderYellow=glCreateShader(GL_FRAGMENT_SHADER);
//    glShaderSource(fragmentShaderYellow,1,&fragmentShaderSourceYellow,NULL);
//    glCompileShader(fragmentShaderYellow);
//    test.ShaderTest(fragmentShaderYellow, 0);
//    
//    
//    unsigned int shaderProgramOrange=glCreateProgram();
//    glAttachShader(shaderProgramOrange,vertexShader);
//    glAttachShader(shaderProgramOrange,fragmentShaderOrange);
//    glLinkProgram(shaderProgramOrange);
//    test.ProgramTest(shaderProgramOrange);
//    
//    unsigned int shaderProgramYellow=glCreateProgram();
//    glAttachShader(shaderProgramYellow,vertexShader);
//    glAttachShader(shaderProgramYellow,fragmentShaderYellow);
//    glLinkProgram(shaderProgramYellow);
//    test.ProgramTest(shaderProgramYellow);
//    
//    glDeleteShader(vertexShader);
//    glDeleteShader(fragmentShaderYellow);
//    glDeleteShader(fragmentShaderOrange);
//    
//    unsigned int VBOs[2],VAOs[2];
//    glGenVertexArrays(2,VAOs);
//    glGenBuffers(2,VBOs);
//    
//    glBindVertexArray(VAOs[0]);
//    glBindBuffer(GL_ARRAY_BUFFER,VBOs[0]);
//    glBufferData(GL_ARRAY_BUFFER,sizeof(firstTriangle),firstTriangle,GL_STATIC_DRAW);
//    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3*sizeof(GL_FLOAT),(void*)0);
//    glEnableVertexAttribArray(0);
//    
//    glBindVertexArray(VAOs[1]);
//    glBindBuffer(GL_ARRAY_BUFFER,VBOs[1]);
//    glBufferData(GL_ARRAY_BUFFER,sizeof(secondTriangle),secondTriangle,GL_STATIC_DRAW);
//    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,(void*)0);
//    glEnableVertexAttribArray(0);
//    
//    while (!glfwWindowShouldClose(window)) {
//        processInput(window);
//        glClearColor(0.1f,0.2f,0.3f,0.5f);
//        glClear(GL_COLOR_BUFFER_BIT);
//        
//        glUseProgram(shaderProgramOrange);
//        glBindVertexArray(VAOs[0]);
//        glDrawArrays(GL_TRIANGLES,0,3);
//        
//        glUseProgram(shaderProgramYellow);
//        glBindVertexArray(VAOs[1]);
//        glDrawArrays(GL_TRIANGLES,0,3);
//        
//        glfwSwapBuffers(window);
//        glfwPollEvents();
//    }
//    glDeleteProgram(shaderProgramYellow);
//    glDeleteProgram(shaderProgramOrange);
//    glDeleteVertexArrays(2,VAOs);
//    glDeleteBuffers(2,VBOs);
//    
//    glfwTerminate();
//    return 0;
//}
