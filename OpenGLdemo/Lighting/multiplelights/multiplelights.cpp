//
//  multiplelights.cpp
//  OpenGLdemo
//
//  Created by SHERLOCK on 16.07.23.
//

#include "multiplelights.hpp"

static unsigned const int SCR_WIDTH=1200;
static unsigned const int SCR_HEIGHT=800;

void mouse_callback(GLFWwindow* window,double xposIn,double yposIn);
void scroll_callback(GLFWwindow* window,double xoffset,double yoffset);

Camera camera(glm::vec3(0.0f,0.0f,6.0f));
bool firstMouse=true;
float lastX=SCR_WIDTH/2.0f;
float lastY=SCR_HEIGHT/2.0f;

static float deltaTime=0.0f;
static float lastTime=0.0f;

static glm::vec3 lightPos(1.2f,1.0f,2.0f);

static GLfloat vertices[]={
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
    -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
     0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
};

static glm::vec3 cubePosition[]={
    glm::vec3( 0.0f,  0.0f,  0.0f),
    glm::vec3( 2.0f,  5.0f, -15.0f),
    glm::vec3(-1.5f, -2.2f, -2.5f),
    glm::vec3(-3.8f, -2.0f, -12.3f),
    glm::vec3( 2.4f, -0.4f, -3.5f),
    glm::vec3(-1.7f,  3.0f, -7.5f),
    glm::vec3( 1.3f, -2.0f, -2.5f),
    glm::vec3( 1.5f,  2.0f, -2.5f),
    glm::vec3( 1.5f,  0.2f, -1.5f),
    glm::vec3(-1.3f,  1.0f, -1.5f)
};

static glm::vec3  pointLightPositions[]={
    glm::vec3( 0.7f,  0.2f,  2.0f),
    glm::vec3( 2.3f, -3.3f, -4.0f),
    glm::vec3(-4.0f,  2.0f, -12.0f),
    glm::vec3( 0.0f,  0.0f, -3.0f)
};

int multiplelights(){
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    GLFWwindow *window=glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "leanOpenGL", NULL, NULL);
    if(window==nullptr){
        cout<<"fail to load GLFW window\n";
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        cout<<"fail to initialize GLAD\n";
        glfwTerminate();
        return -1;
    }

    glEnable(GL_DEPTH_TEST);

    Shader *objshader=new Shader("/Users/sherlock/Documents/Code/OpenGLdemo/OpenGLdemo/Lighting/multiplelights/multipleobj.vs","/Users/sherlock/Documents/Code/OpenGLdemo/OpenGLdemo/Lighting/multiplelights/multipleobj.fs");
    Shader *lightshader=new Shader("/Users/sherlock/Documents/Code/OpenGLdemo/OpenGLdemo/Lighting/multiplelights/multiplelight.vs","/Users/sherlock/Documents/Code/OpenGLdemo/OpenGLdemo/Lighting/multiplelights/multiplelight.fs");

    unsigned int VBO,objVAO,lightVAO;
    glGenBuffers(1,&VBO);
    glGenVertexArrays(1,&objVAO);
    glGenVertexArrays(1,&lightVAO);

    glBindVertexArray(objVAO);
    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,8*sizeof(GL_FLOAT),(void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,8*sizeof(GL_FLOAT),(void*)(3*sizeof(GL_FLOAT)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2,2,GL_FLOAT,GL_FALSE,8*sizeof(GL_FLOAT),(void*)(6*sizeof(GL_FLOAT)));
    glEnableVertexAttribArray(2);

    glBindVertexArray(lightVAO);
    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,8*sizeof(GL_FLOAT),(void*)0);
    glEnableVertexAttribArray(0);

    unsigned diffuseMap=loadTexture("/Users/sherlock/Documents/Code/OpenGLdemo/OpenGLdemo/resource/container2.png");
    unsigned specularMap=loadTexture("/Users/sherlock/Documents/Code/OpenGLdemo/OpenGLdemo/resource/container2_specular.png");

    objshader->use();
    //material
    objshader->setInt("material.diffuse", 0);
    objshader->setInt("material.specular", 1);
