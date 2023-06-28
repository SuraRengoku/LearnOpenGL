////
////  viewlighting.cpp
////  OpenGLdemo
////
////  Created by SHERLOCK on 28.06.23.
////
//#define STB_IMAGE_IMPLEMENTATION
//#include "viewlighting.hpp"
//
//void mouse_callback(GLFWwindow* window,double xposIn,double yposIn);
//void scroll_callback(GLFWwindow* window,double xoffset,double yoffset);
//
//const unsigned int SCR_WIDTH=1200;
//const unsigned int SCR_HEIGHT=800;
//
//static GLfloat vertices[] = {
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
//};//渲染一个立方体，需要36个顶点, 同时还有为了计算漫反射和镜面反射，引入了每个顶点的法向量
//
//Camera camera(glm::vec3(0.0f,0.0f,6.0f));
//bool firstMouse=true;
//float lastX=SCR_WIDTH/2.0f;
//float lastY=SCR_HEIGHT/2.0f;
//
//static float deltaTime=0.0f;
//static float lastTime=0.0f;
//
//glm::vec3 lightPos(1.2f,1.0f,2.0f);
//
//int viewlighting(){
//    glfwInit();
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//#ifdef __APPLE__
//    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
//    const char* glsl_version="#version 330 core";
//#endif
//
//    GLFWwindow *window=glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "learnOpenGL", NULL, NULL);
//    if(window==nullptr){
//        cout<<"fail to load GLFW window\n";
//        glfwTerminate();
//        return -1;
//    }
//    glfwMakeContextCurrent(window);
//    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
//    //鼠标捕捉
//    glfwSetCursorPosCallback(window, mouse_callback);
//    //鼠标滚轮捕捉
//    glfwSetScrollCallback(window, scroll_callback);
//
//    //设置窗口光标形态：消失，隐藏，常规
//    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
//
//    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
//        cout<<"fail to initialize GLAD\n";
//        glfwTerminate();
//        return -1;
//    }
//
//    glEnable(GL_DEPTH_TEST);
//
//    ImGui::CreateContext();
//    ImGuiIO& io=ImGui::GetIO();
//    (void)io;
//    io.ConfigFlags|=ImGuiConfigFlags_NavEnableKeyboard;
//    io.ConfigFlags|=ImGuiConfigFlags_NavEnableGamepad;
//
//    ImGui::StyleColorsDark();
//    ImGui_ImplGlfw_InitForOpenGL(window, true);
//    ImGui_ImplOpenGL3_Init(glsl_version);
//
////    bool show_demo_window=true;
////    bool show_another_window=false;
////    ImVec4 clear_color=ImVec4(0.45f,0.55f,0.60f,1.00f);
//
//    Shader *objshader=new Shader("/Users/sherlock/Documents/Code/OpenGLdemo/OpenGLdemo/Lighting/BasicLighting/viewlighting.vs","/Users/sherlock/Documents/Code/OpenGLdemo/OpenGLdemo/Lighting/BasicLighting/viewlighting.fs");
//    Shader *lightshader=new Shader("/Users/sherlock/Documents/Code/OpenGLdemo/OpenGLdemo/Lighting/BasicLighting/viewlighting.vs","/Users/sherlock/Documents/Code/OpenGLdemo/OpenGLdemo/Lighting/BasicLighting/basiclight.fs");
//
//    unsigned int VBO,objVAO;
//    glGenBuffers(1,&VBO);
//    glGenVertexArrays(1,&objVAO);
//
//    glBindVertexArray(objVAO);
//    glBindBuffer(GL_ARRAY_BUFFER,VBO);
//    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);
//    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,6*sizeof(GL_FLOAT),(void*)0);
//    glEnableVertexAttribArray(0);
//    glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,6*sizeof(GL_FLOAT),(void*)(3*sizeof(GL_FLOAT)));
//    glEnableVertexAttribArray(1);
//
//    unsigned int lightVAO;
//    glGenVertexArrays(1,&lightVAO);
//    glBindVertexArray(lightVAO);
//    glBindBuffer(GL_ARRAY_BUFFER,VBO);
//    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,6*sizeof(GL_FLOAT),(void*)0);
//    glEnableVertexAttribArray(0);
//
//    objshader->use();//不要忘记在填入uniform值之前先应用着色器
//    objshader->setVec3("lightPos",lightPos);//由于光源和物体之间的位置始终不变，故可以在循环外设置
//
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
////        ImGui_ImplOpenGL3_NewFrame();
////        ImGui_ImplGlfw_NewFrame();
////        ImGui::NewFrame();
////        if(show_demo_window)
////            ImGui::ShowDemoWindow(&show_demo_window);
////        {
////            static float f=0.0f;
////            static int counter=0;
////            ImGui::Begin("control");
////            ImGui::Text("control the scene by following panel");
////            ImGui::Checkbox("Demo Window", &show_demo_window);
////            ImGui::Checkbox("Another Window", &show_another_window);
////            ImGui::SliderFloat("float", &f, 0.0f, 1.0f);
////            ImGui::ColorEdit3("clear color", (float*)&clear_color);
////
////            if(ImGui::Button("Button"))
////                counter++;
////            ImGui::SameLine();
////            ImGui::Text("counter=%d",counter);
////            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)",1000.0f/io.Framerate, io.Framerate);
////            ImGui::End();
////        }
////        if(show_another_window){
////            ImGui::Begin("Another Window",&show_another_window);
////            ImGui::Text("Hello from another window!");
////            if(ImGui::Button("Close Me"))
////                show_another_window=false;
////            ImGui::End();
////        }
//
//        glm::mat4 projection=glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH/(float)SCR_HEIGHT, 0.1f, 100.0f);
//
//        objshader->use();
////        objshader->setVec3("viewPos", camera.Position);
//        objshader->setMat4("projection", projection);
//        objshader->setVec3("objectColor",1.0f,0.5f,0.31f);
//        objshader->setVec3("lightColor",1.0f,1.0f,1.0f);
//        glm::mat4 view=camera.GetViewMatrix();
//        objshader->setMat4("view", view);
//        glm::mat4 objmodel=glm::mat4(1.0f);
//        objshader->setMat4("model", objmodel);
//        glm::mat3 normalMatrix=glm::mat3(glm::transpose(glm::inverse(objmodel)));
//        objshader->setMat3("normalMatrix", normalMatrix);
//
//        glBindVertexArray(objVAO);
//        glDrawArrays(GL_TRIANGLES,0,36);
//
//        lightshader->use();
//        lightshader->setVec3("lightPos", lightPos);
//        lightshader->setMat4("projection", projection);
//        lightshader->setMat4("view", view);
//        glm::mat4 lightmodel=glm::mat4(1.0f);
//        lightmodel=glm::translate(lightmodel, lightPos);
//        lightmodel=glm::scale(lightmodel,glm::vec3(0.2f));
//        lightshader->setMat4("model", lightmodel);
//
//        glBindVertexArray(lightVAO);
//        glDrawArrays(GL_TRIANGLES,0,36);
//
////        ImGui::Render();
////        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
//
//        glfwSwapBuffers(window);
//        glfwPollEvents();
//    }
//    delete lightshader;
//    delete objshader;
//    glDeleteBuffers(1,&VBO);
//    glDeleteVertexArrays(1,&objVAO);
//    glDeleteVertexArrays(1,&lightVAO);
////    ImGui_ImplGlfw_Shutdown();
////    ImGui_ImplOpenGL3_Shutdown();
////    ImGui::DestroyContext();
//
//    glfwTerminate();
//    return 0;
//}
//
//void mouse_callback(GLFWwindow* window, double xposIn, double yposIn){
//    float xpos=static_cast<float>(xposIn);
//    float ypos=static_cast<float>(yposIn);
//
//    if(firstMouse){
//        lastX=xpos;
//        lastY=ypos;
//        firstMouse=false;
//    }
//
//    float xoffset=xpos-lastX;
//    float yoffset=lastY-ypos;
//    lastX=xpos;
//    lastY=ypos;
//
//    camera.ProcessMouseMovement(xoffset, yoffset);
//}
//
//void scroll_callback(GLFWwindow* window, double xoffset, double yoffset){
//    camera.ProcessMouseScroll(static_cast<float>(yoffset));
//}
