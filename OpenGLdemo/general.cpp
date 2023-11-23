//
//  general.cpp
//  OpenGLdemo
//
//  Created by SHERLOCK on 21.05.23.
//
#define STB_IMAGE_IMPLEMENTATION
#include "general.h"

Triangle::Triangle(GLint verticesNum){
    this->vertices=new float(verticesNum*3);
}

void Test::ShaderTest(unsigned int Shader,int type){
    if(type==1){
        this->shaderType="VERTEX";
    }else if(type==0){
        this->shaderType="FRAGMENT";
    }else if(type==2){
        this->shaderType="GEOMETRY";
    }
    glGetShaderiv(Shader,GL_COMPILE_STATUS,&this->success);
    if(!this->success){
        glGetShaderInfoLog(Shader,512,NULL,this->infoLog);
        cout<<"ERROR::SHADER::"<<this->shaderType<<"::COMPILATION_FAILED\n"<<infoLog<<"\n";
    }
}
void Test::ProgramTest(unsigned int shaderProgram){
    glGetProgramiv(shaderProgram,GL_LINK_STATUS,&this->success);
    if(!this->success){
        glGetProgramInfoLog(shaderProgram,512,NULL,infoLog);
        cout<<"ERROR::PORGRAM::SHADERPROGRAM::LINK_FAILED\n"<<infoLog<<"\n";
    }
}


//void Texture::load_texture(char* filepath){
//    int width, height, nrChannels;
//    unsigned char* data=stbi_load(filepath,&width, &height, &nrChannels, 0);
//    if(data){
//        glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,width,height,0,GL_RGB,GL_UNSIGNED_BYTE,data);
//        glGenerateMipmap(GL_TEXTURE_2D);
//    }else{
//        cout<<"Failed to load texture\n";
//    }
//    stbi_image_free(data);
//}


void framebuffer_size_callback(GLFWwindow* window,int width, int height){
    glViewport(0,0,width,height);
}

void processInput(GLFWwindow* window, GLFWcursorposfun mouse_callback, GLFWscrollfun scroll_callback){
    if(glfwGetKey(window,GLFW_KEY_ESCAPE)==GLFW_PRESS){
        //检测键盘输入，需要一个窗口和一个键盘键做参数，返回该键盘键是否被按下，如果没有被按下返回GLFW_RELEASE
        glfwSetWindowShouldClose(window, true);//使用函数将window的WindowShouldClose属性设置为true，该举动可以打破while循环
    }
    if(glfwGetKey(window, GLFW_KEY_O)==GLFW_PRESS){
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        glfwSetCursorPosCallback(window, NULL);
        glfwSetScrollCallback(window, NULL);
    }
    if(glfwGetKey(window, GLFW_KEY_I)==GLFW_PRESS){
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        glfwSetCursorPosCallback(window, mouse_callback);
        glfwSetScrollCallback(window, scroll_callback);
    }
}

