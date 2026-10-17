#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cmath>

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}
int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "Hello Window", NULL, NULL);
   if (window == NULL) {
       std::cout<<"failed to create GLFW Window"<<std::endl;
       glfwTerminate();
       return -1;
   }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout<<"Failed to initialize GLAD"<<std::endl;
        return -1;
    }
    glViewport(0, 0, 800, 600);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    float firstTriangle[] = {
        // positions
        0.5f, -0.5f, 0.0f,
       -0.5f, -0.5f, 0.0f,
        0.0f,  0.5f, 0.0f
    };

    unsigned int indices[] = {
        0,1,3,
        1,2,3
    };

    const char *vertexShaderSource ="#version 330 core\n"
     "layout (location = 0) in vec3 aPos;\n"
     "void main()\n"
     "{\n"
     "   gl_Position = vec4(aPos, 1.0);\n"
     "}\0";

    const char *fragmentShaderSource = "#version 330 core\n"
        "out vec4 FragColor;\n"
        "uniform vec4 ourColor;\n"
        "void main()\n"
        "{\n"
        "   FragColor = ourColor;\n"
        "}\n\0";




    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    unsigned int OrangeShader;

    OrangeShader = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(OrangeShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(OrangeShader);

    //Creates a Shader Program
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();



    //Attaches Shaders to Shader Program
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, OrangeShader);

    glLinkProgram(shaderProgram);

    // Validation layer which checks wether the shader linking failed or not
        //Variables
            int  success;
            char infoLog[512];
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
        if(!success) {
            glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);

        }


    //Vertex Shader Validation Layer

    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

    if(!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    unsigned int VAO, VBO;

    glGenVertexArrays(2, &VAO);
    glGenBuffers(2, &VBO);

    // First triangle
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(firstTriangle),firstTriangle, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);




    //Render Loop
    while (!glfwWindowShouldClose(window)) {
        processInput(window);

       //Clear Previous frame first
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        //draw triangle
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);

        double TimeValue = glfwGetTime();
        float greenValue = static_cast<float>(sin(TimeValue) / 2.0 + 0.5);
        int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
        glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);

        glDrawArrays(GL_TRIANGLES, 0, 3);

        //display rendered events
        glfwSwapBuffers(window);

        glfwPollEvents();
    }


    glDeleteProgram(shaderProgram);


    glfwTerminate();
    return 0;
}
