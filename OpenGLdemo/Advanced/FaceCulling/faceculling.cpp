////
////  faceculling.cpp
////  OpenGLdemo
////
////  Created by SHERLOCK on 12.09.23.
////
//
//#include "faceculling.hpp"
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
//static float planeVertices[] = {
//    // positions          // texture Coords (note we set these higher than 1 (together with GL_REPEAT as texture wrapping mode). this will cause the floor texture to repeat)
//     5.0f, -0.5f,  5.0f,  1.0f, 0.0f,
//    -5.0f, -0.5f, -5.0f,  0.0f, 1.0f,
//    -5.0f, -0.5f,  5.0f,  0.0f, 0.0f,
//
//     5.0f, -0.5f,  5.0f,  1.0f, 0.0f,
//     5.0f, -0.5f, -5.0f,  1.0f, 1.0f,
//    -5.0f, -0.5f, -5.0f,  0.0f, 1.0f
//};
//
//
//void mouse_callback(GLFWwindow* window, double xposIn, double yposIn);
//void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
//
//int faceculling(){
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
//    glEnable(GL_CULL_FACE);
//    bool face_culling=true;
//    /**
//     *GL_FRONT 只剔除背向面
//     *GL_FRONT 只剔除正向面
//     *GL_FRONT_AND_BACK 剔除正向面和背向面
//     */
//    glCullFace(GL_BACK);
//    bool front_culling=false;
//    /**
//     *设置正面的顶点环绕顺序
//     *GL_CCW 逆时针的环绕顺序
//     *GL_CW 顺时针的环绕顺序
//     */
//    glFrontFace(GL_CCW);
//
//    Shader* shader=new Shader("/Users/sherlock/Documents/Code/OpenGLdemo/OpenGLdemo/Advanced/FaceCulling/faceculling.vs","/Users/sherlock/Documents/Code/OpenGLdemo/OpenGLdemo/Advanced/FaceCulling/faceculling.fs");
//
//    unsigned marbleTexture=loadTexture("/Users/sherlock/Documents/Code/OpenGLdemo/OpenGLdemo/resource/marble.jpg");
//    unsigned metalTexture=loadTexture("/Users/sherlock/Documents/Code/OpenGLdemo/OpenGLdemo/resource/metal.png");
//
//    unsigned int cubeVAO,cubeVBO,planeVAO,planeVBO;
//    glGenVertexArrays(1,&cubeVAO);
//    glGenVertexArrays(1,&planeVAO);
//    glGenBuffers(1,&cubeVBO);
//    glGenBuffers(1,&planeVBO);
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
//    glBindVertexArray(0);
//
//    shader->use();
//    shader->setInt("texture1", 0);
//
//    glEnable(GL_DEPTH_TEST);
//    glDepthFunc(GL_LESS);
//
//    const char* glsl_version="#version 330 core";
//    ImGui::CreateContext();
//    ImGuiIO& io=ImGui::GetIO();
//    (void)io;
//    io.ConfigFlags|=ImGuiConfigFlags_NavEnableKeyboard;
//    //对控件启用键盘导航
//    io.ConfigFlags|=ImGuiConfigFlags_NavEnableGamepad;
//    //对控件启用手柄导航
//
//    ImGui::StyleColorsDark();
//    ImGui_ImplGlfw_InitForOpenGL(window, true);
//    //使用OpenGL渲染
//    ImGui_ImplOpenGL3_Init(glsl_version);
//
//    bool show_demo_window=false;
//    bool show_another_window=false;
//    ImVec4 clear_color=ImVec4(0.45f,0.55f,0.60f,1.00f);
//
//    while(!glfwWindowShouldClose(window)){
//        float currentTime=static_cast<float>(glfwGetTime());
//        deltaTime=currentTime-lastTime;
//        lastTime=currentTime;
//
//        processInput(window, mouse_callback, scroll_callback);
//        processCameraWSAD(window, camera, deltaTime);
//
//        glClearColor(0.1f,0.1f,0.1f,1.0f);
//        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
//
//        ImGui_ImplOpenGL3_NewFrame();
//        //开始准备渲染下一帧的内容，通常应该在渲染循环的开头调用
//        ImGui_ImplGlfw_NewFrame();
//        //开始处理与窗口事件和输入相关的内容，通常应该在渲染循环的开头调用
//        ImGui::NewFrame();
//        //创建一个新的界面帧，用于构建和更新ImGui界面，应该在渲染循环开头
//        if(show_demo_window)
//            ImGui::ShowDemoWindow(&show_demo_window);//官方doc
////        static float f=0.0f;
////        static int counter=0;
//        ImGui::Begin("Tool Panel");
//        ImGui::Checkbox("Demo Window", &show_demo_window);
////        ImGui::Checkbox("Another Window", &show_another_window);
////        ImGui::SliderFloat("float", &f, 0.0f, 1.0f);
////        ImGui::ColorEdit3("clear color", (float*)&clear_color);
////        if(ImGui::Button("Button"))
////            counter++;
//        ImGui::Checkbox("Face_Cull", &face_culling);
//        ImGui::Checkbox("Front_Cull", &front_culling);
////        ImGui::SameLine();//同一行显示
////        ImGui::Text("counter=%d",counter);
//        ImGui::NewLine();
//        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)",1000.0f/io.Framerate, io.Framerate);
//        ImGui::End();
//        if(show_another_window){
//            ImGui::Begin("Another Window",&show_another_window);
//            ImGui::Text("Hello from another window!");
//            if(ImGui::Button("Close Me"))
//                show_another_window=false;
//            ImGui::End();
//        }
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
//        glDisable(GL_CULL_FACE);
//        glDrawArrays(GL_TRIANGLES,0,6);
//
//        if(face_culling)
//            glEnable(GL_CULL_FACE);
//        if(front_culling)
//            glCullFace(GL_FRONT);
//        else
//            glCullFace(GL_BACK);
//
//        glBindVertexArray(cubeVAO);
//        glBindTexture(GL_TEXTURE_2D,marbleTexture);
//        shader->setMat4("model", glm::translate(glm::mat4(1.0f), glm::vec3(-1.0f,0.0f,-1.0f)));
//        glDrawArrays(GL_TRIANGLES,0,36);
//        shader->setMat4("model", glm::translate(glm::mat4(1.0f), glm::vec3(2.0f,0.0f,0.0f)));
//        glDrawArrays(GL_TRIANGLES,0,36);
//
//        glBindVertexArray(0);
//
//        ImGui::Render();
//        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
//
//        glfwSwapBuffers(window);
//        glfwPollEvents();
//    }
//    glDeleteVertexArrays(1,&cubeVAO);
//    glDeleteVertexArrays(1,&planeVAO);
//    glDeleteBuffers(1,&cubeVBO);
//    glDeleteBuffers(1,&planeVBO);
//    delete shader;
//    shader=nullptr;
//
//    ImGui_ImplGlfw_Shutdown();
//    ImGui_ImplOpenGL3_Shutdown();
//    ImGui::DestroyContext();
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
