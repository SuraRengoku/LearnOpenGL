////
////  cubemaps.cpp
////  OpenGLdemo
////
////  Created by SHERLOCK on 14.09.23.
////
//
//#include "cubemaps.hpp"
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
//float skyboxVertices[] = {
//    // positions
//    -1.0f,  1.0f, -1.0f,
//    -1.0f, -1.0f, -1.0f,
//     1.0f, -1.0f, -1.0f,
//     1.0f, -1.0f, -1.0f,
//     1.0f,  1.0f, -1.0f,
//    -1.0f,  1.0f, -1.0f,
//
//    -1.0f, -1.0f,  1.0f,
//    -1.0f, -1.0f, -1.0f,
//    -1.0f,  1.0f, -1.0f,
//    -1.0f,  1.0f, -1.0f,
//    -1.0f,  1.0f,  1.0f,
//    -1.0f, -1.0f,  1.0f,
//
//     1.0f, -1.0f, -1.0f,
//     1.0f, -1.0f,  1.0f,
//     1.0f,  1.0f,  1.0f,
//     1.0f,  1.0f,  1.0f,
//     1.0f,  1.0f, -1.0f,
//     1.0f, -1.0f, -1.0f,
//
//    -1.0f, -1.0f,  1.0f,
//    -1.0f,  1.0f,  1.0f,
//     1.0f,  1.0f,  1.0f,
//     1.0f,  1.0f,  1.0f,
//     1.0f, -1.0f,  1.0f,
//    -1.0f, -1.0f,  1.0f,
//
//    -1.0f,  1.0f, -1.0f,
//     1.0f,  1.0f, -1.0f,
//     1.0f,  1.0f,  1.0f,
//     1.0f,  1.0f,  1.0f,
//    -1.0f,  1.0f,  1.0f,
//    -1.0f,  1.0f, -1.0f,
//
//    -1.0f, -1.0f, -1.0f,
//    -1.0f, -1.0f,  1.0f,
//     1.0f, -1.0f, -1.0f,
//     1.0f, -1.0f, -1.0f,
//    -1.0f, -1.0f,  1.0f,
//     1.0f, -1.0f,  1.0f
//};
//
//float cubeVertices[] = {
//    // Back face
//    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, // Bottom-left
//     0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-right
//     0.5f, -0.5f, -0.5f,  1.0f, 0.0f, // bottom-right
//     0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-right
//    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, // bottom-left
//    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, // top-left
//    // Front face
//    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-left
//     0.5f, -0.5f,  0.5f,  1.0f, 0.0f, // bottom-right
//     0.5f,  0.5f,  0.5f,  1.0f, 1.0f, // top-right
//     0.5f,  0.5f,  0.5f,  1.0f, 1.0f, // top-right
//    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f, // top-left
//    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-left
//    // Left face
//    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // top-right
//    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-left
//    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // bottom-left
//    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // bottom-left
//    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-right
//    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // top-right
//    // Right face
//     0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // top-left
//     0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // bottom-right
//     0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-right
//     0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // bottom-right
//     0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // top-left
//     0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-left
//    // Bottom face
//    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // top-right
//     0.5f, -0.5f, -0.5f,  1.0f, 1.0f, // top-left
//     0.5f, -0.5f,  0.5f,  1.0f, 0.0f, // bottom-left
//     0.5f, -0.5f,  0.5f,  1.0f, 0.0f, // bottom-left
//    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-right
//    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // top-right
//    // Top face
//    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, // top-left
//     0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // bottom-right
//     0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-right
//     0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // bottom-right
//    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, // top-left
//    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f  // bottom-left
//};
//float reflectvertices[] = {
//    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
//     0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
//     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
//     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
//    -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
//    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
//
//    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
//     0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
//     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
//     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
//    -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
//    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
//
//    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
//    -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
//    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
//    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
//    -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
//    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
//
//     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
//     0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
//     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
//     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
//     0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
//     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
//
//    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
//     0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
//     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
//     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
//    -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
//    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
//
//    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
//     0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
//     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
//     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
//    -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
//    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
//};
//
//auto DrawCube(unsigned int& VAO,Shader* shader,unsigned int& texture)->void{
//    shader->use();
//    glm::mat4 view=camera.GetViewMatrix();
//    glm::mat4 projection=glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH/(float)SCR_HEIGHT, 0.1f, 100.0f);
//    shader->setMat4("view", view);
//    shader->setMat4("projection", projection);
//    shader->setMat4("model", glm::mat4(1.0f));
//    glBindVertexArray(VAO);
//    glBindTexture(GL_TEXTURE_2D,texture);
//    glDrawArrays(GL_TRIANGLES,0,36);
//}
//
//auto DrawReflectCube(unsigned int& VAO,Shader* shader,unsigned int& texture)->void{
//    shader->use();
//    glm::mat4 view=camera.GetViewMatrix();
//    glm::mat4 projection=glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH/(float)SCR_WIDTH, 0.1f, 100.0f);
//    glm::mat3 normalmatrix=glm::mat3(glm::transpose(glm::inverse(glm::mat4(1.0f))));
//    shader->setMat4("view", view);
//    shader->setMat4("projection", projection);
//    shader->setMat4("model", glm::mat4(1.0f));
//    shader->setVec3("cameraPos", camera.Position);
//    shader->setMat3("normalmatrix", normalmatrix);
//    glBindVertexArray(VAO);
//    glActiveTexture(GL_TEXTURE0);
//    glBindTexture(GL_TEXTURE_CUBE_MAP,texture);
//    glDrawArrays(GL_TRIANGLES,0,36);
//}
//
//auto DrawCubeMap(unsigned int& VAO,Shader* shader,unsigned int& texture){
//    shader->use();
//    glm::mat4 view=glm::mat4(glm::mat3(camera.GetViewMatrix()));
//    glm::mat4 projection=glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH/(float)SCR_HEIGHT, 0.1f, 100.0f);
//    shader->setMat4("view", view);//  去掉view矩阵的第三列，即位移列
//    shader->setMat4("projection", projection);
//    glBindVertexArray(VAO);
//    glActiveTexture(GL_TEXTURE0);
//    glBindTexture(GL_TEXTURE_CUBE_MAP,texture);
//    glDrawArrays(GL_TRIANGLES,0,36);
//}
//
//auto DrawModel(Shader* shader,unsigned int& texture,Model* Model){
//    shader->use();
//    glm::mat4 projection=glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH/(float)SCR_HEIGHT, 0.1f, 1000.0f);
//    glm::mat4 view=camera.GetViewMatrix();
//    shader->setMat4("projection", projection);
//    shader->setMat4("view", view);
//    glm::mat4 model=glm::scale(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f,0.0f,0.0f)),glm::vec3(1.0f,1.0f,1.0f));
//    shader->setMat4("model", model);
//    Model->Draw(*shader);
//}
//
//
//int cubemaps(){
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
//    Shader* cubeshader=new Shader("/Users/sherlock/Documents/Code/OpenGLdemo/OpenGLdemo/Advanced/Cubemaps/cubemaps.vs","/Users/sherlock/Documents/Code/OpenGLdemo/OpenGLdemo/Advanced/Cubemaps/cubemaps.fs");
//    Shader* objectshader=new Shader("/Users/sherlock/Documents/Code/OpenGLdemo/OpenGLdemo/Advanced/Cubemaps/objects.vs","/Users/sherlock/Documents/Code/OpenGLdemo/OpenGLdemo/Advanced/Cubemaps/objects.fs");
//    
//    Shader* reflectshader=new Shader("/Users/sherlock/Documents/Code/OpenGLdemo/OpenGLdemo/Advanced/Cubemaps/objectsreflect.vs","/Users/sherlock/Documents/Code/OpenGLdemo/OpenGLdemo/Advanced/Cubemaps/objectsreflect.fs");
//    
//    Model* Nanosuit=new Model("/Users/sherlock/Documents/Code/OpenGLdemo/OpenGLdemo/resource/models/nanosuit/nanosuit.obj");
//    
//    unsigned int woodTexture=loadTexture("/Users/sherlock/Documents/Code/OpenGLdemo/OpenGLdemo/resource/container2.png");
//
//    vector<string> faces{
//        "/Users/sherlock/Documents/Code/OpenGLdemo/OpenGLdemo/resource/skybox/right.jpg",
//        "/Users/sherlock/Documents/Code/OpenGLdemo/OpenGLdemo/resource/skybox/left.jpg",
//        "/Users/sherlock/Documents/Code/OpenGLdemo/OpenGLdemo/resource/skybox/top.jpg",
//        "/Users/sherlock/Documents/Code/OpenGLdemo/OpenGLdemo/resource/skybox/bottom.jpg",
//        "/Users/sherlock/Documents/Code/OpenGLdemo/OpenGLdemo/resource/skybox/front.jpg",
//        "/Users/sherlock/Documents/Code/OpenGLdemo/OpenGLdemo/resource/skybox/back.jpg",
//    };
//    unsigned int cubemapTexture=loadCubemap(faces);
//    
//    unsigned int containerVAO,containerVBO,reflectVAO,reflectVBO,cubeVAO,cubeVBO;
//    glGenVertexArrays(1,&containerVAO);
//    glGenVertexArrays(1,&reflectVAO);
//    glGenVertexArrays(1,&cubeVAO);
//    glGenBuffers(1,&containerVBO);
//    glGenBuffers(1,&reflectVBO);
//    glGenBuffers(1,&cubeVBO);
//    
//    glBindVertexArray(containerVAO);
//    glBindBuffer(GL_ARRAY_BUFFER,containerVBO);
//    glBufferData(GL_ARRAY_BUFFER,sizeof(cubeVertices),&cubeVertices,GL_STATIC_DRAW);
//    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,5*sizeof(GL_FLOAT),(void*)0);
//    glEnableVertexAttribArray(0);
//    glVertexAttribPointer(1,2,GL_FLOAT,GL_FALSE,5*sizeof(GL_FLOAT),(void*)(3*sizeof(GL_FLOAT)));
//    glEnableVertexAttribArray(1);
//    
//    glBindVertexArray(reflectVAO);
//    glBindBuffer(GL_ARRAY_BUFFER,reflectVBO);
//    glBufferData(GL_ARRAY_BUFFER,sizeof(reflectvertices),&reflectvertices,GL_STATIC_DRAW);
//    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,6*sizeof(GL_FLOAT),(void*)0);
//    glEnableVertexAttribArray(0);
//    glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,6*sizeof(GL_FLOAT),(void*)(3*sizeof(GL_FLOAT)));
//    glEnableVertexAttribArray(1);
//    
//    glBindVertexArray(cubeVAO);
//    glBindBuffer(GL_ARRAY_BUFFER,cubeVBO);
//    glBufferData(GL_ARRAY_BUFFER,sizeof(skyboxVertices),&skyboxVertices,GL_STATIC_DRAW);
//    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3*sizeof(GL_FLOAT),(void*)0);
//    glEnableVertexAttribArray(0);
//    
//    glBindVertexArray(0);
//    
//    cubeshader->use();
//    cubeshader->setInt("skybox", 0);
//    reflectshader->use();
//    reflectshader->setInt("skybox", 0);
//    objectshader->use();
//    objectshader->setInt("texture1", 0);
//    
//    while (!glfwWindowShouldClose(window)) {
//        float currentTime=static_cast<float>(glfwGetTime());
//        deltaTime=currentTime-lastTime;
//        lastTime=currentTime;
//        
//        processInput(window, mouse_callback,scroll_callback);
//        processCameraWSAD(window, camera, deltaTime);
//        
//        glClearColor(0.1f,0.1f,0.1f,1.0f);
//        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
//        
//        glDepthMask(GL_TRUE);
//        glDepthFunc(GL_LEQUAL);//在深度值等于1.0f时也要通过深度测试，否则天空盒不现实
//        
////        float depthValue;
////        int viewport[4];
////        glGetIntegerv(GL_VIEWPORT,viewport);
////        glReadPixels(viewport[2]/2,viewport[3]/2,1,1,GL_DEPTH_COMPONENT,GL_FLOAT,&depthValue);
////        cout<<depthValue<<"\n";
////        DrawCube(containerVAO, objectshader, woodTexture);
////        DrawReflectCube(reflectVAO, reflectshader, cubemapTexture);
//        DrawModel(reflectshader, cubemapTexture, Nanosuit);
//        
//        DrawCubeMap(cubeVAO, cubeshader, cubemapTexture);
//        
//        glBindVertexArray(0);
//        
//        glfwSwapBuffers(window);
//        glfwPollEvents();
//    }
//    glDeleteVertexArrays(1,&cubeVAO);
//    glDeleteVertexArrays(1,&containerVAO);
//    glDeleteBuffers(1,&cubeVBO);
//    glDeleteBuffers(1,&containerVBO);
//    delete cubeshader;
//    cubeshader=nullptr;
//    delete objectshader;
//    objectshader=nullptr;
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
