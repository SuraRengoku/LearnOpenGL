//
//  stenciltest.cpp
//  OpenGLdemo
//
//  Created by SHERLOCK on 05.09.23.
//

#include "stenciltest.hpp"

static unsigned const int SCR_WIDTH=1200;
static unsigned const int SCR_HEIGHT=800;

Camera camera(glm::vec3(0.0f,0.0f,6.0f));
bool firstMouse=true;
float lastX=SCR_WIDTH/2.0f;
float lastY=SCR_HEIGHT/2.0f;

static float deltaTime=0.0f;
static float lastTime=0.0f;

static float cubeVertices[] = {
    // positions          // texture Coords
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f

};
static float planeVertices[] = {
    // positions          // texture Coords (note we set these higher than 1 (together with GL_REPEAT as texture wrapping mode). this will cause the floor texture to repeat)
     5.0f, -0.5f,  5.0f,  1.0f, 0.0f,
    -5.0f, -0.5f,  5.0f,  0.0f, 0.0f,
    -5.0f, -0.5f, -5.0f,  0.0f, 1.0f,

     5.0f, -0.5f,  5.0f,  1.0f, 0.0f,
    -5.0f, -0.5f, -5.0f,  0.0f, 1.0f,
     5.0f, -0.5f, -5.0f,  1.0f, 1.0f
};

void mouse_callback(GLFWwindow* window, double xposIn, double yposIn);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
//这两个回调函数在glfw.h中被实现，原型为
//typedef void (* GLFWcursorposfun)(GLFWwindow* window, double xpos, double ypos);
//typedef void (* GLFWscrollfun)(GLFWwindow* window, double xoffset, double yoffset);
//如果需要自定义回调函数的行为，可以在回调函数内部处理函数，但参数的类型和数量必须与库函数的要求相匹配

