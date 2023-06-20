////
////  texture_0.cpp
////  OpenGLdemo
////
////  Created by SHERLOCK on 05.06.23.
////
//#define STB_IMAGE_IMPLEMENTATION
////宏定义最好写在源文件中，这样可以避免在包含同一个头文件的多个源文件中重复定义宏
//#include "texture_0.hpp"
//
//const unsigned int SCR_WIDTH=800;
//const unsigned int SCR_HEIGHT=600;
//
//static GLfloat vertices[]={
//    //     ---- 位置 ----       ---- 颜色 ----     - 纹理坐标 -
//         0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // 右上
//         0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // 右下
//        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // 左下
//        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // 左上
//};
//
//static int indices[]={
//    0,1,3, //first triangle
//    1,2,3  //second triangle
//};
//
//int texture_0(){
//    glfwInit();
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
//
//    GLFWwindow *window=glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "learnOpenGL", NULL, NULL);
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
//    Shader *shader=new Shader("/Users/sherlock/Documents/Code/OpenGLdemo/OpenGLdemo/Entry/texture/shader_0.vs","/Users/sherlock/Documents/Code/OpenGLdemo/OpenGLdemo/Entry/texture/shader_0.fs");
//
//    unsigned int VBO,VAO,EBO;
//    glGenVertexArrays(1,&VAO);
//    glGenBuffers(1,&VBO);
//    glGenBuffers(1,&EBO);
//
//    glBindVertexArray(VAO);
//    glBindBuffer(GL_ARRAY_BUFFER,VBO);
//    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
//    glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indices),indices,GL_STATIC_DRAW);
//
//    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,8*sizeof(GL_FLOAT),(void*)0);
//    glEnableVertexAttribArray(0);
//    glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,8*sizeof(GL_FLOAT),(void*)(3*sizeof(GL_FLOAT)));
//    glEnableVertexAttribArray(1);
//    glVertexAttribPointer(2,2,GL_FLOAT,GL_FALSE,8*sizeof(GL_FLOAT),(void*)(6*sizeof(GL_FLOAT)));
//    glEnableVertexAttribArray(2);
//
//    unsigned int texture[2];
//    glGenTextures(2,texture);
//    glBindTexture(GL_TEXTURE_2D,texture[0]);
//    //为当前绑定的纹理对象设置环绕和过滤方式
//    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
//    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
//    //环绕方式
//    //GL_REPEAT:对纹理的默认行为，重复纹理图像
//    //GL_MIRRORED_REPEAT:和GL_REPEAT一样，但每次重复图片都是镜像放置的
//    //GL_CLAMP_TO_EDGE:纹理坐标会被约束在0到1之间，超出的部分会重复纹理坐标的边缘，产生一种边缘被拉伸到效果
//    //GL_CLAMP_TO_BORDER:超过的坐标为用户指定的边缘颜色，使用glTexParameterfv(GL_TEXTURE_2D,GL_TEXTURE_BORDER_COLOR,borderColor)指定
//    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
//    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
//    //过滤方式
//    //GL_TEXTURE_MIN_FILTER:缩小
//    //GL_TEXTURE_MAG_FILTER:放大
//    //GL_NEAREST:邻近过滤
//    //GL_LINEAR:线性过滤
//    //采用Mipmap
//    //GL_NEAREST_MIPMAP_NEAREST:采用最邻近的多级渐远纹理来匹配像素大小，并使用邻近插值进行纹理采样
//    //GL_LINEAR_MIPMAP_NEAREST:使用最邻近的多级渐远纹理级别，并使用线性插值进行采样
//    //GL_NEAREST_MIPMAP_LINEAR:在两个最匹配像素大小的多级渐远纹理之间进行线性插值，使用邻近插值进行采样
//    //GL_LINEAR_MIPMAP_LINEAR:在两个邻近的多级渐远纹理之间使用线性插值，并使用线性插值进行采样
//
//    int width,height,nrChannels;
//    stbi_set_flip_vertically_on_load(true);
//    unsigned char *data=stbi_load("/Users/sherlock/Documents/Code/OpenGLdemo/OpenGLdemo/resource/container.jpg", &width, &height, &nrChannels, 0);
//    if(data){
//        glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,width,height,0,GL_RGB,GL_UNSIGNED_BYTE,data);
//        //glTexImage2D生成纹理
//        //GL_TEXTURE_2D指定纹理目标，意味着会生成与当前绑定的纹理对象在同一个目标上的纹理，任何绑定到GL_TEXTURE_1D和GL_TEXTURE_3D上的纹理都不会收到影响
//        //0指定多级纹理级别，0是基本级别
//        //GL_RGB指定纹理存储格式
//        //width和height指定最终纹理的宽度和高度
//        //0总是为0(历史遗留问题)
//        //GL_RGB和GL_UNSIGNED_BYTE定义了源图的格式和数据类型
//        //data是图像数据
//        glGenerateMipmap(GL_TEXTURE_2D);//生成多级纹理
//    }
//    else{
//        cout<<"Failed to load texture"<<"\n";
//    }
//    stbi_image_free(data);
//
//    glBindTexture(GL_TEXTURE_2D,texture[1]);
//    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
//    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
//    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
//    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
//    data=stbi_load("/Users/sherlock/Documents/Code/OpenGLdemo/OpenGLdemo/resource/awesomeface.png", &width, &height, &nrChannels, 0);
//    if(data){
//        glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,width,height,0,GL_RGBA,GL_UNSIGNED_BYTE,data);
//        glGenerateMipmap(GL_TEXTURE_2D);
//    }else{
//        cout<<"Failed to load texture"<<"\n";
//    }
//    stbi_image_free(data);
//
//    shader->use();//使用uniform前必须先激活着色器
//    glUniform1i(glGetUniformLocation(shader->ID,"ourTexture1"),0);
//    shader->setInt("ourTexture2", 1);
//
//    while (!glfwWindowShouldClose(window)) {
//        processInput(window);
//        glClearColor(0.2f,0.3f,0.3f,1.0f);
//        glClear(GL_COLOR_BUFFER_BIT);
//        //绑定纹理
//        glActiveTexture(GL_TEXTURE0);
//        glBindTexture(GL_TEXTURE_2D,texture[0]);
//        glActiveTexture(GL_TEXTURE1);
//        glBindTexture(GL_TEXTURE_2D,texture[1]);
//        //纹理单元的目的是可是同时使用多个纹理，可以使用glActiveTexture来激活纹理单元，传入想要的纹理
//
//        shader->use();
//        glBindVertexArray(VAO);
//        glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);
//
//        glfwSwapBuffers(window);
//        glfwPollEvents();
//    }
//    glDeleteBuffers(1,&VBO);
//    glDeleteBuffers(1,&EBO);
//    glDeleteVertexArrays(1,&VAO);
//    delete shader;
//
//    glfwTerminate();
//    return 0;
//}
