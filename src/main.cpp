#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cmath>
#include <Headers/Shader.h>

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
        // positions         //colors
        0.5f, -0.5f, 0.0f,   1.0f, 0.0f, 0.0f,
       -0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,
        0.0f,  0.5f, 0.0f,   0.0f, 0.0f, 1.0f
    };

    unsigned int indices[] = {
        0,1,3,
        1,2,3
    };


    Shader ourShader("Triangle.vert", "Triangle.frag");


    unsigned int VAO,VBO;
    glGenVertexArrays(2, &VAO);
    glGenBuffers(2, &VBO);

    // First triangle
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(firstTriangle),firstTriangle, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);




    //Render Loop
    while (!glfwWindowShouldClose(window)) {
        processInput(window);

       //Clear Previous frame first
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        //draw triangle
        ourShader.use();
        glBindVertexArray(VAO);

        // double TimeValue = glfwGetTime();
        // float greenValue = static_cast<float>(sin(TimeValue) / 2.0 + 0.5);
        // int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
        // glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);

        glDrawArrays(GL_TRIANGLES, 0, 3);

        //display rendered events
        glfwSwapBuffers(window);

        glfwPollEvents();
    }





    glfwTerminate();
    return 0;
}
