////
////  camera_0.cpp
////  OpenGLdemo
////
////  Created by SHERLOCK on 10.06.23.
////
//#define STB_IMAGE_IMPLEMENTATION
//#include "camera_0.hpp"
//
//void mouse_callback(GLFWwindow* window,double xpos,double ypos);
//void scroll_callback(GLFWwindow* window,double xoffset,double yoffset);
//
//const unsigned int SCR_WIDTH=800;
//const unsigned int SCR_HEIGHT=600;
//
//static GLfloat vertices[] = {
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
//};//渲染一个立方体，需要36个顶点
//
//static glm::vec3 cubePositions[]={
//    glm::vec3( 0.0f,  0.0f,  0.0f),
//    glm::vec3( 2.0f,  5.0f, -15.0f),
//    glm::vec3(-1.5f, -2.2f, -2.5f),
//    glm::vec3(-3.8f, -2.0f, -12.3f),
//    glm::vec3( 2.4f, -0.4f, -3.5f),
//    glm::vec3(-1.7f,  3.0f, -7.5f),
//    glm::vec3( 1.3f, -2.0f, -2.5f),
//    glm::vec3( 1.5f,  2.0f, -2.5f),
//    glm::vec3( 1.5f,  0.2f, -1.5f),
//    glm::vec3(-1.3f,  1.0f, -1.5f)
//};
//
//static unsigned int cubecount=sizeof(cubePositions)/sizeof(cubePositions[0]);
//
//
//Camera camera(glm::vec3(0.0f,0.0f,3.0f));
////构造函数共给定了四个默认参数，此处构造只指定第一个参数，其余全部是默认参数
//bool firstMouse=true;
////float yaw=-90.0f;
////float pitch=0.0f;
//float lastX=SCR_WIDTH/2.0f;
//float lastY=SCR_HEIGHT/2.0f;
////float fov=45.0f;
//
//FPSCamera fpscamera(glm::vec3(0.0f,0.0f,3.0f));
//
//static float deltaTime=0.0f;//该帧和上一帧时间差
//static float lastTime=0.0f;
//
////glm::vec3 cameraPos=glm::vec3(0.0f,0.0f,3.0f);
////glm::vec3 cameraFront=glm::vec3(0.0f,0.0f,-1.0f);
////glm::vec3 cameraUp=glm::vec3(0.0f,1.0f,0.0f);
////实际上相机方向是与指向物体方向相反的
//
//int camera_0(){
//    glfwInit();
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//#ifdef __APPLE__
//    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
//#endif
//
//    GLFWwindow *window=glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "learnOpenGL", NULL, NULL);
//    if(window==nullptr){
//        cout<<"fail to load GLFW window\n";
//        glfwTerminate();
//        return -1;
//    }
//    glfwMakeContextCurrent(window);
//    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);//注册帧缓冲回调函数
//
//    glfwSetCursorPosCallback(window, mouse_callback);//注册鼠标位置回调函数
//    glfwSetScrollCallback(window, scroll_callback);//注册鼠标滚轮回调函数
//
//    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);//当程序得到焦点时，隐藏鼠标
//
//    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
//        cout<<"fail to initialize GLAD\n";
//        return -1;
//    }
//
//    Shader *shader=new Shader("/Users/sherlock/Documents/Code/OpenGLdemo/OpenGLdemo/Entry/camera/camera_0.vs","/Users/sherlock/Documents/Code/OpenGLdemo/OpenGLdemo/Entry/camera/camera_0.fs");
//
//    unsigned int VBO,VAO;
//    glGenVertexArrays(1,&VAO);
//    glGenBuffers(1,&VBO);
//
//    glBindVertexArray(VAO);
//    glBindBuffer(GL_ARRAY_BUFFER,VBO);
//    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);
//
//    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,5*sizeof(GL_FLOAT),(void*)0);
//    glEnableVertexAttribArray(0);
//    glVertexAttribPointer(1,2,GL_FLOAT,GL_FALSE,5*sizeof(GL_FLOAT),(void*)(3*sizeof(GL_FLOAT)));
//    glEnableVertexAttribArray(1);
//
//    unsigned int texture[2];
//    glGenTextures(2,texture);
//
//    glBindTexture(GL_TEXTURE_2D,texture[0]);
//    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
//    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
//    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
//    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
//    int width,height,nrChannels;
//    unsigned char *data=stbi_load("/Users/sherlock/Documents/Code/OpenGLdemo/OpenGLdemo/resource/container.jpg", &width, &height, &nrChannels, 0);
//    if(data){
//        glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,width,height,0,GL_RGB,GL_UNSIGNED_BYTE,data);
//        glGenerateMipmap(GL_TEXTURE_2D);
//    }else{
//        cout<<"fail to load texture0\n";
//    }
//    stbi_image_free(data);
//
//    glBindTexture(GL_TEXTURE_2D,texture[1]);
//    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
//    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
//    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
//    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
//    data=stbi_load("/Users/sherlock/Documents/Code/OpenGLdemo/OpenGLdemo/resource/awesomeface.png", &width, &height, &nrChannels, 0);
//    if(data){
//        glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,width,height,0,GL_RGBA,GL_UNSIGNED_BYTE,data);
//        glGenerateMipmap(GL_TEXTURE_2D);
//    }else{
//        cout<<"Failed to load texture1\n";
//    }
//    stbi_image_free(data);
//
//    shader->use();
//    shader->setInt("texture1", 0);
//    shader->setInt("texture2", 1);
//
//    glActiveTexture(GL_TEXTURE0);
//    glBindTexture(GL_TEXTURE_2D,texture[0]);
//    glActiveTexture(GL_TEXTURE1);
//    glBindTexture(GL_TEXTURE_2D,texture[1]);
//
//    int updown;
//    float density=0.5;
//    //浮点数在内存中的第一位数据必须表示符号，而unsigned要求将第一位数据作为数据位，因此浮点数没有unsigned
//
//    glEnable(GL_DEPTH_TEST);
//
//    glm::mat4 projection=glm::perspective(glm::radians(fpscamera.Zoom), (float)SCR_WIDTH/(float)SCR_HEIGHT, 0.1f, 100.0f);
//    shader->setMat4("projection", projection);
//
//    while (!glfwWindowShouldClose(window)) {
//        float currentTime=static_cast<float>(glfwGetTime());
//        deltaTime=currentTime-lastTime;
//        lastTime=currentTime;
//
//        processInput(window);
//        updown=processInputUpDown(window);
//        density+=updown*0.01f;
//        if(density>1.0f){
//            density=1.0f;
//        }else if(density<0.0f){
//            density=0.0f;
//        }
//        processCameraWSAD(window, fpscamera, deltaTime);
////        glm::mat4 view=glm::lookAt(camera.Position, camera.Position+camera.Front, camera.Up);
//        glm::mat4 view=fpscamera.GetViewMatrix();
//        shader->setMat4("view", view);
//
//        glClearColor(0.2f,0.3f,0.3f,1.0f);
//        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
//
//        shader->setFloat("density", density);
//
//        //相机自动旋转
////        float radius=10.0f;
////        float camX=static_cast<float>(sin(glfwGetTime())*radius);
////        float camZ=static_cast<float>(cos(glfwGetTime())*radius);
////        glm::mat4 view=glm::lookAt(glm::vec3(camX,0.0f,camZ), glm::vec3(0.0f,0.0f,0.0f), glm::vec3(0.0f,1.0f,0.0f));
//        //lookAt参数：位置，目标，上向量
//
//        glBindVertexArray(VAO);
//        for(unsigned int i=0;i<cubecount;i++){
//            glm::mat model=glm::translate(glm::mat4(1.0f), cubePositions[i]);
//            float angle;
//            if(i==0){
//                angle=50.0f;
//                model=glm::rotate(model, (float)glfwGetTime()*glm::radians(angle), glm::vec3(0.0f,0.0f,1.0f));
//                //若使用位置作为旋转轴，则第一个立方体的旋转轴为原点，这将导致其不被渲染
//            }else{
//                angle=20.0f*i;
//                model=glm::rotate(model, (float)glfwGetTime()*glm::radians(angle), cubePositions[i]);
//            }
//            shader->setMat4("model", model);
//            glDrawArrays(GL_TRIANGLES,0,36);
//        }
//
//        glfwSwapBuffers(window);
//        glfwPollEvents();
//    }
//    glDeleteBuffers(1,&VBO);
//    glDeleteVertexArrays(1,&VAO);
//    delete shader;
//
//    glfwTerminate();
//    return 0;
//}
//
////void framebuffer_size_callback(GLFWwindow* window, int width,int height){
////    glViewport(0,0,width,height);
////}
//
///**
// *@param xposIn 当前鼠标位置x值
// *@param yposIn 当前鼠标位置y值
// */
//void mouse_callback(GLFWwindow* window,double xposIn,double yposIn){
//    float xpos = static_cast<float>(xposIn);
//    float ypos = static_cast<float>(yposIn);
//
//    if (firstMouse)
//    {
//        lastX = xpos;
//        lastY = ypos;
//        firstMouse = false;
//    }
//
//    float xoffset = xpos - lastX;
//    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top
//    lastX = xpos;
//    lastY = ypos;
//
//    fpscamera.ProcessMouseMovement(xoffset, yoffset);
//
////    float sensitivity = 0.1f; // change this value to your liking
////    xoffset *= sensitivity;
////    yoffset *= sensitivity;
////
////    yaw += xoffset;
////    pitch += yoffset;
////
////    // make sure that when pitch is out of bounds, screen doesn't get flipped
////    if (pitch > 89.0f)
////        pitch = 89.0f;
////    if (pitch < -89.0f)
////        pitch = -89.0f;
////
////    glm::vec3 front;
////    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
////    front.y = sin(glm::radians(pitch));
////    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
////    cameraFront = glm::normalize(front);
//}
//
//void scroll_callback(GLFWwindow* window,double xoffset,double yoffset){
//    fpscamera.ProcessMouseScroll(static_cast<float>(yoffset));
////    if(fov>=1.0f&&fov<=45.0f)
////        fov-=yoffset;
////    if(fov<=1.0f)
////        fov=1.0f;
////    if(fov>=45.0f)
////        fov=45.0f;
//
//}
