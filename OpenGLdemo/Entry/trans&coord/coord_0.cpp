////
////  coord_0.cpp
////  OpenGLdemo
////
////  Created by SHERLOCK on 09.06.23.
////
//#define STB_IMAGE_IMPLEMENTATION
//#include "coord_0.hpp"
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
//
//int coord_0(){
//    glfwInit();
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
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
//
//    unsigned int EBO,VBO,VAO;
//    glGenBuffers(1,&EBO);
//    glGenBuffers(1,&VBO);
//    glGenVertexArrays(1,&VAO);
//
//    glBindVertexArray(VAO);
//    glBindBuffer(GL_ARRAY_BUFFER,VBO);
//    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
//    glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indices),indices,GL_STATIC_DRAW);
//
//    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,5*sizeof(GL_FLOAT),(void*)0);
//    glEnableVertexAttribArray(0);
//    glVertexAttribPointer(1,2,GL_FLOAT,GL_FALSE,5*sizeof(GL_FLOAT),(void*)(3*sizeof(GL_FLOAT)));
//    glEnableVertexAttribArray(1);
//
//    Shader *shader=new Shader("/Users/sherlock/Documents/Code/OpenGLdemo/OpenGLdemo/Entry/trans&coord/coord_0.vs","/Users/sherlock/Documents/Code/OpenGLdemo/OpenGLdemo//Entry/trans&coord/coord_0.fs");
//
//    unsigned int texture[2];
//    glGenTextures(2,texture);
//
//    glBindTexture(GL_TEXTURE_2D,texture[0]);
//    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
//    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
//    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
//    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
//    int width,height,nrChannels;
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
//    }else{
//        cout<<"Failed to load texture\n";
//    }
//    stbi_image_free(data);
//
//    shader->use();
//    shader->setInt("texture1", 0);
//    shader->setInt("texture2", 1);
//
//    glActiveTexture(GL_TEXTURE0);
//    glBindTexture(GL_TEXTURE_2D,texture[0]);
//    glActiveTexture(GL_TEXTURE1);
//    glBindTexture(GL_TEXTURE_2D,texture[1]);
//
//    while (!glfwWindowShouldClose(window)) {
//        processInput(window);
//        glClearColor(0.2f,0.3f,0.3f,1.0f);
//        glClear(GL_COLOR_BUFFER_BIT);
//
//        shader->use();
//        glm::mat4 model=glm::rotate(glm::mat4(1.0f),glm::radians(-55.0f),glm::vec3(1.0f,0.0f,0.0f));
//        glm::mat4 view=glm::translate(glm::mat4(1.0f), glm::vec3(0.0f,0.0f,-3.0f));
//        glm::mat4 projection=glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH/(float)SCR_HEIGHT, 0.1f, 100.0f);
//        glUniformMatrix4fv(glGetUniformLocation(shader->ID,"model"),1,GL_FALSE,glm::value_ptr(model));
//        shader->setMat4("view", view);
//        //glm::value_ptr(view)==&view[0][0]
//        shader->setMat4("projection", projection);
//
//        glBindVertexArray(VAO);
//        glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);
//        //最后一个参数指定EBO中偏移量
//
//        glfwSwapBuffers(window);
//        glfwPollEvents();
//    }
//    glDeleteBuffers(1,&EBO);
//    glDeleteBuffers(1,&VBO);
//    glDeleteBuffers(1,&VAO);
//    delete shader;
//
//    glfwTerminate();
//    return 0;
//}
