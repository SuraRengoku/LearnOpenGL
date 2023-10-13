////
////  pointshadows.cpp
////  OpenGLdemo
////
////  Created by SHERLOCK on 11.10.23.
////
//
//#include "pointshadows.hpp"
//#define Default_Width 1200;
//#define Default_Height 800;
//
//static unsigned const int SCR_WIDTH=Default_Width;
//static unsigned const int SCR_HEIGHT=Default_Height;
//
//static unsigned const int SHADOW_WIDTH=1024;
//static unsigned const int SHADOW_HEIGHT=1024;
//
//Camera camera(glm::vec3(0.0f,0.0f,3.0f));
//bool firstMouse=true;
//float lastX=SCR_WIDTH/2.0f;
//float lastY=SCR_HEIGHT/2.0f;
//
//GLboolean shadows=true;
//
//static float deltaTime=0.0f;
//static float lastTime=0.0f;
//
//void Shadow();
//void mouse_callback(GLFWwindow* window, double xposIn, double yposIn);
//void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
//
//static GLfloat cubevertices[] = {
//    // Back face
//    -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, // Bottom-left
//    0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f, // top-right
//    0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f, // bottom-right
//    0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,  // top-right
//    -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,  // bottom-left
//    -0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f,// top-left
//    // Front face
//    -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom-left
//    0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,  // bottom-right
//    0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,  // top-right
//    0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, // top-right
//    -0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,  // top-left
//    -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,  // bottom-left
//    // Left face
//    -0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f, // top-right
//    -0.5f, 0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // top-left
//    -0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,  // bottom-left
//    -0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f, // bottom-left
//    -0.5f, -0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f,  // bottom-right
//    -0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f, // top-right
//    // Right face
//    0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, // top-left
//    0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, // bottom-right
//    0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // top-right
//    0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,  // bottom-right
//    0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,  // top-left
//    0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, // bottom-left
//    // Bottom face
//    -0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f, // top-right
//    0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f, // top-left
//    0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,// bottom-left
//    0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f, // bottom-left
//    -0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f, // bottom-right
//    -0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f, // top-right
//    // Top face
//    -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,// top-left
//    0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // bottom-right
//    0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, // top-right
//    0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // bottom-right
//    -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,// top-left
//    -0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f // bottom-left
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
//
//    return cubeVAO;
//}
//void renderCube(unsigned int cubeVAO){
//    glBindVertexArray(cubeVAO);
//    glDrawArrays(GL_TRIANGLES,0,36);
//    glBindVertexArray(0);
//}
//
//int pointshadows(){
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
//    glEnable(GL_FRAMEBUFFER_SRGB);
//    glEnable(GL_DEPTH_TEST);
//    glEnable(GL_CULL_FACE);
//    
//    Shader *shader=new Shader("/Users/sherlock/Documents/Code/OpenGLdemo/OpenGLdemo/AdvancedLighting/PointShadows/scene.vs","/Users/sherlock/Documents/Code/OpenGLdemo/OpenGLdemo/AdvancedLighting/PointShadows/scene.fs");
//    Shader *depthshader=new Shader("/Users/sherlock/Documents/Code/OpenGLdemo/OpenGLdemo/AdvancedLighting/PointShadows/shadowdepth.vs","/Users/sherlock/Documents/Code/OpenGLdemo/OpenGLdemo/AdvancedLighting/PointShadows/shadowdepth.gs","/Users/sherlock/Documents/Code/OpenGLdemo/OpenGLdemo/AdvancedLighting/PointShadows/shadowdepth.fs");
//
//    GLuint depthCubeMap,depthCubeMapFBO;
//    glGenFramebuffers(1,&depthCubeMapFBO);
//    glGenTextures(1,&depthCubeMap);
//    glBindTexture(GL_TEXTURE_CUBE_MAP,depthCubeMap);
//    for(GLuint i=0;i<6;++i)
//        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X+i,0,GL_DEPTH_COMPONENT,SHADOW_WIDTH,SHADOW_HEIGHT,0,GL_DEPTH_COMPONENT,GL_FLOAT,NULL);
//    //GL_DEPTH_COMPONENT表示深度纹理的内部存储格式，存储每个像素的深度值而不包括颜色信息
//    glTexParameteri(GL_TEXTURE_CUBE_MAP,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
//    glTexParameteri(GL_TEXTURE_CUBE_MAP,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
//    glTexParameteri(GL_TEXTURE_CUBE_MAP,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
//    glTexParameteri(GL_TEXTURE_CUBE_MAP,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);
//    glTexParameteri(GL_TEXTURE_CUBE_MAP,GL_TEXTURE_WRAP_R,GL_CLAMP_TO_EDGE);
//
//    glBindFramebuffer(GL_FRAMEBUFFER,depthCubeMapFBO);
//    glFramebufferTexture(GL_FRAMEBUFFER,GL_DEPTH_ATTACHMENT,depthCubeMap,0);
//    glDrawBuffer(GL_NONE);
//    glReadBuffer(GL_NONE);
//    if(glCheckFramebufferStatus(GL_FRAMEBUFFER)!=GL_FRAMEBUFFER_COMPLETE)
//        std::cout<<"Framebuffer not complete!"<<std::endl;
//    glBindFramebuffer(GL_FRAMEBUFFER,0);
//
//    glm::vec3 lightPos(0.0f,0.0f,0.0f);
//
//    GLuint woodTexture=loadTexture("/Users/sherlock/Documents/Code/OpenGLdemo/OpenGLdemo/resource/wood.png",true);
//
//    //光空间变换
//    GLfloat aspect=(GLfloat)SHADOW_WIDTH/(GLfloat)SHADOW_HEIGHT;
//    GLfloat near_plane=1.0f;
//    GLfloat far_plane=25.0f;
//    glm::mat4 shadowProjection=glm::perspective(glm::radians(90.0f), aspect, near_plane, far_plane);//90度视野可以保证六个视锥覆盖整个立方体
//    std::vector<glm::mat4> shadowTransforms;
//    shadowTransforms.push_back(shadowProjection*glm::lookAt(lightPos, lightPos+glm::vec3(1.0f,0.0f,0.0f), glm::vec3(0.0f,-1.0f,0.0f)));
//    shadowTransforms.push_back(shadowProjection*glm::lookAt(lightPos, lightPos+glm::vec3(-1.0f,0.0f,0.0f), glm::vec3(0.0f,-1.0f,0.0f)));
//    shadowTransforms.push_back(shadowProjection*glm::lookAt(lightPos,lightPos+ glm::vec3(0.0f,1.0f,0.0f),glm::vec3(0.0f,0.0f,1.0f)));
//    shadowTransforms.push_back(shadowProjection*glm::lookAt(lightPos,lightPos+glm::vec3(0.0f,-1.0f,0.0f), glm::vec3(0.0f,0.0f,-1.0f)));
//    shadowTransforms.push_back(shadowProjection*glm::lookAt(lightPos, lightPos+glm::vec3(0.0f,0.0f,1.0f),glm::vec3(0.0f,-1.0f,0.0f)));
//    shadowTransforms.push_back(shadowProjection*glm::lookAt(lightPos, lightPos+glm::vec3(0.0f,0.0f,-1.0f),glm::vec3(0.0f,-1.0f,0.0f)));
//    
//    shader->use();
//    shader->setInt("diffuseTexture", 0);
//    shader->setInt("depthCubeMap", 1);
//    
//    depthshader->use();
//    for(GLuint i=0;i<6;i++)
//        depthshader->setMat4(("shadowMatrices["+std::to_string(i)+"]").c_str(), shadowTransforms[i]);
//    depthshader->setVec3("lightPos", lightPos);
//    depthshader->setFloat("far_plane", far_plane);
//
//    GLuint CubeVAO=loadCubeBuffer();
//
//    while (!glfwWindowShouldClose(window)) {
//        float currentTime=static_cast<float>(glfwGetTime());
//        deltaTime=currentTime-lastTime;
//        lastTime=currentTime;
//
//        processInput(window, mouse_callback, scroll_callback);
//        processCameraWSAD(window, camera, deltaTime);
//        Shadow();
//
//        glClearColor(0.1f,0.1f,0.1f,1.0f);
//        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
//
//        depthshader->use();
//        glViewport(0,0,SHADOW_WIDTH,SHADOW_HEIGHT);
//        glBindFramebuffer(GL_FRAMEBUFFER,depthCubeMapFBO);
//        glClear(GL_DEPTH_BUFFER_BIT);
//        glm::mat4 model(1.0f);
//        model=glm::scale(model,glm::vec3(10.0f));
//        depthshader->setMat4("model", model);
//        glDisable(GL_CULL_FACE);//由于是渲染大立方体贴图的内部，所以不能进行背面裁剪
//        depthshader->setInt("reverse_normals", 1);
//        renderCube(CubeVAO);
//        depthshader->setInt("reverse_normals", 0);
//        glEnable(GL_CULL_FACE);
//        model=glm::mat4(1.0f);
//        glm::mat4 model1=glm::translate(model, glm::vec3(4.0f,-3.5f,0.0f));
//        depthshader->setMat4("model", model1);
//        renderCube(CubeVAO);
//        glm::mat4 model2=glm::scale(glm::translate(model, glm::vec3(2.0f,3.0f,1.0f)),glm::vec3(1.5f));
//        depthshader->setMat4("model", model2);
//        renderCube(CubeVAO);
//        glm::mat4 model3=glm::translate(model, glm::vec3(-3.0f,-1.0f,0.0f));
//        depthshader->setMat4("model", model3);
//        renderCube(CubeVAO);
//        glm::mat4 model4=glm::translate(model, glm::vec3(-1.5f,1.0f,0.0f));
//        depthshader->setMat4("model", model4);
//        renderCube(CubeVAO);
//        glm::mat4 model5=glm::scale(glm::rotate(glm::translate(model, glm::vec3(-1.5f,2.0f,-3.0f)),60.0f,glm::normalize(glm::vec3(1.0f,0.0f,1.0f))),glm::vec3(1.5f));
//        depthshader->setMat4("model", model5);
//        renderCube(CubeVAO);
//
//        glBindFramebuffer(GL_FRAMEBUFFER,0);
//        int framebuffersizeWidth,framebuffersizeHeight;
//        glfwGetFramebufferSize(window, &framebuffersizeWidth, &framebuffersizeHeight);
//        glViewport(0,0,framebuffersizeWidth,framebuffersizeHeight);
//        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
//        shader->use();
//        glm::mat4 projection=glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH/(float)SCR_HEIGHT, 0.1f, 100.0f);
//        glm::mat4 view=camera.GetViewMatrix();
//        shader->setMat4("projection", projection);
//        shader->setMat4("view", view);
//        shader->setVec3("lightPos", lightPos);
//        shader->setVec3("viewPos", camera.Position);
//        shader->setInt("shadows", shadows);
//        shader->setFloat("far_plane", far_plane);
//        glActiveTexture(GL_TEXTURE0);
//        glBindTexture(GL_TEXTURE_2D,woodTexture);
//        glActiveTexture(GL_TEXTURE1);
//        glBindTexture(GL_TEXTURE_CUBE_MAP,depthCubeMap);
//        glm::mat4 scenemodel(1.0f);
//        scenemodel=glm::scale(scenemodel,glm::vec3(10.0f));
//        shader->setMat4("model", scenemodel);
//        shader->setMat3("normalMatrix", glm::transpose(glm::inverse(glm::mat3(scenemodel))));
//        glDisable(GL_CULL_FACE);
//        shader->setInt("reverse_normals", 1);
//        renderCube(CubeVAO);
//        shader->setInt("reverse_normals", 0);
//        glEnable(GL_CULL_FACE);
//        scenemodel=glm::mat4(1.0f);
//        glm::mat4 scenemodel1=glm::translate(scenemodel, glm::vec3(4.0f,-3.5f,0.0f));
//        shader->setMat4("model", scenemodel1);
//        shader->setMat3("normalMatrix", glm::transpose(glm::inverse(glm::mat3(scenemodel1))));
//        renderCube(CubeVAO);
//        glm::mat4 scenemodel2=glm::scale(glm::translate(scenemodel, glm::vec3(2.0f,3.0f,1.0f)),glm::vec3(1.5f));
//        shader->setMat4("model", scenemodel2);
//        shader->setMat3("normalMatrix", glm::transpose(glm::inverse(glm::mat3(scenemodel2))));
//        renderCube(CubeVAO);
//        glm::mat4 scenemodel3=glm::translate(scenemodel, glm::vec3(-3.0f,-1.0f,0.0f));
//        shader->setMat4("model", scenemodel3);
//        shader->setMat3("normalMatrix", glm::transpose(glm::inverse(glm::mat3(scenemodel3))));
//        renderCube(CubeVAO);
//        glm::mat4 scenemodel4=glm::translate(scenemodel, glm::vec3(-1.5f,1.0f,0.0f));
//        shader->setMat4("model", scenemodel4);
//        shader->setMat3("normalMatrix", glm::transpose(glm::inverse(glm::mat3(scenemodel4))));
//        renderCube(CubeVAO);
//        glm::mat4 scenemodel5=glm::scale(glm::rotate(glm::translate(scenemodel, glm::vec3(-1.5f,2.0f,-3.0f)),60.0f,glm::normalize(glm::vec3(1.0f,0.0f,1.0f))),glm::vec3(1.5f));
//        shader->setMat4("model", scenemodel5);
//        shader->setMat3("normalMatrix", glm::transpose(glm::inverse(glm::mat3(scenemodel5))));
//        renderCube(CubeVAO);
//        
//        glfwSwapBuffers(window);
//        glfwPollEvents();
//    }
//    delete shader;
//    shader=nullptr;
//    delete depthshader;
//    depthshader=nullptr;
//    
//    glfwTerminate();
//    return 0;
//}
//
//bool keys[1024];//randomly initialization
//bool keysPressed[1024];
//void Shadow(){
//    if(keys[GLFW_KEY_SPACE]&&!keysPressed[GLFW_KEY_SPACE]){
//        shadows=!shadows;
//        keysPressed[GLFW_KEY_SPACE]=true;
//    }
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
