#include <GL/glew.h> 
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <format>
#include <cstdlib>
#include <cmath>
#include <array>

#include "../renderer/renderer.h"
#include "../shader/shader.h"
#include "../texture/texture.h"
#include "../vert_array/vert_array.h"
#include "../utils/utils.h"
#include "../camera/camera.h"
#include "global.h"

int main(void) 
{
    if (!glfwInit()) throwMessage("GLFW did not initialise");
    glfwSetErrorCallback(customGlfwErrorCallback);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    GLFWwindow* window = glfwCreateWindow(SCREEN_DIM.x, SCREEN_DIM.y, "Learn OpenGL", nullptr, nullptr);
    if (!window) { glfwTerminate(); return -1; }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    if (glewInit() != GLEW_OK) throwMessage("GLEW did not initialise");

    glfwSetFramebufferSizeCallback(window, framebufferSize_Callback);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glEnable(GL_DEPTH_TEST);
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // wireframe

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window, mouse_Callback);
    glfwSetScrollCallback(window, scroll_Callback);

    float vertices[] = {
        // positions         // colors           // texture coords
        0.5f,  0.5f, 0.5f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,    // f top right
        0.5f, -0.5f, 0.5f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,    // f bottom right
       -0.5f, -0.5f, 0.5f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,    // f bottom left
       -0.5f,  0.5f, 0.5f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f,    // f top left 

        0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 0.0f,  1.0f, 1.0f,     // b top right
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f,  1.0f, 0.0f,     // b bottom right
       -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 1.0f,  0.0f, 0.0f,     // b bottom left
       -0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f,  0.0f, 1.0f,     // b top left 
    };
    unsigned int indices[] = {
        0, 1, 2, 2, 3, 0,
        4, 5, 6, 6, 7, 4,
        1, 5, 6, 6, 2, 1,
        0, 4, 7, 7, 3, 0,
        3, 2, 6, 6, 7, 3,
        0, 1, 5, 5, 4, 0,
    };
    glm::vec3 positions[] = {
        {  0.0f,  0.0f,  0.0f  },
        {  2.0f,  5.0f, -15.0f },
        { -1.5f, -2.2f, -2.5f  },
        { -3.8f, -2.0f, -12.3f },
        {  2.4f, -0.4f, -3.5f  },
        { -1.7f,  3.0f, -7.5f  },
        {  1.3f, -2.0f, -2.5f  },
        {  1.5f,  2.0f, -2.5f  },
        {  1.5f,  0.2f, -1.5f  },
        { -1.3f,  1.0f, -1.5f  },
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
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        for (size_t i = 0; i < sizeof(positions)/sizeof(*positions); ++i) {
            auto& p = positions[i];
            glm::mat4 model, view, proj; 
            model = glm::mat4(1.0);
            model = glm::translate(model, p);
            model = glm::rotate(model, i * 40.f, glm::normalize(glm::vec3(glfwGetTime(), glfwGetTime(), glfwGetTime())));
            model = glm::scale(model, glm::vec3(1.0, 1.0, 1.0));
            
            view = camera.getViewMat();
            
            proj = glm::perspective(glm::radians(camera.getFOV()), Renderer::getAspectRatio(), 0.1f, 100.0f);

            shader.bind();
            shader.setUniformMat4("vu_Model", model);
            shader.setUniformMat4("vu_View", view);
            shader.setUniformMat4("vu_Proj", proj);

            textures[0].bind(0);
            textures[1].bind(1);
            shader.setUniform1i("fu_Texture0", 0);
            shader.setUniform1i("fu_Texture1", 1);
            Renderer::draw(VAO, EBO, shader);
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
