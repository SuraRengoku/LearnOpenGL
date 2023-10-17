//
//  deferredshading.cpp
//  OpenGLdemo
//
//  Created by SHERLOCK on 15.10.23.
//

// 延迟渲染法的一个缺点就是不能进行混合blending

#include "deferredshading.hpp"
#define Default_Width 1200;
#define Default_Height 800;

static unsigned const int SCR_WIDTH=Default_Width;
static unsigned const int SCR_HEIGHT=Default_Height;

Camera camera(glm::vec3(0.0f,0.0f,5.0f));
bool firstMouse=true;
float lastX=SCR_WIDTH/2.0f;
float lastY=SCR_HEIGHT/2.0f;

static float deltaTime=0.0f;
static float lastTime=0.0f;
//
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void lighting_control(GLFWwindow* window);
//
static bool hdr_=true;
static bool hdrKeyPressed=false;
static bool Reinhard=true;
static bool ReinhardPressed=false;
static bool bloom_=true;
static bool bloomPressed=false;
static float exposure=1.0f;
//
float vertices[] = {
    // back face
    -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f, // bottom-left
     1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f, // top-right
     1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 1.0f, 0.0f, // bottom-right
     1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f, // top-right
    -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f, // bottom-left
    -1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 0.0f, 1.0f, // top-left
    // front face
    -1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 0.0f, // bottom-left
     1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, 0.0f, // bottom-right
     1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, 1.0f, // top-right
     1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, 1.0f, // top-right
    -1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 1.0f, // top-left
    -1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 0.0f, // bottom-left
    // left face
    -1.0f,  1.0f,  1.0f, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-right
    -1.0f,  1.0f, -1.0f, -1.0f,  0.0f,  0.0f, 1.0f, 1.0f, // top-left
    -1.0f, -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-left
    -1.0f, -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-left
    -1.0f, -1.0f,  1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 0.0f, // bottom-right
    -1.0f,  1.0f,  1.0f, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-right
    // right face
     1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-left
     1.0f, -1.0f, -1.0f,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-right
     1.0f,  1.0f, -1.0f,  1.0f,  0.0f,  0.0f, 1.0f, 1.0f, // top-right
     1.0f, -1.0f, -1.0f,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-right
     1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-left
     1.0f, -1.0f,  1.0f,  1.0f,  0.0f,  0.0f, 0.0f, 0.0f, // bottom-left
    // bottom face
    -1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f, // top-right
     1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f, 1.0f, 1.0f, // top-left
     1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f, // bottom-left
     1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f, // bottom-left
    -1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f, 0.0f, 0.0f, // bottom-right
    -1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f, // top-right
    // top face
    -1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f, // top-left
     1.0f,  1.0f , 1.0f,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f, // bottom-right
     1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f, 1.0f, 1.0f, // top-right
     1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f, // bottom-right
    -1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f, // top-left
    -1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f, 0.0f, 0.0f  // bottom-left
};
auto loadCubeBuffer()->GLuint{
    GLuint cubeVAO,cubeVBO;
    glGenVertexArrays(1,&cubeVAO);
    glGenBuffers(1,&cubeVBO);
    glBindVertexArray(cubeVAO);
    glBindBuffer(GL_ARRAY_BUFFER,cubeVBO);
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),&vertices,GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,8*sizeof(GLfloat),(GLvoid*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,8*sizeof(GLfloat),(GLvoid*)(3*sizeof(GLfloat)));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2,2,GL_FLOAT,GL_FALSE,8*sizeof(GLfloat),(GLvoid*)(6*sizeof(GLfloat)));
    glBindVertexArray(0);
    return cubeVAO;
}
void renderCube(GLuint cubeVAO){
    glBindVertexArray(cubeVAO);
    glDrawArrays(GL_TRIANGLES,0,36);
    glBindVertexArray(0);
}