void processCameraWSAD(GLFWwindow* window,Camera &camera,float &deltaTime){
    if(glfwGetKey(window, GLFW_KEY_W)==GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if(glfwGetKey(window, GLFW_KEY_S)==GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if(glfwGetKey(window, GLFW_KEY_A)==GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if(glfwGetKey(window, GLFW_KEY_D)==GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);
}

int processInputUpDown(GLFWwindow* window){
    if(glfwGetKey(window, GLFW_KEY_UP)==GLFW_PRESS){
        return 1;
    }else if(glfwGetKey(window, GLFW_KEY_DOWN)==GLFW_PRESS){
        return -1;
    }else{
        return 0;
    }
}

void Lightshift(GLFWwindow *window,bool &blinn,bool &blinnkeyPressed){
    if(glfwGetKey(window, GLFW_KEY_B)==GLFW_PRESS&&!blinnkeyPressed){
        blinn=!blinn;
        blinnkeyPressed=true;
    }
    if(glfwGetKey(window, GLFW_KEY_B)==GLFW_PRESS)
        blinnkeyPressed=false;
}

/**
 * @param window 窗口指针
 * @param xpos 当前鼠标x位置
 * @param ypos 当前鼠标y位置
 * @param lastX 鼠标上一帧x位置
 * @param lastY 鼠标上一帧y位置
 * @param firstMouse 是否第一次获取焦点
 * @param yaw 偏航弧度
 * @param pitch 俯仰弧度
 */
//void mouse_callback(GLFWwindow* window,double &xpos,double ypos,float &lastX,float &lastY,bool &firstMouse,float &yaw,float &pitch,glm::vec3 &cameraFront){
//    if(firstMouse){
//        lastX=xpos;
//        lastY=ypos;
//        firstMouse=false;
//    }
//
//    float sensitivity=0.05f;
//
//    float xoffset=(xpos-lastX)*sensitivity;
//    float yoffset=(lastY-ypos)*sensitivity;
//    lastX=xpos;
//    lastY=ypos;
//
//    yaw+=xoffset;
//    pitch+=yoffset;
//
//    //限位防止gimbal lock
//    if(pitch>89.0f)
//        pitch=89.0f;
//    if(pitch<-89.0f)
//        pitch=-89.0f;
//
//    glm::vec3 front;
//    front.x=cos(glm::radians(yaw))*cos(glm::radians(pitch));
//    front.y=sin(glm::radians(pitch));
//    front.z=sin(glm::radians(yaw))*cos(glm::radians(pitch));
//    cameraFront=glm::normalize(front);
//}

glm::mat4 Camera::selfLookAt(){
    glm::mat4 translate(1.0f);
    translate[3]=glm::vec4(-Position,1.0f);
    glm::mat4 ori(1.0f);
    ori[0][0]=Right.x;
    ori[0][1]=Up.x;
    ori[0][2]=-Front.x;
    ori[1][0]=Right.y;
    ori[1][1]=Up.y;
    ori[1][2]=-Front.y;
    ori[2][0]=Right.z;
    ori[2][1]=Up.z;
    ori[2][2]=-Front.z;
    return ori*translate;
}

glm::mat4 Camera::GetViewMatrix(){
    return selfLookAt();
//    return glm::lookAt(this->Position,this->Position+this->Front,this->Up);
}

void Camera::ProcessKeyboard(Camera_Movement direction, float deltaTime){
    float velocity=MovementSpeed*deltaTime;
    if(direction==FORWARD)
        Position+=Front*velocity;
    if(direction==BACKWARD)
        Position-=Front*velocity;
    if(direction==LEFT)
        Position-=Right*velocity;
    if(direction==RIGHT)
        Position+=Right*velocity;
}

void Camera::ProcessMouseMovement(float xoffset, float yoffset,GLboolean constrianPitch){
    xoffset*=MouseSensitivity;
    yoffset*=MouseSensitivity;
    Yaw+=xoffset;
    Pitch+=yoffset;
    if(constrianPitch){
        if(Pitch>89.0f)
            Pitch=89.0f;
        if(Pitch<-89.0f)
            Pitch=-89.0f;
    }
    updataCameraVectors();
}

void Camera::ProcessMouseScroll(float yoffset){
    Zoom-=(float)yoffset;
    if(Zoom<1.0f)
        Zoom=1.0f;
    if(Zoom>45.f)
        Zoom=45.0f;
}

void Camera::updataCameraVectors(){
    glm::vec3 front;
    front.x=cos(glm::radians(Yaw))*cos(glm::radians(Pitch));
    front.y=sin(glm::radians(Pitch));
    front.z=sin(glm::radians(Yaw))*cos(glm::radians(Pitch));
    Front=glm::normalize(front);
    Right=glm::normalize(glm::cross(Front, WorldUp));
    Up=glm::normalize(glm::cross(Right, Front));
}

void FPSCamera::ProcessKeyboard(Camera_Movement direction, float deltaTime){
    float velocity=MovementSpeed*deltaTime;
    if(direction==FORWARD)
        Position+=glm::vec3(Front.x*velocity,0.0f,Front.z*velocity);
    if(direction==BACKWARD)
        Position-=glm::vec3(Front.x*velocity,0.0f,Front.z*velocity);
    if(direction==LEFT)
        Position-=glm::vec3(Right.x*velocity,0.0f,Right.z*velocity);
    if(direction==RIGHT)
        Position+=glm::vec3(Right.x*velocity,0.0f,Right.z*velocity);
}

//glm::mat4 inverse_mat4(glm::mat4 &mat){
//    std::vector<float> vec{
//        mat[0][0],mat[1][0],mat[2][0],mat[3][0],
//        mat[0][1],mat[1][1],mat[2][1],mat[3][1],
//        mat[0][2],mat[1][2],mat[2][2],mat[3][2],
//        mat[0][3],mat[1][3],mat[2][3],mat[3][3],
//    };
//    Eigen::Map<Eigen::MatrixXf> map(vec.data(),4,4);
//    Eigen::MatrixXf inv=map.inverse();
//    glm::mat4 result;
//    for(int m=0;m<4;m++){
//        for(int n=0;n<4;n++){
//            result[m][n]=inv[m*4+n];
//        }
//    }
//    return result;
//}

unsigned int loadTexture(char const *filepath){
    unsigned int textureID;
    glGenTextures(1,&textureID);

    int width,height,nrChannels;
//    stbi_set_flip_vertically_on_load(true);
    unsigned char *data=stbi_load(filepath, &width, &height, &nrChannels, 0);
    if(data){
        GLenum format;
        if(nrChannels==1)
            format=GL_RED;
        else if(nrChannels==3)
            format=GL_RGB;
        else if(nrChannels==4)
            format=GL_RGBA;

        glBindTexture(GL_TEXTURE_2D,textureID);
        glTexImage2D(GL_TEXTURE_2D,0,format,width,height,0,format,GL_UNSIGNED_BYTE,data);
        glGenerateMipmap(GL_TEXTURE_2D);
        if(nrChannels==4){
            glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);
        }
        else{
            glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
        }
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
        stbi_image_free(data);
    }
    else{
        cout<<"Failed to load texture at path"<<filepath<<"\n";
        stbi_image_free(data);
    }
    return textureID;
}

unsigned int loadTexture(char const *filepath,bool sRGB){
    unsigned int textureID;
    glGenTextures(1,&textureID);

    int width,height,nrChannels;
//    stbi_set_flip_vertically_on_load(true);
    unsigned char *data=stbi_load(filepath, &width, &height, &nrChannels, 0);
    if(data){
        GLenum format1,format2;
        if(nrChannels==1){
            format1=GL_RED;
            format2=GL_RED;
        }
        if(sRGB){
            if(nrChannels==3){
                format1=GL_SRGB;
                format2=GL_RGB;
            }
            else if(nrChannels==4){
                format1=GL_SRGB_ALPHA;
                format2=GL_RGBA;
            }
        }else{
            if(nrChannels==3){
                format1=GL_RGB;
                format2=GL_RGB;
            }
            else if(nrChannels==4){
                format1=GL_RGBA;
                format2=GL_RGBA;
            }
        }

        glBindTexture(GL_TEXTURE_2D,textureID);
        glTexImage2D(GL_TEXTURE_2D,0,format1,width,height,0,format2,GL_UNSIGNED_BYTE,data);
        glGenerateMipmap(GL_TEXTURE_2D);
        if(nrChannels==4){
            glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);
        }
        else{
            glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
        }
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
        stbi_image_free(data);
    }
    else{
        cout<<"Failed to load texture at path"<<filepath<<"\n";
        stbi_image_free(data);
    }
    return textureID;

}

unsigned int loadTextureHDR(char const *filepath){
    stbi_set_flip_vertically_on_load(true);
    int width,height,nrComponents;
    float *data=stbi_loadf(filepath, &width, &height, &nrComponents, 0);
    unsigned int hdrTexture;
    try{
        if(data){
            glGenTextures(1,&hdrTexture);
            glBindTexture(GL_TEXTURE_2D,hdrTexture);
            glTexImage2D(GL_TEXTURE_2D,0,GL_RGB16F,width,height,0,GL_RGB,GL_FLOAT,data);
            glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
            stbi_image_free(data);
        }else{
            stbi_image_free(data);
            throw std::runtime_error("Failed to load HDR image.");
        }
    }catch(const std::runtime_error &err){
        cerr<<err.what()<<"\n";
        throw;
    }
    return hdrTexture;
}

unsigned int loadCubemap(vector<string> faces){
    unsigned int textureID;
    glGenTextures(1,&textureID);
    glBindTexture(GL_TEXTURE_CUBE_MAP,textureID);
    
    int width,height,nrChannels;
    for(unsigned int i=0;i<faces.size();i++){
        unsigned char *data=stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
        try{
            if(data){
                glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X+i,0,GL_RGB,width,height,0,GL_RGB,GL_UNSIGNED_BYTE,data);
                stbi_image_free(data);
            }else{
                stbi_image_free(data);
                throw std::runtime_error("Cubemap texture failed to load at path");
            }
        }catch(const std::runtime_error &err){
            cerr<<err.what()<<faces[i]<<"\n";
            throw;
        }
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP,GL_TEXTURE_WRAP_R,GL_CLAMP_TO_EDGE);
    return textureID;
}

