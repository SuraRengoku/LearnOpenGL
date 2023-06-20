//#define GL_SLIENCE_DEPRECATION
//#include "triangle_0.hpp"
//
//static GLfloat vertices[]={
//    -0.5f,-0.5f,0.0f,
//    0.5f,-0.5f,0.0f,
//    0.0f,0.5f,0.0f
//};
//
//static GLfloat vertexset[]={
//    0.5f, 0.5f, 0.0f,   // 右上角
//    0.5f, -0.5f, 0.0f,  // 右下角
//    -0.5f, -0.5f, 0.0f, // 左下角
//    -0.5f, 0.5f, 0.0f   // 左上角
//};
//
//static int indices[]={
//    0,1,3,//第一个三角形
////    1,2,3//第二个三角形
//};
//
//const char *vertexShaderSource="#version 330 core\n"
//"layout (location=0) in vec3 aPos;\n"
//"void main(){\n"
//"   gl_Position=vec4(aPos.x,aPos.y,aPos.z,1.0f);\n"
//"}\n";
//
//const char *fragmentShaderSource="#version 330 core\n"
//"out vec4 FragColor;\n"
//"void main(){\n"
//"   FragColor=vec4(1.0f,0.5f,0.2f,1.0f);\n"
//"}\n";
////四个颜色参数：RGBalpha  alpha=1则完全不透明
//
//int triangle_0(){
//    glfwInit();
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
//
//    GLFWwindow* window=glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
//    if(window==nullptr){
//        cout<<"fail to create GLFW window"<<"\n";
//        glfwTerminate();
//        return -1;
//    }
//    glfwMakeContextCurrent(window);
//    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
//        cout<<"fail to initialize GLAD"<<"\n";
//        return -1;
//    }
//    glViewport(0,0,800,600);//控制窗口左下角位置
//    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);//注册窗口大小改变的回调函数
//
//    //创建VBO对象（顶点缓冲对象）
//    unsigned int VBO;
//    glGenBuffers(1, &VBO);
//    glBindBuffer(GL_ARRAY_BUFFER, VBO);//绑定缓冲
//    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);//复制顶点数据到缓冲内存中
//    //第四个参数指定了显卡管理给定数据的方式，这决定了显卡将数据放在不同速度的内存中
//    //GL_STATIC_DRAW:数据几乎不会改变
//    //GL_DYNAMIC_DRAW:数据会被改变很多
//    //GL_STREAM_DRAW:数据每次绘制时都会被改变
//
//    Test test;
//    unsigned int vertexShader=glCreateShader(GL_VERTEX_SHADER);//创建顶点着色器对象
//    glShaderSource(vertexShader,1,&vertexShaderSource,NULL);//传入信息
//    glCompileShader(vertexShader);//编译
//    test.ShaderTest(vertexShader, 1);
//
//    unsigned int fragmentShader=glCreateShader(GL_FRAGMENT_SHADER);
//    glShaderSource(fragmentShader,1,&fragmentShaderSource,NULL);
//    glCompileShader(fragmentShader);
//    test.ShaderTest(fragmentShader, 0);
//
//    unsigned int shaderProgram=glCreateProgram();//该函数创建程序并返回该程序对象的ID引用
//    glAttachShader(shaderProgram,vertexShader);
//    glAttachShader(shaderProgram,fragmentShader);
//    glLinkProgram(shaderProgram);//链接得到一个着色器对象
//    test.ProgramTest(shaderProgram);
//    //至此，可以删除着色器对象，不再被需要
//    glDeleteShader(vertexShader);
//    glDeleteShader(fragmentShader);
//
//    unsigned int VAO;
//    glGenVertexArrays(1,&VAO);
//    glBindVertexArray(VAO);
//    glBindBuffer(GL_ARRAY_BUFFER,VBO);
//    glBufferData(GL_ARRAY_BUFFER,sizeof(vertexset),vertexset,GL_STATIC_DRAW);
//    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3*sizeof(GL_FLOAT),(void*)0);
//    //p1:指定要配置的顶点
//    //p2:指定顶点大小
//    //p3:顶点数据类型
//    //p4:标准化与否
//    //p5:每组顶点起始点步长
//    //P6:数据位置在缓冲中起始位置的偏置量
//    glEnableVertexAttribArray(0);
//
//    unsigned int EBO;
//    glGenBuffers(1,&EBO);
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
//    glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indices),indices,GL_STATIC_DRAW);
//
//
//    while (!glfwWindowShouldClose(window)) {
//        //输入
//        processInput(window);
//
//        //渲染指令
//        glClearColor(0.2f,0.3f,0.3f,1.0f);
//        glClear(GL_COLOR_BUFFER_BIT);
//
//        glUseProgram(shaderProgram);
//        glBindVertexArray(VAO);
//        //画三角形
////        glDrawArrays(GL_TRIANGLES,0,3);
//        //画四边形
//        glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);
//        //检查并调用事件，交换缓冲区
//        //TODO:双缓冲
//        glfwSwapBuffers(window);
//        //交换颜色缓冲（它是一个储存着GLFW窗口每一个像素颜色值的大缓冲），它在这一迭代中被用来绘制，并且将会作为输出显示在屏幕上。
//        glfwPollEvents();//检查触发事件
//    }
//    glDeleteVertexArrays(1,&VAO);
//    glDeleteBuffers(1,&VBO);
//    glDeleteProgram(shaderProgram);
//
//    glfwTerminate();
//    return 0;
//}
//
