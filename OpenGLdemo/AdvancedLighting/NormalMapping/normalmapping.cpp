////
////  normalmapping.cpp
////  OpenGLdemo
////
////  Created by SHERLOCK on 12.10.23.
////
//
//#include "normalmapping.hpp"
//#define Default_Width 1200;
//#define Default_Height 800;
//
//static unsigned const int SCR_WIDTH=Default_Width;
//static unsigned const int SCR_HEIGHT=Default_Height;
//
//Camera camera(glm::vec3(0.0f,0.0f,3.0f));
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
//static glm::vec3 vertices[]={
//    glm::vec3(-1.0f,1.0f,0.0f),
//    glm::vec3(-1.0f,-1.0f,0.0f),
//    glm::vec3(1.0f,-1.0f,0.0f),
//    glm::vec3(1.0f,1.0f,0.0f)
//};
//static glm::vec2 texCoords[]={
//    glm::vec2(0.0f,1.0f),
//    glm::vec2(0.0f,0.0f),
//    glm::vec2(1.0f,0.0f),
//    glm::vec2(1.0f,1.0f)
//};
//static glm::vec3 normal(0.0f,0.0f,1.0f);
//
//auto loadWallBuffer()->GLuint{
//    GLuint wallVAO,wallVBO;
//    
//    glm::vec3 tangent1,bitangent1;
//    glm::vec3 tangent2,bitangent2;
//    
//    glm::vec3 edge1=vertices[1]-vertices[0];
//    glm::vec3 edge2=vertices[2]-vertices[0];
//    glm::vec2 deltaUV1=texCoords[1]-texCoords[0];
//    glm::vec2 deltaUV2=texCoords[2]-texCoords[0];
//    
//    float Det_=1.0f/(deltaUV1.x*deltaUV2.y-deltaUV2.x*deltaUV1.y);
//    
//    tangent1.x=Det_*(deltaUV2.y*edge1.x-deltaUV1.y*edge2.x);
//    tangent1.y=Det_*(deltaUV2.y*edge1.y-deltaUV1.y*edge2.y);
//    tangent1.z=Det_*(deltaUV2.y*edge1.z-deltaUV1.y*edge2.z);
//    tangent1=glm::normalize(tangent1);//确保是单位向量
//    
//    bitangent1.x=Det_*(-deltaUV2.x*edge1.x+deltaUV1.x*edge2.x);
//    bitangent1.y=Det_*(-deltaUV2.x*edge1.y+deltaUV1.x*edge2.y);
//    bitangent1.z=Det_*(-deltaUV2.x*edge1.z+deltaUV1.x*edge2.z);
//    bitangent1=glm::normalize(bitangent1);
//    
//    edge1=vertices[2]-vertices[0];
//    edge2=vertices[3]-vertices[0];
//    deltaUV1=texCoords[2]-texCoords[0];
//    deltaUV2=texCoords[3]-texCoords[0];
//    
//    tangent2.x=Det_*(deltaUV2.y*edge1.x-deltaUV1.y*edge2.x);
//    tangent2.y=Det_*(deltaUV2.y*edge1.y-deltaUV1.y*edge2.y);
//    tangent2.z=Det_*(deltaUV2.y*edge1.z-deltaUV1.y*edge2.z);
//    tangent2=glm::normalize(tangent2);//确保是单位向量
//    
//    bitangent2.x=Det_*(-deltaUV2.x*edge1.x+deltaUV1.x*edge2.x);
//    bitangent2.y=Det_*(-deltaUV2.x*edge1.y+deltaUV1.x*edge2.y);
//    bitangent2.z=Det_*(-deltaUV2.x*edge1.z+deltaUV1.x*edge2.z);
//    bitangent2=glm::normalize(bitangent2);
//    
//    GLfloat wallVertices[]={
//        vertices[0].x,vertices[0].y,vertices[0].z, normal.x,normal.y,normal.z, texCoords[0].x, texCoords[0].y, tangent1.x,tangent1.y,tangent1.z, bitangent1.x,bitangent1.y,bitangent1.z,
//        vertices[1].x,vertices[1].y,vertices[1].z, normal.x,normal.y,normal.z, texCoords[1].x, texCoords[1].y, tangent1.x,tangent1.y,tangent1.z, bitangent1.x,bitangent1.y,bitangent1.z,
//        vertices[2].x,vertices[2].y,vertices[2].z, normal.x,normal.y,normal.z, texCoords[2].x, texCoords[2].y, tangent1.x,tangent1.y,tangent1.z, bitangent1.x,bitangent1.y,bitangent1.z,
//
//        vertices[0].x,vertices[0].y,vertices[0].z, normal.x,normal.y,normal.z, texCoords[0].x, texCoords[0].y, tangent2.x,tangent2.y,tangent2.z, bitangent2.x,bitangent2.y,bitangent2.z,
//        vertices[2].x,vertices[2].y,vertices[2].z, normal.x,normal.y,normal.z, texCoords[2].x, texCoords[2].y, tangent2.x,tangent2.y,tangent2.z, bitangent2.x,bitangent2.y,bitangent2.z,
//        vertices[3].x,vertices[3].y,vertices[3].z, normal.x,normal.y,normal.z, texCoords[3].x, texCoords[3].y, tangent2.x,tangent2.y,tangent2.z, bitangent2.x,bitangent2.y,bitangent2.z
//    };
//    glGenVertexArrays(1,&wallVAO);
//    glGenBuffers(1,&wallVBO);
//    glBindVertexArray(wallVAO);
//    glBindBuffer(GL_ARRAY_BUFFER,wallVBO);
//    glBufferData(GL_ARRAY_BUFFER,sizeof(wallVertices),&wallVertices,GL_STATIC_DRAW);
//    glEnableVertexAttribArray(0);
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 14 * sizeof(GLfloat), (GLvoid*)0);
//    glEnableVertexAttribArray(1);
//    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 14 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
//    glEnableVertexAttribArray(2);
//    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 14 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
//    glEnableVertexAttribArray(3);
//    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 14 * sizeof(GLfloat), (GLvoid*)(8 * sizeof(GLfloat)));
//    glEnableVertexAttribArray(4);
//    glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, 14 * sizeof(GLfloat), (GLvoid*)(11 * sizeof(GLfloat)));
//    
//    return wallVAO;
//}
//void renderWall(GLuint wallVAO){
//    glBindVertexArray(wallVAO);
//    glDrawArrays(GL_TRIANGLES,0,6);
//    glBindVertexArray(0);
//}
//
//int normalmapping(){
//    glfwInit();
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);//设置上下文主要版本号
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);//次要版本号
//    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//    glfwWindowHint(GL_SAMPLES, 4);//四个采样点
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
//    GLuint wallVAO=loadWallBuffer();
//    
//    Shader *shader=new Shader("/Users/sherlock/Documents/Code/OpenGLdemo/OpenGLdemo/AdvancedLighting/NormalMapping/normalmapping.vs","/Users/sherlock/Documents/Code/OpenGLdemo/OpenGLdemo/AdvancedLighting/NormalMapping/normalmapping.fs");
//    
//    GLuint brickwall=loadTexture("/Users/sherlock/Documents/Code/OpenGLdemo/OpenGLdemo/resource/brickwall.jpg",false);
//    GLuint brickwallnormal=loadTexture("/Users/sherlock/Documents/Code/OpenGLdemo/OpenGLdemo/resource/brickwall_normal.jpg", false);
//    
//    shader->use();
//    shader->setInt("diffuseMap", 0);
//    shader->setInt("normalMap", 1);
//    
//    glm::vec3 LightPos(0.5f,1.0f,0.3f);
//    
//    while (!glfwWindowShouldClose(window)) {
//        GLfloat currentFrame = glfwGetTime();
//        deltaTime = currentFrame - lastTime;
//        lastTime = currentFrame;
//        
//        processInput(window, mouse_callback, scroll_callback);
//        processCameraWSAD(window, camera, deltaTime);
//
//        glClearColor(0.1f,0.1f,0.1f,1.0f);
//        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
//
//        glm::mat4 view=camera.GetViewMatrix();
//        glm::mat4 projection=glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH/(float)SCR_HEIGHT, 0.1f, 100.0f);
//        shader->setMat4("view", view);
//        shader->setMat4("projection", projection);
//        
//        glm::mat4 model(1.0f);
////        model=glm::rotate(model, (GLfloat)glfwGetTime()*(-1), glm::normalize(glm::vec3(1.0f,0.0f,1.0f)));
//        glm::mat4 normalMatrix=glm::transpose(glm::inverse(glm::mat3(model)));
//        shader->setMat4("model", model);
//        shader->setMat3("normalMatrix", normalMatrix);
//        shader->setVec3("lightPos", LightPos);
//        shader->setVec3("viewPos", camera.Position);
//        glActiveTexture(GL_TEXTURE0);
//        glBindTexture(GL_TEXTURE_2D,brickwall);
//        glActiveTexture(GL_TEXTURE1);
//        glBindTexture(GL_TEXTURE_2D,brickwallnormal);
//        renderWall(wallVAO);
//        
//        glfwSwapBuffers(window);
//        glfwPollEvents();
//    }
//    delete shader;
//    shader=nullptr;
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