int stenciltest(){
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);//设置上下文主要版本号
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);//次要版本号
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //GLFW_OPENGL_PROFILE宏用于指定OpenGL上下文的配置文件类型
    //GLFW_OPENGL_CORE_PROFILE宏用于表示使用核心配置文件
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    //启用向前兼容模式，允许在较新的版本中使用较旧的特性
#endif

    GLFWwindow* window=glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "learnOpenGL", NULL, NULL);
    try{
        if(window==nullptr)
            throw std::runtime_error("window generated unsuccessfully");
    }catch(std::runtime_error err){
        cerr<<err.what()<<"\n";
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    try{
        if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
            throw std::runtime_error("fail to initialize GLAD");
    }catch(std::runtime_error err){
        cerr<<err.what()<<"\n";
        glfwTerminate();
        return -1;
    }


    Shader *shader=new Shader("/Users/sherlock/Documents/Code/OpenGLdemo/OpenGLdemo/Advanced/StencilTest/stenciltest.vs","/Users/sherlock/Documents/Code/OpenGLdemo/OpenGLdemo/Advanced/StencilTest/stenciltest.fs");
    Shader *Frame=new Shader("/Users/sherlock/Documents/Code/OpenGLdemo/OpenGLdemo/Advanced/StencilTest/stenciltest.vs","/Users/sherlock/Documents/Code/OpenGLdemo/OpenGLdemo/Advanced/StencilTest/shaderSingleColor.fs");

    unsigned marbleTexture=loadTexture("/Users/sherlock/Documents/Code/OpenGLdemo/OpenGLdemo/resource/marble.jpg");
    unsigned metalTexture=loadTexture("/Users/sherlock/Documents/Code/OpenGLdemo/OpenGLdemo/resource/metal.png");

    unsigned int cubeVAO,cubeVBO,planeVAO,planeVBO;
    glGenVertexArrays(1,&cubeVAO);
    glGenVertexArrays(1,&planeVAO);
    glGenBuffers(1,&cubeVBO);
    glGenBuffers(1,&planeVBO);

    glBindVertexArray(cubeVAO);
    glBindBuffer(GL_ARRAY_BUFFER,cubeVBO);
    glBufferData(GL_ARRAY_BUFFER,sizeof(cubeVertices),&cubeVertices,GL_STATIC_DRAW);
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,5*sizeof(GL_FLOAT),(void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1,2,GL_FLOAT,GL_FALSE,5*sizeof(GL_FLOAT),(void*)(3*sizeof(GL_FLOAT)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(planeVAO);
    glBindBuffer(GL_ARRAY_BUFFER,planeVBO);
    glBufferData(GL_ARRAY_BUFFER,sizeof(planeVertices),&planeVertices,GL_STATIC_DRAW);
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,5*sizeof(GL_FLOAT),(void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1,2,GL_FLOAT,GL_FALSE,5*sizeof(GL_FLOAT),(void*)(3*sizeof(GL_FLOAT)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);

    shader->use();
    shader->setInt("texture1", 0);

    //global configuration
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glEnable(GL_STENCIL_TEST);
    /**
     * @param func 设置模版测试函数，可用选项为：GL_NEVER, GL_LESS, GL_LEQUAL, GL_GREATER, GL_GEQUAL, GL_EQUAL, GL_NOTEQUAL, GLALWAYS
     * @param ref 设置了模版测试的参考值
     * @param mask 设置一个掩码，它将会与参考值和储存的模版值在测试比较他们之间进行与(AND)运算。初始情况下所有位都为1
     */
    glStencilFunc(GL_NOTEQUAL,1,0xFF);
    /**
     * @param GLenum sfail 模版测试失败时采取的行为
     * @param GLenum dpfail 模版测试通过，但深度测试失败时采取的行为
     * @param GLenum dppass 模版测试和深度测试都通过时采取的行为
     * 默认情况下三个参数都是GL_KEEP
     */
    glStencilOp(GL_KEEP,GL_REPLACE,GL_REPLACE);//测试失败或通过时的行为
    //GL_KEEP 保持当前存储的模版值
    //GL_ZERO 将模版值设置为0
    //GL_REPLACE 将模版值设置为glfwStencilFunc函数设置的ref值
    //GL_INCR 如果模版值小于最大值将模版值加1
    //GL_INCR_WRAP 与GL_INCR一样，但如果模版值超过了最大值则归零
    //GL_DECR 如果模版值大于小于最小值则将模版值减1
    //GL_DECR_WRAP 与GL_DECR一样，但如果模版值小于0则将其设置为最大值
    //GL_INVERT 安慰反转当前的模版桓冲值

    while(!glfwWindowShouldClose(window)){
        float currentTime=static_cast<float>(glfwGetTime());
        deltaTime=currentTime-lastTime;
        lastTime=currentTime;

        processInput(window);
        processCameraWSAD(window, camera, deltaTime);

        glClearColor(0.1f,0.1f,0.1f,1.0f);
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT|GL_STENCIL_BUFFER_BIT);


        glm::mat4 view=camera.GetViewMatrix();
        glm::mat4 projection=glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH/(float)SCR_HEIGHT, 0.1f, 100.0f);

        Frame->use();
        Frame->setMat4("view", view);
        Frame->setMat4("projection", projection);

        shader->use();//在渲染之前，一定要指定着色器
        shader->setMat4("view", view);
        shader->setMat4("projection", projection);


        glStencilMask(0x00);//在渲染地板时，禁用模版缓冲写入
        glBindVertexArray(planeVAO);
        glBindTexture(GL_TEXTURE_2D,metalTexture);
        shader->setMat4("model", glm::mat4(1.0f));
        glDrawArrays(GL_TRIANGLES,0,6);
        glBindVertexArray(0);

        glStencilFunc(GL_ALWAYS,1,0xFF);
        glStencilMask(0xFF);//在渲染箱子时，启用模版缓冲写入
        glBindVertexArray(cubeVAO);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D,marbleTexture);
        shader->setMat4("model", glm::translate(glm::mat4(1.0f), glm::vec3(-1.0f,-0.25f,-1.0f)));
        glDrawArrays(GL_TRIANGLES,0,36);

        glStencilFunc(GL_NOTEQUAL,1,0xFF);
        glStencilMask(0x00);//在渲染轮廓时，禁用模版缓冲写入
//        glDisable(GL_DEPTH_TEST);//防止深度信息干扰模版测试
        Frame->use();
        float scale=1.03f;
        glBindVertexArray(cubeVAO);
        Frame->setMat4("model", glm::scale(glm::translate(glm::mat4(1.0f), glm::vec3(-1.0f,-0.25f,-1.0f)), glm::vec3(scale,scale,scale)));
        glDrawArrays(GL_TRIANGLES,0,36);
        glStencilFunc(GL_ALWAYS,1,0xFF);
        glStencilMask(0xFF);
        glClear(GL_STENCIL_BUFFER_BIT);

        glStencilFunc(GL_ALWAYS,1,0xFF);
        glStencilMask(0xFF);//在渲染箱子时，启用模版缓冲写入
        glBindVertexArray(cubeVAO);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D,marbleTexture);
        glEnable(GL_DEPTH_TEST);
        shader->use();
        shader->setMat4("model", glm::translate(glm::mat4(1.0f), glm::vec3(2.0f,-0.15f,0.0f)));
        glDrawArrays(GL_TRIANGLES,0,36);

        glStencilFunc(GL_NOTEQUAL,1,0xFF);
        glStencilMask(0x00);//在渲染轮廓时，禁用模版缓冲写入
//        glDisable(GL_DEPTH_TEST);//防止深度信息干扰模版测试
        Frame->use();
        Frame->setMat4("model", glm::scale(glm::translate(glm::mat4(1.0f), glm::vec3(2.0f,-0.15f,0.0f)), glm::vec3(scale,scale,scale)));
        glDrawArrays(GL_TRIANGLES,0,36);
        glStencilFunc(GL_ALWAYS,1,0xFF);
        glStencilMask(0xFF);
        glClear(GL_STENCIL_BUFFER_BIT);

        glStencilFunc(GL_ALWAYS,1,0xFF);
        glStencilMask(0xFF);//在渲染箱子时，启用模版缓冲写入
        glBindVertexArray(cubeVAO);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D,marbleTexture);
        glEnable(GL_DEPTH_TEST);
        shader->use();
        shader->setMat4("model", glm::translate(glm::mat4(1.0f), glm::vec3(2.0f,-0.5f,-3.0f)));
        glDrawArrays(GL_TRIANGLES,0,36);

        glStencilFunc(GL_NOTEQUAL,1,0xFF);
        glStencilMask(0x00);//在渲染轮廓时，禁用模版缓冲写入