unsigned int loadTextureFromAssimp(const aiTexture* aiTex, GLint wrapMode, GLint MagFilterMode, GLint MinFilterMode){
    if(aiTex==nullptr)
        return 0;
    GLuint textureID=0;
    glGenTextures(1,&textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,wrapMode);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,wrapMode);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,MagFilterMode);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,MinFilterMode);

    int width, height, nrChannels;
    unsigned char* image_data=nullptr;
    if(aiTex->mHeight==0){
        image_data=stbi_load_from_memory(reinterpret_cast<unsigned char*>(aiTex->pcData), aiTex->mWidth, &width, &height, &nrChannels, 0);
    }
    else{
        image_data = stbi_load_from_memory(reinterpret_cast<unsigned char*>(aiTex->pcData), aiTex->mWidth * aiTex->mHeight, &width, &height, &nrChannels, 0);
    }
    if(image_data!=nullptr){
        GLenum format;
        if(nrChannels==1)
            format=GL_RED;
        else if(nrChannels==3)
            format=GL_RGB;
        else if(nrChannels==4)
            format=GL_RGBA;
        glTexImage2D(GL_TEXTURE_2D,0,format,width,height,0,format,GL_UNSIGNED_BYTE,image_data);
    }
    glGenerateMipmap(GL_TEXTURE_2D);
    return textureID;
}

