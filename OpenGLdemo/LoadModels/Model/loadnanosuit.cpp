////
////  loadnanosuit.cpp
////  OpenGLdemo
////
////  Created by SHERLOCK on 22.07.23.
////
//#include "loadnanosuit.hpp"
//
//static unsigned const int SCR_WIDTH=1200;
//static unsigned const int SCR_HEIGHT=800;
//
//void mouse_callback(GLFWwindow* window,double xposIn,double yposIn);
//void scroll_callback(GLFWwindow* window,double xoffset,double yoffset);
//
//static GLfloat vertices[]={
//    // positions          // normals           // texture coords
//    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
//     0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
//     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
//     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
//    -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
//    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
//
//    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
//     0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
//     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
//     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
//    -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
//    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
//
//    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
//    -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
//    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
//    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
//    -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
//    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
//
//     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
//     0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
//     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
//     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
//     0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
//     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
//
//    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
//     0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
//     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
//     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
//    -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
//    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
//
//    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
//     0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
//     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
//     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
//    -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
//    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
//};
//
//
//Camera camera(glm::vec3(0.0f,10.0f,20.0f));
//bool firstMouse=true;
//float lastX=SCR_WIDTH/2.0f;
//float lastY=SCR_HEIGHT/2.0f;
//
//static float deltaTime=0.0f;
//static float lastTime=0.0f;
//
//int loadnanosuit(){
//    // glfw: initialize and configure
//    // ------------------------------
//    glfwInit();
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//
//#ifdef __APPLE__
//    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
//#endif
//
//    // glfw window creation
//    // --------------------
//    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Demo", NULL, NULL);
//    if (window == NULL)
//    {
//        std::cout << "Failed to create GLFW window" << std::endl;
//        glfwTerminate();
//        return -1;
//    }
//    glfwMakeContextCurrent(window);
//    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
//    glfwSetCursorPosCallback(window, mouse_callback);
//    glfwSetScrollCallback(window, scroll_callback);
//
//    // tell GLFW to capture our mouse
//    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
//
//    // glad: load all OpenGL function pointers
//    // ---------------------------------------
//    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
//    {
//        std::cout << "Failed to initialize GLAD" << std::endl;
//        return -1;
//    }
//
//    // tell stb_image.h to flip loaded texture's on the y-axis (before loading model).
////    stbi_set_flip_vertically_on_load(true);
//
//    glEnable(GL_DEPTH_TEST);
//
//    Shader *shader=new Shader("/Users/sherlock/Documents/Code/OpenGLdemo/OpenGLdemo/LoadModels/Model/nanosuitobj.vs","/Users/sherlock/Documents/Code/OpenGLdemo/OpenGLdemo/LoadModels/Model/nanosuitobj.fs");
//
//    Shader *lightshader=new Shader("/Users/sherlock/Documents/Code/OpenGLdemo/OpenGLdemo/LoadModels/Model/light.vs","/Users/sherlock/Documents/Code/OpenGLdemo/OpenGLdemo/LoadModels/Model/light.fs");
//
//    unsigned int lightVAO, lightVBO;
//    glGenVertexArrays(1,&lightVAO);
//    glGenBuffers(1,&lightVBO);
//
//    glBindVertexArray(lightVAO);
//    glBindBuffer(GL_ARRAY_BUFFER,lightVBO);
//    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);
//    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,8*sizeof(GL_FLOAT),(void*)0);
//    glEnableVertexAttribArray(0);
//
//    Model *nanosuit=new Model("/Users/sherlock/Documents/Code/OpenGLdemo/OpenGLdemo/resource/models/nanosuit/nanosuit.obj");
//
//    Model *nanosuit_reflection=new Model("/Users/sherlock/Documents/Code/OpenGLdemo/OpenGLdemo/resource/models/nanosuit_reflection/nanosuit.obj");
////    Model *MawJLaygo=new Model("/Users/sherlock/Documents/Code/OpenGLdemo/OpenGLdemo/LoadModels/models/MawJLaygo.fbx");
//    Model *AlienSoldier=new Model("/Users/sherlock/Documents/Code/OpenGLdemo/OpenGLdemo/resource/models/AlienSoldier.fbx");
//    Model *Paladin=new Model("/Users/sherlock/Documents/Code/OpenGLdemo/OpenGLdemo/resource/models/Paladin.fbx");
//
//    Model *room=new Model("/Users/sherlock/Documents/Code/OpenGLdemo/OpenGLdemo/resource/0817.fbx");
//
//    float movingvelocity=4.0f;
//
//    glm::vec3 specularColor=glm::vec3(1.0f,1.0f,1.0f);
//    glm::vec3 ambientColor=glm::vec3(0.5f,0.5f,0.5f);
//    glm::vec3 diffuseColor=glm::vec3(0.8f,0.8f,0.8f);
//
//    shader->use();
//    shader->setFloat("shininess", 64.0f);
//    shader->setVec3("light.ambient", ambientColor);
//    shader->setVec3("light.diffuse", diffuseColor);
//    shader->setVec3("light.specular", specularColor);
//
////    glEnable(GL_FRAMEBUFFER_SRGB);
//
//    while (!glfwWindowShouldClose(window)) {
//        float currentTime=static_cast<float>(glfwGetTime());
//        deltaTime=(currentTime-lastTime)*movingvelocity;
//        lastTime=currentTime;
//
//        processInput(window,mouse_callback,scroll_callback);
//        processCameraWSAD(window, camera, deltaTime);
//
//        glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
//        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//        float x=cos(currentTime)*4;
//        float y=13;
//        float z=sin(currentTime)*4;
//        glm::vec3 lightPos=glm::vec3(x,y,z);
//
//        shader->use();
//        glm::mat4 projection=glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH/(float)SCR_HEIGHT, 0.1f, 1000.0f);
//        glm::mat4 view=camera.GetViewMatrix();
//        shader->setMat4("projection", projection);
//        shader->setMat4("view", view);
//        glm::mat4 model=glm::scale(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f,0.0f,0.0f)),glm::vec3(1.0f,1.0f,1.0f));
//        shader->setMat4("model", model);
//        shader->setMat3("normalMatrix", glm::mat3(glm::transpose(glm::inverse(model))));
//        shader->setVec3("viewPos", camera.Position);
//        shader->setVec3("light.position", lightPos);
//
////        nanosuit->Draw(*shader);
//        room->Draw(*shader);
////        nanosuit_reflection->Draw(*shader);
////        Paladin->Draw(*shader);
//
//        lightshader->use();
//        lightshader->setVec3("lightColor", specularColor);
//        lightshader->setMat4("projection", projection);
//        lightshader->setMat4("view", view);
//        glm::mat4 lightmodel=glm::scale(glm::translate(glm::mat4(1.0f), lightPos), glm::vec3(1.0f));
//        lightshader->setMat4("model", lightmodel);
//
//        glBindVertexArray(lightVAO);
//        glDrawArrays(GL_TRIANGLES,0,36);
//
//        glfwSwapBuffers(window);
//        glfwPollEvents();
//    }
//    delete shader;
////    delete nanosuit;
//    delete AlienSoldier;
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
//        firstMouse=false;
//        lastY=ypos;
//        lastX=xpos;
//    }
//
//    float xoffset=xpos-lastX;
//    float yoffset=lastY-ypos;
//    lastY=ypos;
//    lastX=xpos;
//
//    camera.ProcessMouseMovement(xoffset, yoffset);
//}
//
//void scroll_callback(GLFWwindow* window,double xoffset,double yoffset){
//    camera.ProcessMouseScroll(yoffset);
//}
