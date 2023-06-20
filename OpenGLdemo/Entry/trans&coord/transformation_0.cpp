////
////  transformation_0.cpp
////  OpenGLdemo
////
////  Created by SHERLOCK on 08.06.23.
////
//#define STB_IMAGE_IMPLEMENTATION
//#include "transformation_0.hpp"
//
//const unsigned int SCR_WIDTH=800;
//const unsigned int SCR_HEIGHT=600;
//
//static GLfloat vertices[]={
//    //     ---- 位置 ----    - 纹理坐标 -
//         0.5f,  0.5f, 0.0f, 1.0f, 1.0f,   // 右上
//         0.5f, -0.5f, 0.0f, 1.0f, 0.0f,   // 右下
//        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,   // 左下
//        -0.5f,  0.5f, 0.0f, 0.0f, 1.0f    // 左上
//
//};
//
//static int indices[]={
//    0,1,3, //first triangle
//    1,2,3  //second triangle
//};
//
//int transformation_0(){
//    glfwInit();
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//
//#ifdef __APPLE__
//    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
//#endif
//
//    GLFWwindow *window=glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "learnOpenGL", NULL, NULL);
//    if(window==nullptr){
//        cout<<"fail to create GLFW window\n";
//        glfwTerminate();
//        return -1;
//    }
//    glfwMakeContextCurrent(window);
//    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
//        cout<<"fail to initialize GLAD\n";
//        return -1;
//    }
////    glViewport(0,0,SCR_WIDTH,SCR_HEIGHT);
////    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
//
//    Shader *shader=new Shader("/Users/sherlock/Documents/Code/OpenGLdemo/OpenGLdemo/Entry/trans&coord/shader_0.vs","/Users/sherlock/Documents/Code/OpenGLdemo/OpenGLdemo/Entry/trans&coord/shader_0.fs");
//
//    glm::vec4 vec(1.0f,0.0f,0.0f,1.0f);
//    glm::mat4 trans=glm::mat4(1.0f);
////    trans=glm::translate(trans, glm::vec3(1.0f,1.0f,0.0f));
//    //偏转
//    glm::mat4 trans_rs=glm::rotate(trans, glm::radians(90.0f), glm::vec3(0.0,0.0,1.0));
//    //glm::rotate参数：
//    //原变换矩阵
//    //变换弧度，可以使用glm::radians(角度)转化弧度
//    //旋转轴
//    trans_rs=glm::scale(trans_rs,glm::vec3(0.5,0.5,0.5));
//
//
//    vec=trans*vec;
//
//    unsigned int VBO,VAO,EBO;
//    glGenBuffers(1,&VBO);
//    glGenBuffers(1,&EBO);
//    glGenVertexArrays(1,&VAO);
//
//    glBindVertexArray(VAO);
//    glBindBuffer(GL_ARRAY_BUFFER,VBO);
//    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
//    glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indices),indices,GL_STATIC_DRAW);
//    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,5*sizeof(GL_FLOAT),(void*)0);
//    glEnableVertexAttribArray(0);
//    glVertexAttribPointer(1,2,GL_FLOAT,GL_FALSE,5*sizeof(GL_FLOAT),(void*)(3*sizeof(GL_FLOAT)));
//    glEnableVertexAttribArray(1);
//
//    unsigned int texture[2];
//    glGenTextures(2,texture);
//    glBindTexture(GL_TEXTURE_2D,texture[0]);
//    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
//    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
//    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
//    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
//    int width, height, nrChannels;
//    unsigned char* data=stbi_load("/Users/sherlock/Documents/Code/OpenGLdemo/OpenGLdemo/resource/container.jpg", &width, &height, &nrChannels, 0);
//    if(data){
//        glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,width,height,0,GL_RGB,GL_UNSIGNED_BYTE,data);
//        glGenerateMipmap(GL_TEXTURE_2D);
//    }else{
//        cout<<"Failed to load texture\n";
//    }
//    stbi_image_free(data);
//
//    glBindTexture(GL_TEXTURE_2D,texture[1]);
//    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
//    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
//    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
//    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
//    data=stbi_load("/Users/sherlock/Documents/Code/OpenGLdemo/OpenGLdemo/resource/awesomeface.png", &width, &height, &nrChannels, 0);
//    if(data){
//        glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,width,height,0,GL_RGBA,GL_UNSIGNED_BYTE,data);
//        glGenerateMipmap(GL_TEXTURE_2D);
//    }else{
//        cout<<"Failed to load texture\n";
//    }
//    stbi_image_free(data);
//
//    shader->use();
//    shader->setInt("texture1", 0);
//    shader->setInt("texture2", 1);
//
//        glActiveTexture(GL_TEXTURE0);
//        glBindTexture(GL_TEXTURE_2D,texture[0]);
//        glActiveTexture(GL_TEXTURE1);
//        glBindTexture(GL_TEXTURE_2D,texture[1]);
//
//    while (!glfwWindowShouldClose(window)) {
//        processInput(window);
//        glClearColor(0.2f,0.3f,0.3f,1.0f);
//        glClear(GL_COLOR_BUFFER_BIT);
//
//        //偏移旋转
//        glm::mat4 trans_tr=glm::translate(trans, glm::vec3(0.5f,-0.5f,0.0f));
//        trans_tr=glm::rotate(trans_tr, (float)glfwGetTime(), glm::vec3(0.0f,0.0f,1.0f));
//
//        //旋转偏移
//        glm::mat4 trans_rt=glm::rotate(trans,(float)glfwGetTime(),glm::vec3(0.0f,0.0f,1.0f));
//        trans_rt=glm::translate(trans_rt, glm::vec3(0.5f,-0.5f,0.0f));
//
//        shader->use();
//        glUniformMatrix4fv(glGetUniformLocation(shader->ID,"transform"),1,GL_FALSE,glm::value_ptr(trans_tr));
//        //glUniformMatrix4fv参数：
//        //uniform位置
//        //发送矩阵数量
//        //是否转置
//        //矩阵数据
//        glBindVertexArray(VAO);
//        glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);
//
//        //左上角缩放
//        float timevalue=glfwGetTime();
//        float scalevalue=sin(timevalue)/2.0f+0.5f;
//        glm::mat4 trans_st=glm::scale(trans, glm::vec3(scalevalue,scalevalue,1.0f));
//        trans_st=glm::translate(trans_st, glm::vec3(-0.5f,0.5f,0.0f));
//        shader->use();
//        glUniformMatrix4fv(glGetUniformLocation(shader->ID,"transform"),1,GL_FALSE,glm::value_ptr(trans_st));
//        glBindVertexArray(VAO);
//        glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);
//
//        glfwSwapBuffers(window);
//        glfwPollEvents();
//    }
//    glDeleteBuffers(1,&EBO);
//    glDeleteBuffers(1,&VBO);
//    glDeleteVertexArrays(1,&VAO);
//    delete shader;
//
//    glfwTerminate();
//    return 0;
//}
