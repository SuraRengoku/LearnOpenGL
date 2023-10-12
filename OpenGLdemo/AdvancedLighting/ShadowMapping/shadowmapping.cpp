////
////  shadowmapping.cpp
////  OpenGLdemo
////
////  Created by SHERLOCK on 27.09.23.
////
//
//#include "shadowmapping.hpp"
//#define Default_Width 1200;
//#define Default_Height 800;
//
//static unsigned const int SCR_WIDTH=Default_Width;
//static unsigned const int SCR_HEIGHT=Default_Height;
//
//static unsigned const int SHADOW_WIDTH=1024;
//static unsigned const int SHADOW_HEIGHT=1024;
//
//static bool blinn=false;
//static bool blinnKeyPressed=false;
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
//static float planeVertices[] = {
//    // positions            // normals         // texcoords
//     25.0f, -0.5f,  25.0f,  0.0f, 1.0f, 0.0f,  25.0f,  0.0f,
//    -25.0f, -0.5f,  25.0f,  0.0f, 1.0f, 0.0f,   0.0f,  0.0f,
//    -25.0f, -0.5f, -25.0f,  0.0f, 1.0f, 0.0f,   0.0f, 25.0f,
//
//     25.0f, -0.5f,  25.0f,  0.0f, 1.0f, 0.0f,  25.0f,  0.0f,
//    -25.0f, -0.5f, -25.0f,  0.0f, 1.0f, 0.0f,   0.0f, 25.0f,
//     25.0f, -0.5f, -25.0f,  0.0f, 1.0f, 0.0f,  25.0f, 25.0f
//};
//
//static float cubevertices[] = {
//    // back face
//    -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f, // bottom-left
//     1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f, // top-right
//     1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 1.0f, 0.0f, // bottom-right
//     1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f, // top-right
//    -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f, // bottom-left
//    -1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 0.0f, 1.0f, // top-left
//    // front face
//    -1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 0.0f, // bottom-left
//     1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, 0.0f, // bottom-right
//     1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, 1.0f, // top-right
//     1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, 1.0f, // top-right
//    -1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 1.0f, // top-left
//    -1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 0.0f, // bottom-left
//    // left face
//    -1.0f,  1.0f,  1.0f, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-right
//    -1.0f,  1.0f, -1.0f, -1.0f,  0.0f,  0.0f, 1.0f, 1.0f, // top-left
//    -1.0f, -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-left
//    -1.0f, -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-left
//    -1.0f, -1.0f,  1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 0.0f, // bottom-right
//    -1.0f,  1.0f,  1.0f, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-right
//    // right face
//     1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-left
//     1.0f, -1.0f, -1.0f,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-right
//     1.0f,  1.0f, -1.0f,  1.0f,  0.0f,  0.0f, 1.0f, 1.0f, // top-right
//     1.0f, -1.0f, -1.0f,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-right
//     1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-left
//     1.0f, -1.0f,  1.0f,  1.0f,  0.0f,  0.0f, 0.0f, 0.0f, // bottom-left
//    // bottom face
//    -1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f, // top-right
//     1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f, 1.0f, 1.0f, // top-left
//     1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f, // bottom-left
//     1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f, // bottom-left
//    -1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f, 0.0f, 0.0f, // bottom-right
//    -1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f, // top-right
//    // top face
//    -1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f, // top-left
//     1.0f,  1.0f , 1.0f,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f, // bottom-right
//     1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f, 1.0f, 1.0f, // top-right
//     1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f, // bottom-right
//    -1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f, // top-left
//    -1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f, 0.0f, 0.0f  // bottom-left
//};
//
//static float quadVertices[] = {
//    // positions        // texture Coords
//    -1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
//    -1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
//     1.0f,  1.0f, 0.0f, 1.0f, 1.0f,
//     1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
//};
//
//unsigned int loadCubeBuffer(){
//    unsigned int cubeVAO,cubeVBO;
//    glGenVertexArrays(1,&cubeVAO);
//    glGenBuffers(1,&cubeVBO);
//
//    glBindVertexArray(cubeVAO);
//    glBindBuffer(GL_ARRAY_BUFFER,cubeVBO);
//    glBufferData(GL_ARRAY_BUFFER,sizeof(cubevertices),&cubevertices,GL_STATIC_DRAW);
//
//    glEnableVertexAttribArray(0);
//    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,8*sizeof(GL_FLOAT),(void*)0);
//    glEnableVertexAttribArray(1);
//    glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,8*sizeof(GL_FLOAT),(void*)(3*sizeof(GL_FLOAT)));
//    glEnableVertexAttribArray(2);
//    glVertexAttribPointer(2,2,GL_FLOAT,GL_FALSE,8*sizeof(GL_FLOAT),(void*)(6*sizeof(GL_FLOAT)));
//
//    glBindBuffer(GL_ARRAY_BUFFER,0);
//    glBindVertexArray(0);
//    return cubeVAO;
//}
//void renderCube(unsigned int cubeVAO){
//    glBindVertexArray(cubeVAO);
//    glDrawArrays(GL_TRIANGLES,0,36);
//    glBindVertexArray(0);
//}
//
//unsigned int loadQuadBuffer(){
//    unsigned int quadVAO,quadVBO;
//    glGenVertexArrays(1,&quadVAO);
//    glGenBuffers(1,&quadVBO);
//
//    glBindVertexArray(quadVAO);
//    glBindBuffer(GL_ARRAY_BUFFER,quadVBO);
//    glBufferData(GL_ARRAY_BUFFER,sizeof(quadVertices),&quadVertices,GL_STATIC_DRAW);
//
//    glEnableVertexAttribArray(0);
//    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,5*sizeof(GL_FLOAT),(void*)0);
//    glEnableVertexAttribArray(1);
//    glVertexAttribPointer(1,2,GL_FLOAT,GL_FALSE,5*sizeof(GL_FLOAT),(void*)(3*sizeof(GL_FLOAT)));
//
//    glBindBuffer(GL_ARRAY_BUFFER,0);
//    glBindVertexArray(0);
//    return quadVAO;
//}
//void renderQuad(unsigned int quadVAO){
//    glBindVertexArray(quadVAO);
//    glDrawArrays(GL_TRIANGLE_STRIP,0,4);//绘制三角形带 N个顶点N-1个三角形
//    glBindVertexArray(0);
//}
//
//unsigned int loadPlaneBuffer(){
//    unsigned int planeVAO,planeVBO;
//    glGenVertexArrays(1,&planeVAO);
//    glGenBuffers(1,&planeVBO);
//
//    glBindVertexArray(planeVAO);
//    glBindBuffer(GL_ARRAY_BUFFER,planeVBO);
//    glBufferData(GL_ARRAY_BUFFER,sizeof(planeVertices),&planeVertices,GL_STATIC_DRAW);
//
//    glEnableVertexAttribArray(0);
//    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,8*sizeof(GL_FLOAT),(void*)0);
//    glEnableVertexAttribArray(1);
//    glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,8*sizeof(GL_FLOAT),(void*)(3*sizeof(GL_FLOAT)));
//    glEnableVertexAttribArray(2);
//    glVertexAttribPointer(2,2,GL_FLOAT,GL_FALSE,8*sizeof(GL_FLOAT),(void*)(6*sizeof(GL_FLOAT)));
//
////    glBindBuffer(GL_ARRAY_BUFFER,0);
////    glBindVertexArray(0);
//    return planeVAO;
//}
//void renderPlane(unsigned int planeVAO){
//    glBindVertexArray(planeVAO);
//    glDrawArrays(GL_TRIANGLES,0,6);
////    glBindVertexArray(0);
//}
//
//void renderScene(const Shader &shader){
//    glm::mat4 model=glm::mat4(1.0f);
//    shader.setMat4("model", model);
//    
//}
//
//int shadowmapping(){
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
//    glEnable(GL_FRAMEBUFFER_SRGB);
//    glEnable(GL_CULL_FACE);
//
//    unsigned int cubeVAO=loadCubeBuffer();
//    unsigned int quadVAO=loadQuadBuffer();
//    unsigned int planeVAO=loadPlaneBuffer();
//    
//    Shader *shader=new Shader("/Users/sherlock/Documents/Code/OpenGLdemo/OpenGLdemo/AdvancedLighting/ShadowMapping/shadow.vs","/Users/sherlock/Documents/Code/OpenGLdemo/OpenGLdemo/AdvancedLighting/ShadowMapping/shadow.fs");
//
//    Shader *depthshader=new Shader("/Users/sherlock/Documents/Code/OpenGLdemo/OpenGLdemo/AdvancedLighting/ShadowMapping/shadowmapping.vs","/Users/sherlock/Documents/Code/OpenGLdemo/OpenGLdemo/AdvancedLighting/ShadowMapping/shadowmapping.fs");
//    
//    Shader *quadshader=new Shader("/Users/sherlock/Documents/Code/OpenGLdemo/OpenGLdemo/AdvancedLighting/ShadowMapping/scene.vs","/Users/sherlock/Documents/Code/OpenGLdemo/OpenGLdemo/AdvancedLighting/ShadowMapping/scene.fs");
//
//    unsigned int woodTexture=loadTexture("/Users/sherlock/Documents/Code/OpenGLdemo/OpenGLdemo/resource/wood.png", true);
//
//    unsigned int depthMapFBO,depthMap;
//    glGenFramebuffers(1,&depthMapFBO);
//    glGenTextures(1,&depthMap);
//
//    glBindTexture(GL_TEXTURE_2D,depthMap);
//    glTexImage2D(GL_TEXTURE_2D,0,GL_DEPTH_COMPONENT,SHADOW_WIDTH,SHADOW_HEIGHT,0,GL_DEPTH_COMPONENT,GL_FLOAT,NULL);
//    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
//    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
//    //将超出深度贴图的坐标的深度范围设置为1.0f，这样超出的坐标将永远不在阴影之中
//    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_BORDER);
//    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_BORDER);
//    GLfloat borderColor[]={1.0f,1.0f,1.0f,1.0f};
//    glTexParameterfv(GL_TEXTURE_2D,GL_TEXTURE_BORDER_COLOR,borderColor);
//
//    glBindFramebuffer(GL_FRAMEBUFFER,depthMapFBO);
//    glFramebufferTexture2D(GL_FRAMEBUFFER,GL_DEPTH_ATTACHMENT,GL_TEXTURE_2D,depthMap,0);
//    //显式设置OpenGL不使用任何颜色数据进行渲染
//    glDrawBuffer(GL_NONE);
//    glReadBuffer(GL_NONE);
//    glBindFramebuffer(GL_FRAMEBUFFER,0);
//
//    shader->use();
//    shader->setInt("diffuseTexture", 0);
//    shader->setInt("shadowMap", 1);
//    quadshader->use();
//    quadshader->setInt("depthMap", 0);
//
//    glm::vec3 lightPos(-2.0f,4.0f,-1.0f);
//    float near_plane=1.0f,far_plane=7.5f;
//    glm::mat4 lightProjectionOrtho=glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f,near_plane,far_plane);
//    glm::mat4 lightProjectionPersp=glm::perspective(30.0f, (float)SHADOW_WIDTH/(float)SHADOW_HEIGHT, near_plane, far_plane);
//    glm::mat4 lightView=glm::lookAt(lightPos,glm::vec3(0.0f),glm::vec3(0.0f,1.0f,0.0f));
//    glm::mat4 lightSpaceMatrixOrtho=lightProjectionOrtho*lightView;
//    glm::mat4 lightSpaceMatrixPersp=lightProjectionPersp*lightView;
//    depthshader->use();
//    depthshader->setMat4("lightSpaceMatrix", lightSpaceMatrixPersp);
//
//    while (!glfwWindowShouldClose(window)) {
//        float currentTime=static_cast<float>(glfwGetTime());
//        deltaTime=currentTime-lastTime;
//        lastTime=currentTime;
//
//        processInput(window, mouse_callback, scroll_callback);
//        processCameraWSAD(window, camera, deltaTime);
//        Lightshift(window, blinn, blinnKeyPressed);
//
//        glClearColor(0.1f,0.1f,0.1f,1.0f);
//        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
//
//        depthshader->use();
//        glViewport(0,0,SHADOW_WIDTH,SHADOW_HEIGHT);
//        glBindFramebuffer(GL_FRAMEBUFFER,depthMapFBO);
//        glClear(GL_DEPTH_BUFFER_BIT);
//        glActiveTexture(GL_TEXTURE0);
//        glBindTexture(GL_TEXTURE_2D,woodTexture);
//        
//        glm::mat4 model=glm::mat4(1.0f);
//        depthshader->setMat4("model", model);
//        renderPlane(planeVAO);
////        glCullFace(GL_FRONT);//为解决阴影悬浮问题，开启正面剔除
//        depthshader->setMat4("model", glm::scale(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f,1.5f,0.0f)), glm::vec3(0.5f)));
//        renderCube(cubeVAO);
//        depthshader->setMat4("model", glm::scale(glm::translate(glm::mat4(1.0f), glm::vec3(2.0f,0.0f,1.0f)), glm::vec3(0.5f)));
//        renderCube(cubeVAO);
//        depthshader->setMat4("model", glm::scale(glm::rotate(glm::translate(glm::mat4(1.0f), glm::vec3(-1.0f,0.0f,2.0f)),glm::radians(60.0f),glm::normalize(glm::vec3(1.0f,0.0f,1.0f))), glm::vec3(0.25f)));
//        renderCube(cubeVAO);
//
//        int framebuffersizeWidth,framebuffersizeHeight;
//        glfwGetFramebufferSize(window, &framebuffersizeWidth, &framebuffersizeHeight);
//        float scaleFactorX,scaleFactorY;//retina屏幕的缩放因子一般为2
//        glfwGetWindowContentScale(window, &scaleFactorX, &scaleFactorY);
//        int logicalWidth=static_cast<int>(framebuffersizeWidth/scaleFactorX);
//        int logicalHeight=static_cast<int>(framebuffersizeHeight/scaleFactorY);
//        glBindFramebuffer(GL_FRAMEBUFFER,0);
//        glViewport(0,0,framebuffersizeWidth,framebuffersizeHeight);
//        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
//
//        
//        shader->use();
//        glm::mat4 projection=glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH/(float)SCR_HEIGHT, 0.1f, 100.0f);
//        glm::mat4 view=camera.GetViewMatrix();
//        shader->setMat4("projection", projection);
//        shader->setMat4("view", view);
//        shader->setVec3("viewPos", camera.Position);
//        shader->setVec3("lightPos", lightPos);
//        shader->setMat4("lightSpaceMatrix", lightSpaceMatrixPersp);
//        glActiveTexture(GL_TEXTURE0);
//        glBindTexture(GL_TEXTURE_2D,woodTexture);
//        glActiveTexture(GL_TEXTURE1);
//        glBindTexture(GL_TEXTURE_2D,depthMap);
//        
//        glCullFace(GL_FRONT);
//        model=glm::mat4(1.0f);
//        shader->setMat4("model", model);
//        shader->setMat3("normalMatrix", glm::transpose(glm::inverse(glm::mat3(model))));
//        renderPlane(planeVAO);
//        glCullFace(GL_BACK);//恢复到背面剔除
//        shader->setMat4("model", glm::scale(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f,1.5f,0.0f)), glm::vec3(0.5f)));
//        shader->setMat3("normalMatrix", glm::transpose(glm::inverse(glm::mat3(model))));
//        renderCube(cubeVAO);
//        shader->setMat4("model", glm::scale(glm::translate(glm::mat4(1.0f), glm::vec3(2.0f,0.0f,1.0f)), glm::vec3(0.5f)));
//        shader->setMat3("normalMatrix", glm::transpose(glm::inverse(glm::mat3(model))));
//        renderCube(cubeVAO);
//        shader->setMat4("model", glm::scale(glm::rotate(glm::translate(glm::mat4(1.0f), glm::vec3(-1.0f,0.0f,2.0f)),glm::radians(60.0f),glm::normalize(glm::vec3(1.0f,0.0f,1.0f))), glm::vec3(0.25f)));
//        shader->setMat3("normalMatrix", glm::transpose(glm::inverse(glm::mat3(model))));
//        renderCube(cubeVAO);
//        
//        quadshader->use();
//        quadshader->setFloat("near_plane", near_plane);
//        quadshader->setFloat("far_plane", far_plane);
//        glActiveTexture(GL_TEXTURE0);
//        glBindTexture(GL_TEXTURE_2D,depthMap);
////        renderQuad(quadVAO);
//        
//        glfwSwapBuffers(window);
//        glfwPollEvents();
//    }
//    delete quadshader;
//    quadshader=nullptr;
//    delete depthshader;
//    depthshader=nullptr;
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
//
//
