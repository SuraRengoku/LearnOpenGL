//
//  general.cpp
//  OpenGLdemo
//
//  Created by SHERLOCK on 21.05.23.
//

#ifndef GENERAL_H
#define GENERAL_H

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <math.h>
#include <vector>
#include <Eigen/Dense>
#include "stb_image.h"


using std::cout,std::cin,std::endl;

class Triangle{
public:
    GLfloat *vertices;
    Triangle(GLint);
    Triangle(GLfloat* arrayPtr):vertices(arrayPtr){};
    ~Triangle(){
        delete[] vertices;
    };
};

class Test{
public:
    int success;
    char infoLog[512];
    std::string shaderType;
    void ShaderTest(unsigned int,int type);
    void ProgramTest(unsigned int);
};

class Texture{
public:
    unsigned char* data;
    unsigned char infoLog[512];
    void load_texture(char*);
};

//For Camera
enum Camera_Movement{
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

const float YAW=-90.f;
const float PITCH=0.0f;
const float SPEED=2.5f;
const float SENSITIVITY=0.1f;
const float ZOOM=45.0f;

class Camera{
public:
    glm::vec3 Position;
    glm::vec3 Front;
    glm::vec3 Up;
    glm::vec3 Right;
    glm::vec3 WorldUp;
    float Yaw;
    float Pitch;
    float MovementSpeed;
    float MouseSensitivity;
    float Zoom;
    
    Camera(glm::vec3 position=glm::vec3(0.0f,0.0f,0.0f),glm::vec3 up=glm::vec3(0.0f,1.0f,0.0f),float yaw=YAW, float pitch=PITCH):Front(glm::vec3(0.0f,0.0f,-1.0f)),MovementSpeed(SPEED),MouseSensitivity(SENSITIVITY),Zoom(ZOOM){
        Position=position;
        WorldUp=up;
        Yaw=yaw;
        Pitch=pitch;
        updataCameraVectors();
    }
    Camera(float posX,float posY,float posZ,float upX,float upY,float upZ,float yaw,float pitch):Front(glm::vec3(0.0f,0.0f,-1.0f)),MovementSpeed(SPEED),MouseSensitivity(SENSITIVITY),Zoom(ZOOM){
        Position=glm::vec3(posX,posY,posZ);
        WorldUp=glm::vec3(upX,upY,upZ);
        Yaw=yaw;
        Pitch=pitch;
        //更新Up,Right和Front，这三个变量在摄像机调转朝向时会改变
        updataCameraVectors();
    }
    glm::mat4 selfLookAt();
    glm::mat4 GetViewMatrix();
    virtual void ProcessKeyboard(Camera_Movement direction,float deltaTime);
    void ProcessMouseMovement(float xoffset,float yoffset,GLboolean constrainPitch=true);
    void ProcessMouseScroll(float yoffset);
protected:
    void updataCameraVectors();
};

//该类保证摄像机只能在xz平面上移动
class FPSCamera:public Camera{
public:
    FPSCamera(glm::vec3 position):Camera(position){};
    void ProcessKeyboard(Camera_Movement direction,float deltaTime) override;
};

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
int processInputUpDown(GLFWwindow* window);
void processCameraWSAD(GLFWwindow* window,Camera &camera,float &deltaTime);
//void mouse_callback(GLFWwindow* window,double &xpos,double &ypos,float &lastX,float &lastY,bool &firstMouse,float &yaw,float &pitch,glm::vec3 &cameraFront);


//使用Eigen计算
glm::mat4 inverse_mat4(glm::mat4 &mat);

//加载材质
unsigned int loadTexture(char const *filepath);

#endif