float quadVertices[] = {
    // Positions        // Texture Coords
    -1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
    -1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
    1.0f, 1.0f, 0.0f, 1.0f, 1.0f,
    1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
};
auto loadQuadBuffer()->GLuint{
    GLuint quadVAO,quadVBO;
    glGenVertexArrays(1,&quadVAO);
    glGenBuffers(1,&quadVBO);
    glBindVertexArray(quadVAO);
    glBindBuffer(GL_ARRAY_BUFFER,quadVBO);
    glBufferData(GL_ARRAY_BUFFER,sizeof(quadVertices),&quadVertices,GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,5*sizeof(GLfloat),(GLvoid*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1,2,GL_FLOAT,GL_FALSE,5*sizeof(GLfloat),(GLvoid*)(3*sizeof(GLfloat)));
    return quadVAO;
}
void renderQuad(GLuint quadVAO){
    glBindVertexArray(quadVAO);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glBindVertexArray(0);
}

int deferredshading()
{
    GLFWwindow* window=glfw_Init(SCR_WIDTH, SCR_HEIGHT, mouse_callback, scroll_callback);
    // tell stb_image.h to flip loaded texture's on the y-axis (before loading model).
    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);

    // build and compile shaders
    // -------------------------
    Shader *gBuffershader=new Shader("/Users/sherlock/Documents/Code/OpenGLdemo/OpenGLdemo/AdvancedLighting/DeferredShading/gBuffershader.vs", "/Users/sherlock/Documents/Code/OpenGLdemo/OpenGLdemo/AdvancedLighting/DeferredShading/gBuffershader.fs");
    Shader *lightPassshader=new Shader("/Users/sherlock/Documents/Code/OpenGLdemo/OpenGLdemo/AdvancedLighting/DeferredShading/lightPassshader.vs", "/Users/sherlock/Documents/Code/OpenGLdemo/OpenGLdemo/AdvancedLighting/DeferredShading/lightPassshader.fs");
    Shader *lightshader=new Shader ("/Users/sherlock/Documents/Code/OpenGLdemo/OpenGLdemo/AdvancedLighting/DeferredShading/lightboxshader.vs", "/Users/sherlock/Documents/Code/OpenGLdemo/OpenGLdemo/AdvancedLighting/DeferredShading/lightboxshader.fs");
    Shader *debugshader=new Shader("/Users/sherlock/Documents/Code/OpenGLdemo/OpenGLdemo/AdvancedLighting/DeferredShading/lightPassshader.vs","/Users/sherlock/Documents/Code/OpenGLdemo/OpenGLdemo/AdvancedLighting/DeferredShading/debug.fs");
    Shader *debugspecshader=new Shader("/Users/sherlock/Documents/Code/OpenGLdemo/OpenGLdemo/AdvancedLighting/DeferredShading/lightPassshader.vs","/Users/sherlock/Documents/Code/OpenGLdemo/OpenGLdemo/AdvancedLighting/DeferredShading/debugspec.fs");

    // load models
    // -----------
    Model *backpack=new Model("/Users/sherlock/Documents/Code/OpenGLdemo/OpenGLdemo/resource/models/nanosuit/nanosuit.obj");
    std::vector<glm::vec3> objectPositions;
    objectPositions.push_back(glm::vec3(-3.0, -3.0, -3.0));
    objectPositions.push_back(glm::vec3(0.0, -3.0, -3.0));
    objectPositions.push_back(glm::vec3(3.0, -3.0, -3.0));
    objectPositions.push_back(glm::vec3(-3.0, -3.0, 0.0));
    objectPositions.push_back(glm::vec3(0.0, -3.0, 0.0));
    objectPositions.push_back(glm::vec3(3.0, -3.0, 0.0));
    objectPositions.push_back(glm::vec3(-3.0, -3.0, 3.0));
    objectPositions.push_back(glm::vec3(0.0, -3.0, 3.0));
    objectPositions.push_back(glm::vec3(3.0, -3.0, 3.0));

    const GLuint NR_LIGHTS=32;
    std::vector<glm::vec3> lightPositions;
    std::vector<glm::vec3> lightColors;
    srand(13);
    for(GLuint i=0;i<NR_LIGHTS;i++){
        GLfloat xPos=((rand()%100)/100.0f)*6.0f-3.0f;
        GLfloat yPos=((rand()%100)/100.0f)*6.0f-4.0f;
        GLfloat zPos=((rand()%100)/100.0f)*6.0f-3.0f;
        lightPositions.push_back(glm::vec3(xPos,yPos,zPos));
        GLfloat rColor=((rand()%100)/200.0f)+0.5f; // Between 0.5 and 1.0
        GLfloat gColor=((rand()%100)/200.0f)+0.5f; // Between 0.5 and 1.0
        GLfloat bColor=((rand()%100)/200.0f)+0.5f; // Between 0.5 and 1.0
        lightColors.push_back(glm::vec3(rColor,gColor,bColor));
    }

    // configure g-buffer framebuffer
    // ------------------------------
    unsigned int gBuffer;
    glGenFramebuffers(1, &gBuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, gBuffer);
    unsigned int gPosition, gNormal, gAlbedoSpec;
    // position color buffer
    glGenTextures(1, &gPosition);
    glBindTexture(GL_TEXTURE_2D, gPosition);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, SCR_WIDTH*2, SCR_HEIGHT*2, 0, GL_RGBA, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, gPosition, 0);
    // normal color buffer
    glGenTextures(1, &gNormal);
    glBindTexture(GL_TEXTURE_2D, gNormal);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, SCR_WIDTH*2, SCR_HEIGHT*2, 0, GL_RGBA, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, gNormal, 0);
    // color + specular color buffer
    glGenTextures(1, &gAlbedoSpec);
    glBindTexture(GL_TEXTURE_2D, gAlbedoSpec);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, SCR_WIDTH*2, SCR_HEIGHT*2, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT2, GL_TEXTURE_2D, gAlbedoSpec, 0);
    // tell OpenGL which color attachments we'll use (of this framebuffer) for rendering
    unsigned int attachments[3] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2 };
    glDrawBuffers(3, attachments);//我们需要显式告诉OpenGL需要使用glDrawBuffers渲染的是和GBuffer关联的哪个颜色缓冲

    // create and attach depth buffer (renderbuffer)
    unsigned int rboDepth;
    glGenRenderbuffers(1, &rboDepth);
    glBindRenderbuffer(GL_RENDERBUFFER, rboDepth);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, SCR_WIDTH*2, SCR_HEIGHT*2);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, rboDepth);
    // finally check if framebuffer is complete
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        std::cout << "Framebuffer not complete!" << std::endl;
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    GLuint cubeVAO=loadCubeBuffer();
    GLuint quadVAO=loadQuadBuffer();
    
    gBuffershader->use();
    gBuffershader->setInt("texture_diffuse1", 0);
    gBuffershader->setInt("texture_specular1", 1);
    lightPassshader->use();
    lightPassshader->setInt("gPosition", 0);
    lightPassshader->setInt("gNormal", 1);
    lightPassshader->setInt("gAlbedoSpec", 2);
    debugshader->use();
    debugshader->setInt("debugtexture", 0);
    debugspecshader->use();
    debugspecshader->setInt("debugtexture", 0);

    //imgui
    const char *glsl_version="#version 330 core";
    ImGui::CreateContext();
    ImGuiIO& io=ImGui::GetIO();
    (void)io;
    io.ConfigFlags|=ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags|=ImGuiConfigFlags_NavEnableGamepad;

    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);
    bool show_demo_window=false;
    bool show_another_window=false;
    ImVec4 clear_color=ImVec4(0.45f,0.55f,0.60f,1.00f);
    
    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        auto currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastTime;
        lastTime = currentFrame;

        processInput(window, mouse_callback, scroll_callback);
        processCameraWSAD(window, camera, deltaTime);
        lighting_control(window);
        
        glEnable(GL_DEPTH_TEST);

        // render
        // ------
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        if(show_demo_window)
            ImGui::ShowDemoWindow(&show_demo_window);
        ImGui::Begin("Tool Panel");
        ImGui::Checkbox("Demo Window", &show_demo_window);
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)",1000.0f/io.Framerate,io.Framerate);
        ImGui::End();
        if(show_another_window){
            ImGui::Begin("Another Window",&show_another_window);
            ImGui::Text("Hello from another window!");
            if(ImGui::Button("Close Me"))
                show_another_window=false;
            ImGui::End();
        }
        
        // 1. geometry pass: render scene's geometry/color data into gbuffer
        // -----------------------------------------------------------------
        glBindFramebuffer(GL_FRAMEBUFFER, gBuffer);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        glm::mat4 view = camera.GetViewMatrix();
        glm::mat4 model = glm::mat4(1.0f);
        gBuffershader->use();
        gBuffershader->setMat4("projection", projection);
        gBuffershader->setMat4("view", view);
        for (unsigned int i = 0; i < objectPositions.size(); i++){
            model = glm::mat4(1.0f);
            model = glm::translate(model, objectPositions[i]);
            model = glm::scale(model, glm::vec3(0.25f));
            gBuffershader->setMat4("model", model);
            gBuffershader->setMat3("normalMatrix",glm::transpose(glm::inverse(glm::mat3(model))));
            backpack->Draw(*gBuffershader);
        }

        // 2. lighting pass: calculate lighting by iterating over a screen filled quad pixel-by-pixel using the gbuffer's content.
        // -----------------------------------------------------------------------------------------------------------------------
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        lightPassshader->use();
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, gPosition);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, gNormal);
        glActiveTexture(GL_TEXTURE2);
        glBindTexture(GL_TEXTURE_2D, gAlbedoSpec);
        // send light relevant uniforms
        for (unsigned int i = 0; i < lightPositions.size(); i++)
        {
            lightPassshader->setVec3("lights[" + std::to_string(i) + "].Position", lightPositions[i]);
            lightPassshader->setVec3("lights[" + std::to_string(i) + "].Color", lightColors[i]);
            // update attenuation parameters and calculate radius
            const float linear = 0.7f;
            const float quadratic = 1.8f;
            lightPassshader->setFloat("lights[" + std::to_string(i) + "].Linear", linear);
            lightPassshader->setFloat("lights[" + std::to_string(i) + "].Quadratic", quadratic);
        }
        lightPassshader->setVec3("viewPos", camera.Position);
        renderQuad(quadVAO);

        // 2.5. copy content of geometry's depth buffer to default framebuffer's depth buffer
        // ----------------------------------------------------------------------------------
        glBindFramebuffer(GL_READ_FRAMEBUFFER, gBuffer);
        glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0); // write to default framebuffer
        // blit to default framebuffer. Note that this may or may not work as the internal formats of both the FBO and default framebuffer have to match.
        // the internal formats are implementation defined. This works on all of my systems, but if it doesn't on yours you'll likely have to write to the
        // depth buffer in another shader stage (or somehow see to match the default framebuffer's internal format with the FBO's internal format).
        glBlitFramebuffer(0, 0, SCR_WIDTH*2, SCR_HEIGHT*2, 0, 0, SCR_WIDTH*2, SCR_HEIGHT*2, GL_DEPTH_BUFFER_BIT, GL_NEAREST);
        glBindFramebuffer(GL_FRAMEBUFFER, 0);

        // 3. render lights on top of scene
        // --------------------------------
        lightshader->use();
        lightshader->setMat4("projection", projection);
        lightshader->setMat4("view", view);
        for (unsigned int i = 0; i < lightPositions.size(); i++){
            model = glm::mat4(1.0f);
            model = glm::translate(model, lightPositions[i]);
            model = glm::scale(model, glm::vec3(0.125f));
            lightshader->setMat4("model", model);
            lightshader->setVec3("lightColor", lightColors[i]);
            renderCube(cubeVAO);
        }
        
        //debug
        glDisable(GL_DEPTH_TEST);
        glBindFramebuffer(GL_FRAMEBUFFER,0);
        debugshader->use();
        glViewport(0,0,(SCR_WIDTH*2)/4,(SCR_HEIGHT*2)/4);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D,gPosition);
        renderQuad(quadVAO);
        glViewport(0,(SCR_HEIGHT*2)/4,(SCR_WIDTH*2)/4,(SCR_HEIGHT*2)/4);
        glBindTexture(GL_TEXTURE_2D,gNormal);
        renderQuad(quadVAO);
        glViewport(0,(SCR_HEIGHT*2)/2,(SCR_WIDTH*2)/4,(SCR_HEIGHT*2)/4);
        glBindTexture(GL_TEXTURE_2D,gAlbedoSpec);
        renderQuad(quadVAO);
        debugspecshader->use();
        glViewport((SCR_WIDTH*2)/4,0,(SCR_WIDTH*2)/4,(SCR_HEIGHT*2)/4);
        glBindTexture(GL_TEXTURE_2D,gAlbedoSpec);
        renderQuad(quadVAO);

        glViewport(0,0,SCR_WIDTH*2,SCR_HEIGHT*2);
        
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    delete gBuffershader;
    gBuffershader=nullptr;
    delete lightPassshader;
    lightPassshader=nullptr;
    delete debugshader;
    debugshader=nullptr;

    glfwTerminate();
    return 0;
}

