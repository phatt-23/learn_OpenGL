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

    // float vertices[] = {
    //     // positions
    //     0.5f,  0.5f,  0.5f, // fur
    //     0.5f, -0.5f,  0.5f, // fdr
    //    -0.5f, -0.5f,  0.5f, // fdl
    //    -0.5f,  0.5f,  0.5f, // ful 
    //     0.5f,  0.5f, -0.5f, // bur
    //     0.5f, -0.5f, -0.5f, // bdr
    //    -0.5f, -0.5f, -0.5f, // bdl
    //    -0.5f,  0.5f, -0.5f, // bur 
    // };
    // unsigned int indices[] = {
    //     0, 1, 2, 2, 3, 0, // 0.0, 0.0, 1.0
    //     4, 5, 6, 6, 7, 4,
    //     1, 5, 6, 6, 2, 1,
    //     0, 4, 7, 7, 3, 0,
    //     3, 2, 6, 6, 7, 3,
    //     0, 1, 5, 5, 4, 0,
    // };
    float vertices[] = {
        // pos                // norm
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 
        0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 
        0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 

        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,

        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

        0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
        0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
        0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
        0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
        0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
        0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
        0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
        0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
        0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
    };
    glm::vec3 positions[] = {
        {  0.0f,  0.0f,  0.0f  },
        { -1.3f,  1.0f, -1.5f  },
    };

    VertBuffer VBO(vertices, sizeof(vertices));
    VertBuffLayout layout;
    layout.push<float>(3);
    layout.push<float>(3);
    // ElemBuffer EBO(indices, sizeof(indices)/sizeof(*indices));

    VertArray objectVAO;
    objectVAO.addBuffer(VBO, layout);
    
    VertArray lightVAO;
    lightVAO.addBuffer(VBO, layout);

    Shader lightShader("res/shaders/light.glsl");
    Shader objectShader("res/shaders/object.glsl");

    Texture textures[2] = {
        {"./res/images/container.jpg"},
        {"./res/images/awesomeface.png"},
    };

    lightShader.unbind();
    objectShader.unbind();
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

        {
            glm::mat4 model, view, proj; 
            model = glm::mat4(1.0);
            model = glm::translate(model, positions[0]);
            model = glm::rotate(model, 0.0f, glm::normalize(glm::vec3(glfwGetTime(), glfwGetTime(), glfwGetTime())));
            model = glm::scale(model, glm::vec3(1.0, 1.0, 1.0));
            view = camera.getViewMat();
            proj = glm::perspective(glm::radians(camera.getFOV()), Renderer::getAspectRatio(), 0.1f, 100.0f);

            objectShader.bind();
            objectShader.setUniformMat4("vu_Model", model);
            objectShader.setUniformMat4("vu_View", view);
            objectShader.setUniformMat4("vu_Proj", proj);
            objectShader.setUniform3f("fu_ObjectColor", 1.0f, 0.5f, 0.31f);
            objectShader.setUniform3f("fu_LightSrcColor", sin(3.0 * glfwGetTime()), 1.0, 1.0);
            objectShader.setUniform3f("fu_LightSrcPos", positions[1]);
            // Renderer::draw(objectVAO, EBO, objectShader);
            Renderer::drawArrs(objectVAO, sizeof(vertices)/sizeof(*vertices)/6, objectShader);
        }
        {
            glm::mat4 model, view, proj; 
            model = glm::mat4(1.0);
            model = glm::translate(model, positions[1]);
            model = glm::rotate(model, 0.0f, glm::normalize(glm::vec3(glfwGetTime(), glfwGetTime(), glfwGetTime())));
            model = glm::scale(model, glm::vec3(1.0, 1.0, 1.0));
            view = camera.getViewMat();
            proj = glm::perspective(glm::radians(camera.getFOV()), Renderer::getAspectRatio(), 0.1f, 100.0f);

            lightShader.bind();
            lightShader.setUniformMat4("vu_Model", model);
            lightShader.setUniformMat4("vu_View", view);
            lightShader.setUniformMat4("vu_Proj", proj);
            lightShader.setUniform3f("fu_LightColor", sin(3.0 * glfwGetTime()), 1.0, 1.0);
            // Renderer::draw(objectVAO, EBO, lightShader);
            Renderer::drawArrs(lightVAO, sizeof(vertices)/sizeof(*vertices)/6, lightShader);
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
