#include <GL/glew.h> 
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <cstdlib>
#include <cmath>

#include "../utils/utils.h"
#include "../shader/shader.h"
#include "../texture/texture.h"
#include "../vertex_array/vert_array.h"

void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

int main(void) 
{
    if (!glfwInit()) terminateMessage(-1, "GLFW did not initialise");
    glfwSetErrorCallback(customGlfwErrorCallback);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "Learn OpenGL", nullptr /* glfwGetPrimaryMonitor() */, nullptr);
    if (!window) { glfwTerminate(); return -1; }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    if (glewInit() != GLEW_OK) terminateMessage(-1, "GLEW did not initialise");

    glViewport(0, 0, 800, 600);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // wireframe
    // glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // filled in

    float vertices[] = {
        // positions          // colors           // texture coords
        0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
        0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
       -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
       -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left 
    };
    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0,
    };

    VertBuffer VBO(vertices, sizeof(vertices));
    VertBuffLayout layout;
    layout.push<float>(3);
    layout.push<float>(3);
    layout.push<float>(2);
    ElemBuffer EBO(indices, sizeof(indices)/sizeof(*indices));
    VertArray VAO;
    VAO.addBuffer(VBO, layout, EBO);

    Shader shader("res/shaders/basic.glsl");
    shader.bind();

    Texture textures[2] = {
        {"./res/images/container.jpg"},
        {"./res/images/awesomeface.png"},
    };

    shader.unbind();
    VBO.unbind();
    textures[0].unbind();
    textures[1].unbind();

    while (!glfwWindowShouldClose(window)) 
    {
        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader.bind();
        textures[0].bind(0);
        textures[1].bind(1);
        shader.setUniform1i("fu_Texture0", 0);
        shader.setUniform1i("fu_Texture1", 1);
        VAO.bind();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