//        glDisable(GL_DEPTH_TEST);//防止深度信息干扰模版测试
        Frame->use();
        Frame->setMat4("model", glm::scale(glm::translate(glm::mat4(1.0f), glm::vec3(2.0f,-0.5f,-3.0f)),
            glm::vec3(scale,scale,scale)));
        glDrawArrays(GL_TRIANGLES,0,36);
        glStencilFunc(GL_ALWAYS,1,0xFF);
        glStencilMask(0xFF);
        glClear(GL_STENCIL_BUFFER_BIT);

        glStencilFunc(GL_ALWAYS,1,0xFF);
        glStencilMask(0xFF);//在渲染箱子时，启用模版缓冲写入
        glBindVertexArray(cubeVAO);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D,marbleTexture);
        glEnable(GL_DEPTH_TEST);
        shader->use();
        shader->setMat4("model", glm::translate(glm::mat4(1.0f), glm::vec3(2.5f,-1.5f,-2.15f)));
        glDrawArrays(GL_TRIANGLES,0,36);

        glStencilFunc(GL_NOTEQUAL,1,0xFF);
        glStencilMask(0x00);//在渲染轮廓时，禁用模版缓冲写入
//        glDisable(GL_DEPTH_TEST);//防止深度信息干扰模版测试
        Frame->use();
        Frame->setMat4("model", glm::scale(glm::translate(glm::mat4(1.0f), glm::vec3(2.5f,-1.5f,-2.15f)),
            glm::vec3(scale,scale,scale)));
        glDrawArrays(GL_TRIANGLES,0,36);
        glStencilFunc(GL_ALWAYS,1,0xFF);
        glStencilMask(0xFF);
        glClear(GL_STENCIL_BUFFER_BIT);


        glBindVertexArray(0);
        glStencilMask(0xFF);//将模版缓冲的写入行为恢复正常
        //如果不及时清除箱子的模版带来的影响，其大范围的移动会导致后续的渲染始终无法通过
        //需要注意的是，glStencilMask(0x00)不止会阻止缓冲模版的写入，还会阻止其清空(glClear(GL_STENCIL_BUFFER_BIT))缓冲
        //因此在这里需要将其恢复为可写入状态
        glStencilFunc(GL_ALWAYS,0,0xFF);
        glEnable(GL_DEPTH_TEST);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glDeleteVertexArrays(1,&cubeVAO);
    glDeleteVertexArrays(1,&planeVAO);
    glDeleteBuffers(1,&cubeVBO);
    glDeleteBuffers(1,&planeVBO);
    delete shader;
    delete Frame;

    glfwTerminate();
    return 0;
}

void mouse_callback(GLFWwindow* window, double xposIn, double yposIn){
    float xpos=static_cast<float>(xposIn);
    float ypos=static_cast<float>(yposIn);

    if(firstMouse){
        firstMouse=false;
        lastX=xpos;
        lastY=ypos;
    }

    float xoffset=xpos-lastX;
    float yoffset=lastY-ypos;
    lastX=xpos;
    lastY=ypos;
    camera.ProcessMouseMovement(xoffset, yoffset);

}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset){
    camera.ProcessMouseScroll(yoffset);
}

