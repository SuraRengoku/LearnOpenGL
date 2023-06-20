////
////  color_0.cpp
////  OpenGLdemo
////
////  Created by SHERLOCK on 11.06.23.
////
//#define STB_IMAGE_IMPLEMENTATION
//#include "color_0.hpp"
//
//void mouse_callback(GLFWwindow* window,double xpos,double ypos);
//void scroll_callback(GLFWwindow* window,double xoffset,double yoffset);
//
//const unsigned int SCR_WIDTH=1200;
//const unsigned int SCR_HEIGHT=800;
//
//static GLfloat vertices[] = {
//    -0.5f, -0.5f, -0.5f,
//     0.5f, -0.5f, -0.5f,
//     0.5f,  0.5f, -0.5f,
//     0.5f,  0.5f, -0.5f,
//    -0.5f,  0.5f, -0.5f,
//    -0.5f, -0.5f, -0.5f,
//
//    -0.5f, -0.5f,  0.5f,
//     0.5f, -0.5f,  0.5f,
//     0.5f,  0.5f,  0.5f,
//     0.5f,  0.5f,  0.5f,
//    -0.5f,  0.5f,  0.5f,
//    -0.5f, -0.5f,  0.5f,
//
//    -0.5f,  0.5f,  0.5f,
//    -0.5f,  0.5f, -0.5f,
//    -0.5f, -0.5f, -0.5f,
//    -0.5f, -0.5f, -0.5f,
//    -0.5f, -0.5f,  0.5f,
//    -0.5f,  0.5f,  0.5f,
//
//     0.5f,  0.5f,  0.5f,
//     0.5f,  0.5f, -0.5f,
//     0.5f, -0.5f, -0.5f,
//     0.5f, -0.5f, -0.5f,
//     0.5f, -0.5f,  0.5f,
//     0.5f,  0.5f,  0.5f,
//
//    -0.5f, -0.5f, -0.5f,
//     0.5f, -0.5f, -0.5f,
//     0.5f, -0.5f,  0.5f,
//     0.5f, -0.5f,  0.5f,
//    -0.5f, -0.5f,  0.5f,
//    -0.5f, -0.5f, -0.5f,
//
//    -0.5f,  0.5f, -0.5f,
//     0.5f,  0.5f, -0.5f,
//     0.5f,  0.5f,  0.5f,
//     0.5f,  0.5f,  0.5f,
//    -0.5f,  0.5f,  0.5f,
//    -0.5f,  0.5f, -0.5f
//};//渲染一个立方体，需要36个顶点
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
//int color_0(){
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
//    glfwSetCursorPosCallback(window, mouse_callback);
//    glfwSetScrollCallback(window, scroll_callback);
//
//    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
//
//    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
//        cout<<"fail to initialize GLAD\n";
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
//    bool show_demo_window=true;
//    bool show_another_window=false;
//    ImVec4 clear_color=ImVec4(0.45f,0.55f,0.60f,1.00f);
//
//    Shader *objshader=new Shader("/Users/sherlock/Documents/Code/OpenGLdemo/OpenGLdemo/Lighting/Color/color_0.vs","/Users/sherlock/Documents/Code/OpenGLdemo/OpenGLdemo/Lighting/Color/object.fs");
//    Shader *lightshader=new Shader("/Users/sherlock/Documents/Code/OpenGLdemo/OpenGLdemo/Lighting/Color/color_0.vs","/Users/sherlock/Documents/Code/OpenGLdemo/OpenGLdemo/Lighting/Color/light.fs");
//
//    unsigned int VBO,ObjectVAO,LightVAO;
//    glGenBuffers(1,&VBO);
//    glGenVertexArrays(1,&ObjectVAO);
//    glGenVertexArrays(1,&LightVAO);
//
//    glBindVertexArray(ObjectVAO);
//    glBindBuffer(GL_ARRAY_BUFFER,VBO);
//    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);
//    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3*sizeof(GL_FLOAT),(void*)0);
//    glEnableVertexAttribArray(0);
//
//    glBindVertexArray(LightVAO);
//    glBindBuffer(GL_ARRAY_BUFFER,VBO);
//    //只需要绑定VBO不用再次设置VBO的数据，因为物体的VBO数据已经正确包含了正确的立方体定点数据
//    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3*sizeof(GL_FLOAT),(void*)0);
//    glEnableVertexAttribArray(0);
//
//    glm::mat4 projection=glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH/(float)SCR_HEIGHT, 0.1f, 100.0f);
//
//    while (!glfwWindowShouldClose(window)) {
//        float currentTIme=static_cast<float>(glfwGetTime());
//        deltaTime=currentTIme-lastTime;
//        lastTime=currentTIme;
//
//        processInput(window);
//        processCameraWSAD(window, camera, deltaTime);
//
//        glClearColor(0.1f,0.1f,0.1f,1.0f);
//        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
//
//        ImGui_ImplOpenGL3_NewFrame();
//        ImGui_ImplGlfw_NewFrame();
//        ImGui::NewFrame();
//
//        if(show_demo_window)
//            ImGui::ShowDemoWindow(&show_demo_window);
//        {
//            static float f=0.0f;
//            static int counter=0;
//            ImGui::Begin("Hello,world!");
//            ImGui::Text("This is some useful text.");
//            ImGui::Checkbox("Demo Window", &show_demo_window);
//            ImGui::Checkbox("Another Window", &show_another_window);
//            ImGui::SliderFloat("float", &f, 0.0f, 1.0f);
//            ImGui::ColorEdit3("clear color", (float*)&clear_color);
//
//            if(ImGui::Button("Button"))
//                counter++;
//            ImGui::SameLine();
//            ImGui::Text("counter=%d",counter);
//            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)",1000.0f/io.Framerate, io.Framerate);
//            ImGui::End();
//        }
//        if(show_another_window){
//            ImGui::Begin("Another Window",&show_another_window);
//            ImGui::Text("Hello from another window!");
//            if(ImGui::Button("Close Me"))
//                show_another_window=false;
//            ImGui::End();
//        }
//
//        //object
//        objshader->use();
//        objshader->setMat4("projection", projection);
//        objshader->setVec3("objectColor", 1.0f, 0.5f, 0.31f);
//        objshader->setVec3("lightColor", 1.0f, 1.0f, 1.0f);
//        glm::mat4 view=camera.GetViewMatrix();
//        objshader->setMat4("view", view);
//        glm::mat4 objmodel=glm::mat4(1.0f);
//        objshader->setMat4("model", objmodel);
//
//        glBindVertexArray(ObjectVAO);
//        glDrawArrays(GL_TRIANGLES,0,36);
//
//        //⚠️注意⚠️ 场景中的物体并不会绑定自己的着色程序，在每次绘制之前，必须要保证要绘制对象的着色程序处于use状态，否则会调用其他的着色程序，使得颜色错乱
//
//        //light
//        lightshader->use();
//        lightshader->setMat4("projection", projection);
//        lightshader->setMat4("view", view);
//        glm::mat4 lightmodel=glm::mat4(1.0f);
//        lightmodel=glm::translate(lightmodel, lightPos);
//        lightmodel=glm::scale(lightmodel,glm::vec3(0.2f));
//        lightshader->setMat4("model", lightmodel);
//
//        glBindVertexArray(ObjectVAO);
//        glDrawArrays(GL_TRIANGLES,0,36);
//
//        ImGui::Render();
//        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
//
//        glfwSwapBuffers(window);
//        glfwPollEvents();
//    }
//    delete lightshader;
//    delete objshader;
//    glDeleteBuffers(1,&VBO);
//    glDeleteVertexArrays(1,&ObjectVAO);
//    glDeleteVertexArrays(1,&LightVAO);
//    ImGui_ImplOpenGL3_Shutdown();
//    ImGui_ImplGlfw_Shutdown();
//    ImGui::DestroyContext();
//
//    glfwTerminate();
//    return 0;
//}
//
//void mouse_callback(GLFWwindow* window,double xposIn,double yposIn){
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
//void scroll_callback(GLFWwindow* window,double xoffset,double yoffset){
//    camera.ProcessMouseScroll(static_cast<float>(yoffset));
//}