//    objshader->setInt("material.emission", 2);
    objshader->setFloat("material.shininess", 128.0f);
    //dirlight
    objshader->setVec3("dirlight.direction", -0.2f, -1.0f, -0.3f);
    objshader->setVec3("dirlight.ambient", glm::vec3(0.05f,0.05f,0.05f));
    objshader->setVec3("dirlight.diffuse", glm::vec3(0.4f,0.4f,0.4f));
    objshader->setVec3("dirlight.specular", glm::vec3(0.5f,0.5f,0.5f));
    //pointlight
    objshader->setVec3("pointlight[0].position", pointLightPositions[0]);
    objshader->setVec3("pointlight[1].position", pointLightPositions[1]);
    objshader->setVec3("pointlight[2].position", pointLightPositions[2]);
    objshader->setVec3("pointlight[3].position", pointLightPositions[3]);
    std::string lightname="pointlight";
    int pointlights=4;
    int elenum=6;
    std::string elements[6]={"ambient","diffuse","specular","constant","linear","quadratic"};
    std::vector<std::string> pointlightcolor=multiuniform(lightname, elements, pointlights, elenum);
    glm::vec3 pointlightambient(0.05f,0.05f,0.05f);
    glm::vec3 pointlightdiffuse(0.8f,0.8f,0.8f);
    glm::vec3 pointlightspecular(1.0f,1.0f,1.0f);
    for(int i=0;i<pointlightcolor.size();i++){
        if(i%6==0)
            objshader->setVec3(pointlightcolor.at(i), pointlightambient);
        if(i%6==1)
            objshader->setVec3(pointlightcolor.at(i), pointlightdiffuse);
        if(i%6==2)
            objshader->setVec3(pointlightcolor.at(i), pointlightspecular);
        if(i%6==3)
            objshader->setFloat(pointlightcolor.at(i), 1.0f);
        if(i%6==4)
            objshader->setFloat(pointlightcolor.at(i), 0.09f);
        if(i%6==5)
            objshader->setFloat(pointlightcolor.at(i), 0.032f);
    }
    //spotlight
    objshader->setVec3("spotlight.ambient", 0.5f, 0.5f, 0.5f);
    objshader->setVec3("spotlight.diffuse", 0.8f, 0.8f, 0.8f);
    objshader->setVec3("spotlight.specular", 1.0f, 1.0f, 1.0f);
    objshader->setFloat("spotlight.cutOff", glm::cos(glm::radians(12.5f)));
    objshader->setFloat("spotlight.outerCutOff", glm::cos(glm::radians(15.5f)));
    objshader->setFloat("spotlight.constant", 1.0f);
    objshader->setFloat("spotlight.linear", 0.09f);
    objshader->setFloat("spotlight.quadratic", 0.032f);

    while (!glfwWindowShouldClose(window)) {
        float currentTime=static_cast<float>(glfwGetTime());
        deltaTime=currentTime-lastTime;
        lastTime=currentTime;

        processInput(window);
        processCameraWSAD(window, camera, deltaTime);

        glClearColor(0.1f,0.1f,0.1f,1.0f);
        glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);
        //TODO

        glm::mat4 projection=glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH/(float)SCR_HEIGHT, 0.1f, 100.0f);

        objshader->use();
        objshader->setMat4("projection", projection);
        objshader->setVec3("spotlight.position", camera.Position);
        objshader->setVec3("spotlight.direction",camera.Front);
        glm::mat view=camera.GetViewMatrix();
        objshader->setMat4("view", view);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D,diffuseMap);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D,specularMap);

        glBindVertexArray(objVAO);
        for(unsigned int i=0;i<10;i++){
            glm::mat4 objmodel=glm::translate(glm::mat4(1.0f), cubePosition[i]);
            float angle=20.0f*i;
            objmodel=glm::rotate(objmodel, glm::radians(angle), glm::vec3(1.0f,0.3f,0.5f));
            objshader->setMat4("model", objmodel);
            glm::mat3 normalMatrix=glm::mat3(glm::transpose(glm::inverse(objmodel)));
            objshader->setMat3("normalMatrix", normalMatrix);
            glDrawArrays(GL_TRIANGLES,0,36);
        }

        lightshader->use();
        lightshader->setMat4("projection", projection);
        lightshader->setMat4("view", view);
        lightshader->setVec3("lightColor", glm::vec3(1.0f));

        for(unsigned int j=0;j<4;j++){
            glm::mat4 lightmodel=glm::scale(glm::translate(glm::mat4(1.0f), pointLightPositions[j]),glm::vec3(0.2f));
            lightshader->setMat4("model", lightmodel);
            glDrawArrays(GL_TRIANGLES,0,36);
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glDeleteBuffers(1,&VBO);
    glDeleteVertexArrays(1,&objVAO);
    glDeleteVertexArrays(1,&lightVAO);
    delete objshader;
    delete lightshader;

    glfwTerminate();
    return 0;
}

void mouse_callback(GLFWwindow* window,double xposIn,double yposIn){
    float xpos=static_cast<float>(xposIn);
    float ypos=static_cast<float>(yposIn);

    if(firstMouse){
        firstMouse=false;
        lastY=ypos;
        lastX=xpos;
    }

    float xoffset=xpos-lastX;
    float yoffset=lastY-ypos;
    lastY=ypos;
    lastX=xpos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow* window,double xoffset,double yoffset){
    camera.ProcessMouseScroll(yoffset);
}