std::vector<std::string> multiuniform(std::string _main, std::string(elements) [], int num,int elenum){
    std::vector<std::string> result;
    for(int i=0;i<num;i++){
        for(int j=0;j<elenum;j++){
            std::string element=_main+"["+std::to_string(i)+"]."+elements[j];
            result.push_back(element);
        }
    }
    return result;
}

auto glfw_Init(int SCR_WIDTH,int SCR_HEIGHT,GLFWcursorposfun mouse_callback,GLFWscrollfun scroll_callback)->GLFWwindow*{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);//设置上下文主要版本号
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);//次要版本号
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GL_SAMPLES, 4);//四个采样点
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
        throw;
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
        throw;
    }
    return window;
}

auto glfw_Init(GLuint SCR_WIDTH,GLuint SCR_HEIGHT,const char* name)->GLFWwindow*{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    glfwWindowHint(GL_SAMPLES, 4);//四个采样点
    //GLFW_OPENGL_PROFILE宏用于指定OpenGL上下文的配置文件类型
    //GLFW_OPENGL_CORE_PROFILE宏用于表示使用核心配置文件
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    //启用向前兼容模式，允许在较新的版本中使用较旧的特性
#endif

    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, name, nullptr, nullptr);
    try{
        if(window==nullptr)
            throw std::runtime_error("window generated unsuccessfully");
    }catch(std::runtime_error err){
        cerr<<err.what()<<"\n";
        glfwTerminate();
        throw;
    }

    glfwMakeContextCurrent(window);
    
    try{
        if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
            throw std::runtime_error("fail to initialize GLAD");
    }catch(std::runtime_error err){
        cerr<<err.what()<<"\n";
        glfwTerminate();
        throw;
    }
    return window;
}

