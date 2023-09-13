////
////  blending_.cpp
////  OpenGLdemo
////
////  Created by SHERLOCK on 12.09.23.
////
//
//#include "blending_.hpp"
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
//static float cubeVertices[] = {
//    // positions          // texture Coords
//    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
//     0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
//     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
//     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
//    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
//    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
//
//    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
//     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
//     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
//     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
//    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
//    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
//
//    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
//    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
//    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//
//     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
//     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//     0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
//     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//
//    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//     0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
//     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
//     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
//    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
//    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//
//    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
//     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
//     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
//    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
//
//};
//static float planeVertices[] = {
//    // positions          // texture Coords (note we set these higher than 1 (together with GL_REPEAT as texture wrapping mode). this will cause the floor texture to repeat)
//     5.0f, -0.5f,  5.0f,  1.0f, 0.0f,
//    -5.0f, -0.5f,  5.0f,  0.0f, 0.0f,
//    -5.0f, -0.5f, -5.0f,  0.0f, 1.0f,
//
//     5.0f, -0.5f,  5.0f,  1.0f, 0.0f,
//    -5.0f, -0.5f, -5.0f,  0.0f, 1.0f,
//     5.0f, -0.5f, -5.0f,  1.0f, 1.0f
//};
//float transparentVertices[] = {
//    // positions         // texture Coords (swapped y coordinates because texture is flipped upside down)
//    0.0f,  0.5f,  0.0f,  0.0f,  0.0f,
//    0.0f, -0.5f,  0.0f,  0.0f,  1.0f,
//    1.0f, -0.5f,  0.0f,  1.0f,  1.0f,
//
//    0.0f,  0.5f,  0.0f,  0.0f,  0.0f,
//    1.0f, -0.5f,  0.0f,  1.0f,  1.0f,
//    1.0f,  0.5f,  0.0f,  1.0f,  0.0f
//};
//
//void mouse_callback(GLFWwindow* window, double xposIn, double yposIn);
//void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
//
//
//int blending_(){
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
//    /**
//     * OpenGL中的混合是通过方程C_result=C_source*F_source+C_destination*F_destination实现的
//     * C_source: 源颜色向量，这是源自纹理的颜色向量
//     * C_destination: 目标颜色向量，这是当前储存在颜色缓冲中的颜色向量
//     * F_source: 源因子值，指定了alpha值对源颜色的影响
//     * F_destination: 目标因子值，指定了alpha值对目标颜色的影响
//     */
//    glEnable(GL_BLEND);
//    /**
//     *@param GLenum sfactor 源因子
//     *@param GLenum dfactor 目标因子
//     */
//    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
//    //GL_ZERO 0
//    //GL_ONE 1
//    //GL_SRC_COLOR 因子等于源颜色向量C_source
//    //GL_ONE_MINUS_SRC_COLOR 因子等于1-C_source
//    //GL_DST_COLOR 因子等于目标颜色向量C_destination
//    //GL_ONE_MINUS_DST_COLOR 因子等于1-C_destination
//    //GL_SRC_ALPHA 因子等于C_source的alpha分量
//    //GL_ONE_MINUS_SRC_ALPHA 因子等于1-C_source的alpha分量
//    //GL_DST_ALPHA 因子等于C_destination的alpah分量
//    //GL_ONE_MINUS_DST_ALPHA 因子等于1-C_destination的alpha分量
//    //GL_CONSTANT_COLOR 因子等于常数颜色向量C_constant
//    //GL_ONE_MINUS_CONSTANT_COLOR 因子等于1-C_constant
//    //GL_CONSTANT_ALPHA 因子等于C_constant的alpha分量
//    //GL_ONE_MINUS_CONSTANT_ALPHA 因子等于1-C_constant的alpha分量
//    /**
//     *也开始使用glBlendFuncSeparate为RGB和alpha通道分别设置不同的选项
//     * glBlendFuncSeparate(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA,GL_ONE,GL_ZERO);*
//     */
//    /**
//     *glBlendEquation(GLenum mode)允许我们设置运算符
//     *GL_FUNC_ADD 默认选项，将两个分量相加C_result=Src+Dst
//     *GL_FUNC_SUBTRACT  将两个分量相减，C_result=Src-Dst
//     *GL_FUNC_REVERSE_SUBTRACT 将两个分量相减，但顺序相反C_result=Dst-Src
//     */
//    
//    Shader* shader=new Shader("/Users/sherlock/Documents/Code/OpenGLdemo/OpenGLdemo/Advanced/Blending/blending.vs","/Users/sherlock/Documents/Code/OpenGLdemo/OpenGLdemo/Advanced/Blending/blending_.fs");
//    
//    unsigned marbleTexture=loadTexture("/Users/sherlock/Documents/Code/OpenGLdemo/OpenGLdemo/resource/marble.jpg");
//    unsigned metalTexture=loadTexture("/Users/sherlock/Documents/Code/OpenGLdemo/OpenGLdemo/resource/metal.png");
//    unsigned glassTexture=loadTexture("/Users/sherlock/Documents/Code/OpenGLdemo/OpenGLdemo/resource/blending_transparent_window.png");
//    
//    unsigned int cubeVAO,cubeVBO,planeVAO,planeVBO,glassVAO,glassVBO;
//    glGenVertexArrays(1,&cubeVAO);
//    glGenVertexArrays(1,&planeVAO);
//    glGenVertexArrays(1,&glassVAO);
//    glGenBuffers(1,&cubeVBO);
//    glGenBuffers(1,&planeVBO);
//    glGenBuffers(1,&glassVBO);
//    
//    glBindVertexArray(cubeVAO);
//    glBindBuffer(GL_ARRAY_BUFFER,cubeVBO);
//    glBufferData(GL_ARRAY_BUFFER,sizeof(cubeVertices),&cubeVertices,GL_STATIC_DRAW);
//    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,5*sizeof(GL_FLOAT),(void*)0);
//    glEnableVertexAttribArray(0);
//    glVertexAttribPointer(1,2,GL_FLOAT,GL_FALSE,5*sizeof(GL_FLOAT),(void*)(3*sizeof(GL_FLOAT)));
//    glEnableVertexAttribArray(1);
//
//    glBindVertexArray(planeVAO);
//    glBindBuffer(GL_ARRAY_BUFFER,planeVBO);
//    glBufferData(GL_ARRAY_BUFFER,sizeof(planeVertices),&planeVertices,GL_STATIC_DRAW);
//    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,5*sizeof(GL_FLOAT),(void*)0);
//    glEnableVertexAttribArray(0);
//    glVertexAttribPointer(1,2,GL_FLOAT,GL_FALSE,5*sizeof(GL_FLOAT),(void*)(3*sizeof(GL_FLOAT)));
//    glEnableVertexAttribArray(1);
//
//    glBindVertexArray(glassVAO);
//    glBindBuffer(GL_ARRAY_BUFFER,glassVBO);
//    glBufferData(GL_ARRAY_BUFFER,sizeof(transparentVertices),&transparentVertices,GL_STATIC_DRAW);
//    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,5*sizeof(GL_FLOAT),(void*)0);
//    glEnableVertexAttribArray(0);
//    glVertexAttribPointer(1,2,GL_FLOAT,GL_FALSE,5*sizeof(GL_FLOAT),(void*)(3*sizeof(GL_FLOAT)));
//    glEnableVertexAttribArray(1);
//
//    glBindVertexArray(0);
//    
//    shader->use();
//    shader->setInt("texture1", 0);
//    
//    glEnable(GL_DEPTH_TEST);
//    glDepthFunc(GL_LESS);
//    
//    vector<glm::vec3> transparent{
//        glm::vec3(-1.5f,0.0f,-0.48f),
//        glm::vec3(1.5f,0.0f,0.51f),
//        glm::vec3(0.0f,0.0f,0.7f),
//        glm::vec3(-0.3f,0.0f,-2.3f),
//        glm::vec3(0.5f,0.0f,-0.6f)
//    };
//    
//    /**
//     *当绘制一个有不透明和透明物体的场景的时候，大体的原则如下:
//     *1.先绘制所有不透明的物体
//     *2.对所有透明的物体排序
//     *3.按顺序绘制所有透明的物体
//     */
//    while(!glfwWindowShouldClose(window)){
//        float currentTime=static_cast<float>(glfwGetTime());
//        deltaTime=currentTime-lastTime;
//        lastTime=currentTime;
//        
//        processInput(window);
//        processCameraWSAD(window, camera, deltaTime);
//        
//        glClearColor(0.1f,0.1f,0.1f,1.0f);
//        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
//        
//        glm::mat4 view=camera.GetViewMatrix();
//        glm::mat4 projection=glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH/(float)SCR_HEIGHT, 0.1f, 100.0f);
//        
//        shader->setMat4("view", view);
//        shader->setMat4("projection", projection);
//        shader->setMat4("model", glm::mat4(1.0f));
//        glBindVertexArray(planeVAO);
//        glActiveTexture(GL_TEXTURE0);
//        glBindTexture(GL_TEXTURE_2D,metalTexture);
//        glDrawArrays(GL_TRIANGLES,0,6);
//
//        glBindVertexArray(cubeVAO);
//        glBindTexture(GL_TEXTURE_2D,marbleTexture);
//        shader->setMat4("model", glm::translate(glm::mat4(1.0f), glm::vec3(-1.0f,0.0f,-1.0f)));
//        glDrawArrays(GL_TRIANGLES,0,36);
//        shader->setMat4("model", glm::translate(glm::mat4(1.0f), glm::vec3(2.0f,0.0f,0.0f)));
//        glDrawArrays(GL_TRIANGLES,0,36);
//        
//        std::map<float,glm::vec3> sorted;//从观察者视角获取物体的距离
//        for(unsigned int i=0;i<transparent.size();i++){
//            float distance=glm::length(camera.Position-transparent[i]);
//            sorted[distance]=transparent[i];
//        }
//        glBindVertexArray(glassVAO);
//        glBindTexture(GL_TEXTURE_2D,glassTexture);
//        for(std::map<float,glm::vec3>::reverse_iterator it=sorted.rbegin();it!=sorted.rend();++it){
//            shader->setMat4("model", glm::translate(glm::mat4(1.0f),it->second));
//            glDrawArrays(GL_TRIANGLES,0,6);
//        }
//        
//        glfwSwapBuffers(window);
//        glfwPollEvents();
//    }
//    glDeleteVertexArrays(1,&cubeVAO);
//    glDeleteVertexArrays(1,&planeVAO);
//    glDeleteVertexArrays(1,&glassVAO);
//    glDeleteBuffers(1,&cubeVBO);
//    glDeleteBuffers(1,&planeVBO);
//    glDeleteBuffers(1,&glassVBO);
//    delete shader;
//
//    glfwTerminate();
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
