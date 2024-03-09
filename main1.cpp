#include "include/glad/glad.h"
#include "include/GLFW/glfw3.h"

#include <iostream>

void framebuffer_size_callback(GLFWwindow *window, int width, int height);

void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main() {
    // opengl 多平台，所以不会给你创建上下文，显示窗口，处理用户输入，所以这些都需要自己来做
    // glfw 是一个专门针对OpenGL的C语言库，它提供了一些渲染物体所需的最低限度的接口，比如窗口，输入，OpenGL上下文，以及基本的OpenGL功能
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    GLFWwindow *window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", nullptr, nullptr);
    if (window == nullptr) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad 帮我们找到对应显卡的函数指针，所以在调用任何OpenGL的函数之前，我们需要初始化glad
    // glad: load all OpenGL function pointers
    // 调用任何 opengl 函数前需要初始化 opengl 函数指针
    // 将对应驱动的指针函数传给 glfwGetProcAddress
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }






    //-------------------------------------------------------------------------------------------
    // 创建顶点着色器
    const char *vertexShaderSource = "#version 330 core\n"
                                     "layout (location = 0) in vec3 aPos;\n"
                                     "void main()\n"
                                     "{\n"
                                     "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                                     "}\0";
    // 存放 shader buffer
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    // 复制 shader 源码到 显卡上的 buffer
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    // 编译 shader
    glCompileShader(vertexShader);
    // 检查 shader 编译是否成功
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    //-------------------------------------------------------------------------------------------
    // 创建片段着色器
    const char *fragmentShaderSource = "#version 330 core\n"
                                       "out vec4 FragColor;\n"
                                       "void main()\n"
                                       "{\n"
                                       "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
                                       "}\n\0";
    // 存放 shader buffer
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    // 复制 shader 源码到 显卡上的 buffer
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    // 编译 shader
    glCompileShader(fragmentShader);
    // 检查 shader 编译是否成功
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    //-------------------------------------------------------------------------------------------
    // 创建着色器程序
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();
    // 将顶点着色器和片段着色器链接到着色器程序
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    // 检查着色器程序链接是否成功
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINK_FAILED\n" << infoLog << std::endl;
    }

    // 删除着色器
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    //-------------------------------------------------------------------------------------------
    // 定义 顶点数据 三角形
//    float vertices[] = {
//            -0.5f, -0.5f, 0.0f, // left
//            0.5f, -0.5f, 0.0f, // right
//            0.0f, 0.5f, 0.0f  // top
//    };

    // 作业1
    float vertices[] = {
            0.5f, 0.5f, 0.0f, //
            0.5f, -0.5f, 0.0f, //
            0.0f, -0.5f, 0.0f, //
            0.0f, -0.5f, 0.0f, //
            -0.5f, -0.5f, 0.0f, //
            -0.5f, 0.5f, 0.0f, //
    };

    // 定义 顶点数据 四边形
//    float vertices[] = {
//            0.5f, 0.5f, 0.0f, // 右上角
//            0.5f, -0.5f, 0.0f, // 右下角
//            -0.5f, -0.5f, 0.0f, // 左下角
//            -0.5f, 0.5f, 0.0f // 左上角
//    };

    unsigned int indices[] = {
        0, 1, 3,
        1, 2, 3
    };

    //-------------------------------------------------------------------------------------------
    // 创建索引缓冲对象
    unsigned int EBO;
    glGenBuffers(1, &EBO);


    //-------------------------------------------------------------------------------------------
    // 创建顶点缓冲对象
    unsigned int VBO;
//    glBindVertexArray(VAO);
    unsigned int VAO;
    // genbuffers 第一个参数是生成几个缓冲对象的意思，如果 VBO 是个数组，那么就会生成对应数量的缓冲对象
    glGenBuffers(1, &VBO);

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // 绑定缓冲对象
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    // 将顶点索引复制到缓冲对象
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    // 绑定缓冲对象
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // 将顶点数据复制到缓冲对象
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);



    //-------------------------------------------------------------------------------------------
    // 设置顶点属性指针
    // 顶点属性指针告诉OpenGL该如何解析顶点数据
    // 顶点属性位置值为0
    // 顶点属性大小为3
    // 数据类型为float
    // 步长为3 * sizeof(float)
    // 偏移量为0
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *) 0);
    // 启用顶点属性
    glEnableVertexAttribArray(0);

//    glBindBuffer(GL_ARRAY_BUFFER, 0);
//    glBindVertexArray(0);


    //-------------------------------------------------------------------------------------------
//    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window)) {
        // input
        // -----
        processInput(window);

        // render
        // ------
        // glClearColor 状态设置函数，设置清空屏幕所用的颜色
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        // glClear 状态使用函数，使用当前状态来获取应该清楚的颜色
        glClear(GL_COLOR_BUFFER_BIT);

        // 使用这个着色器
        glUseProgram(shaderProgram);


        glBindVertexArray(VAO);
//
        glDrawArrays(GL_TRIANGLES, 0, 6);


//        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        // 更新事件
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteProgram(shaderProgram);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}