void mouse_callback(GLFWwindow* window, double xposIn, double yposIn){
    float xpos=static_cast<float>(xposIn);
    float ypos=static_cast<float>(yposIn);
    if(firstMouse){
        lastX=xpos;
        lastY=ypos;
        firstMouse=false;
    }
    float xoffset=xpos-lastX;
    float yoffset=lastY-ypos;
    lastY=ypos;
    lastX=xpos;
    camera.ProcessMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset){
    camera.ProcessMouseScroll(yoffset);
}

void lighting_control(GLFWwindow* window){
    if(glfwGetKey(window,GLFW_KEY_SPACE)==GLFW_PRESS&&!hdrKeyPressed){
        hdr_=!hdr_;
        hdrKeyPressed=true;//保证每次按空格只会生效一次
    }
    if(glfwGetKey(window, GLFW_KEY_SPACE)==GLFW_RELEASE)
        hdrKeyPressed=false;
    if(glfwGetKey(window, GLFW_KEY_H)==GLFW_PRESS&&!ReinhardPressed){
        Reinhard=!Reinhard;
        ReinhardPressed=true;
    }
    if(glfwGetKey(window, GLFW_KEY_H)==GLFW_RELEASE)
        ReinhardPressed=false;
    if(glfwGetKey(window, GLFW_KEY_B)==GLFW_PRESS&&!bloomPressed){
        bloom_=!bloom_;
        bloomPressed=true;
    }
    if(glfwGetKey(window, GLFW_KEY_B)==GLFW_RELEASE)
        bloomPressed=false;
    if(glfwGetKey(window,GLFW_KEY_Q)==GLFW_PRESS){
        if(exposure>0.0f)
            exposure-=0.01f;
        else
            exposure=0.0f;
    }else if(glfwGetKey(window, GLFW_KEY_E)==GLFW_PRESS)
        exposure+=0.01f;
}
