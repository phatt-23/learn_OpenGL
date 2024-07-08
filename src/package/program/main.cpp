#if 0
#include <GL/glew.h> 
#include <GLFW/glfw3.h>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <assimp/Importer.hpp>

#include <iostream>
#include <cstddef>
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
#include "../model/model.h"

#include "global.h"

#define ARR_LEN(x) (sizeof((x))/sizeof((*x)))

int main(void) 
{
    if (!glfwInit()) throwMessage("GLFW did not initialise");
    glfwSetErrorCallback(customGlfwError_Callback);

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

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window, mouse_Callback);
    glfwSetScrollCallback(window, scroll_Callback);

    Shader ourShader("res/shaders/model_loading.frag.vert.glsl");
    Model ourModel("res/models/backpack/backpack.obj");

    std::cout << ">> done loading resources" << std::endl;
    std::cin.get();

    while (!glfwWindowShouldClose(window)) 
    {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        processInput(window);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        {
            ourShader.bind();

            glm::mat4 projection = glm::perspective(glm::radians(camera.getFOV()), Renderer::getAspectRatio(), 0.1f, 100.0f);
            glm::mat4 view = camera.getViewMat();
            glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
            model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));

            ourShader.setUniMat4("projection", projection);
            ourShader.setUniMat4("view", view);
            ourShader.setUniMat4("model", model);

            ourModel.draw(ourShader);
        }
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}

#else
#include <GL/glew.h> 
#include <GLFW/glfw3.h>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <assimp/Importer.hpp>

#include <iostream>
#include <cstddef>
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
#include "../model/model.h"

#include "global.h"

#define ARR_LEN(x) (sizeof((x))/sizeof((*x)))

int main(void) 
{
    if (!glfwInit()) throwMessage("GLFW did not initialise");
    glfwSetErrorCallback(customGlfwError_Callback);

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

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window, mouse_Callback);
    glfwSetScrollCallback(window, scroll_Callback);

    std::vector<Vertex> vertices;         // positions          // normals           // texture coords
    vertices.push_back(Vertex::make(-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f ));
    vertices.push_back(Vertex::make( 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f ));
    vertices.push_back(Vertex::make( 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f ));
    vertices.push_back(Vertex::make( 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f ));
    vertices.push_back(Vertex::make(-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f ));
    vertices.push_back(Vertex::make(-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f ));

    vertices.push_back(Vertex::make( -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f ));
    vertices.push_back(Vertex::make(  0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f ));
    vertices.push_back(Vertex::make(  0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f ));
    vertices.push_back(Vertex::make(  0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f ));
    vertices.push_back(Vertex::make( -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f ));
    vertices.push_back(Vertex::make( -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f ));

    vertices.push_back(Vertex::make( -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f ));
    vertices.push_back(Vertex::make( -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f ));
    vertices.push_back(Vertex::make( -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f ));
    vertices.push_back(Vertex::make( -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f ));
    vertices.push_back(Vertex::make( -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f ));
    vertices.push_back(Vertex::make( -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f ));
    
    vertices.push_back(Vertex::make(  0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f ));
    vertices.push_back(Vertex::make(  0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f ));
    vertices.push_back(Vertex::make(  0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f ));
    vertices.push_back(Vertex::make(  0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f ));
    vertices.push_back(Vertex::make(  0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f ));
    vertices.push_back(Vertex::make(  0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f ));
    
    vertices.push_back(Vertex::make( -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f ));
    vertices.push_back(Vertex::make(  0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f ));
    vertices.push_back(Vertex::make(  0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f ));
    vertices.push_back(Vertex::make(  0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f ));
    vertices.push_back(Vertex::make( -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f ));
    vertices.push_back(Vertex::make( -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f ));
    
    vertices.push_back(Vertex::make( -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f ));
    vertices.push_back(Vertex::make(  0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f ));
    vertices.push_back(Vertex::make(  0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f ));
    vertices.push_back(Vertex::make(  0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f ));
    vertices.push_back(Vertex::make( -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f ));
    vertices.push_back(Vertex::make( -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0 ));

    glm::vec3 cubePositions[] = {
        {  0.0f,  0.0f,   0.0f  },
        {  2.0f, -10.0f, -15.0f },
        { -1.5f, -2.2f,  -2.5f  },
        { -3.8f, -2.0f,  -12.3f },
        {  2.4f, -0.4f,  -3.5f  },
        { -1.7f,  3.0f,  -7.5f  },
        {  1.3f, -2.0f,  -2.5f  },
        {  1.5f,  2.0f,  -2.5f  },
        {  1.5f,  0.2f,  -1.5f  },
        { -1.3f,  1.0f,  -1.5f  },
    };

    glm::vec3 pointLightPositions[] = {
        {  0.7f,  0.2f,  2.0f  },
        {  2.3f, -3.3f, -4.0f  },
        { -4.0f,  2.0f, -12.0f },
        {  0.0f,  0.0f, -3.0   },
    };

    VertBuffer VBO(vertices);
    VertBuffLayout layout;
    layout.push<float>(3);
    layout.push<float>(3);
    layout.push<float>(2);

    VertArray objectVAO;
    objectVAO.addBuffer(VBO, layout);
    
    VertArray lightVAO;
    lightVAO.addBuffer(VBO, layout);


    Shader objectShader = { "res/shaders/object.frag.vert.glsl" };
    Shader lightCubeShader = { "res/shaders/light.frag.vert.glsl" };
    Texture textures[] = {
        {"./res/images/container2.png",          Texture::Type::Diffuse  },
        {"./res/images/container2_specular.png", Texture::Type::Specular },
    };

    objectShader.bind();
    textures[0].bind(0);
    textures[1].bind(1);
    objectShader.setUniInt("material.diffuse", textures[0].getSlot());
    objectShader.setUniInt("material.specular", textures[1].getSlot());

    Shader ourShader("res/shaders/model_loading.frag.vert.glsl");
    Model ourModel("res/models/backpack/backpack.obj");

    while (!glfwWindowShouldClose(window)) 
    {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        processInput(window);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        {
            objectShader.bind();
            objectShader.setUniVec3f("viewPos", camera.getPos());
            objectShader.setUniFloat("material.shininess", 32.0f);

            // directional light
            objectShader.setUniVec3f("dirLight.direction", -0.2f, -1.0f, -0.3f);
            objectShader.setUniVec3f("dirLight.ambient", 0.05f, 0.05f, 0.05f);
            objectShader.setUniVec3f("dirLight.diffuse", 0.04f, 0.04f, 0.04f);
            objectShader.setUniVec3f("dirLight.specular", 0.5f, 0.5f, 0.5f);

            // point lights
            for (unsigned int i = 0; i < ARR_LEN(pointLightPositions); ++i)
            {
                const std::string pointLight = "pointLights[" + std::to_string(i) + "]";
                objectShader.setUniVec3f(pointLight + ".position", pointLightPositions[i]);
                objectShader.setUniVec3f(pointLight + ".ambient", 0.05f, 0.05f, 0.05f);
                objectShader.setUniVec3f(pointLight + ".diffuse", 0.8f, 0.8f, 0.8f);
                objectShader.setUniVec3f(pointLight + ".specular", 1.0f, 1.0f, 1.0f);
                objectShader.setUniVec1f(pointLight + ".constant", 1.0f);
                objectShader.setUniVec1f(pointLight + ".linear", 0.09f);
                objectShader.setUniVec1f(pointLight + ".quadratic", 0.032f);
            }

            // spotlight
            objectShader.setUniVec3f("spotLight.position", camera.getPos());
            objectShader.setUniVec3f("spotLight.direction", camera.getFront());
            objectShader.setUniVec1f("spotLight.innerCutoff", glm::cos(glm::radians(12.5f)));
            objectShader.setUniVec1f("spotLight.outerCutoff", glm::cos(glm::radians(13.0f)));
            objectShader.setUniVec1f("spotLight.constant", 1.0f);
            objectShader.setUniVec1f("spotLight.linear", 0.09f);
            objectShader.setUniVec1f("spotLight.quadratic", 0.032f);
            objectShader.setUniVec3f("spotLight.ambient", 0.0f, 0.0f, 0.0f);
            objectShader.setUniVec3f("spotLight.diffuse", 1.0f, 1.0f, 1.0f);
            objectShader.setUniVec3f("spotLight.specular", 1.0f, 1.0f, 1.0f);

            // mvp transformation
            glm::mat4 proj = glm::perspective(glm::radians(camera.getFOV()), Renderer::getAspectRatio(), 0.1f, 100.0f);
            glm::mat4 view = camera.getViewMat();
            glm::mat4 model = glm::mat4(1.0f);        
            objectShader.setUniMat4("proj", proj);
            objectShader.setUniMat4("view", view);
            objectShader.setUniMat4("model", view);

            textures[0].bind(0);
            textures[1].bind(1);

            objectVAO.bind();
            for (unsigned int i = 0; i < ARR_LEN(cubePositions); ++i) 
            {
                model = glm::translate(glm::mat4(1.0f), cubePositions[i]);
                float angle = i * 20.0f * 0.0f;
                model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
                objectShader.setUniMat4("model", model);
                Renderer::drawArrs(objectVAO, vertices.size(), objectShader);
            }

            lightCubeShader.bind();
            lightCubeShader.setUniMat4("proj", proj);
            lightCubeShader.setUniMat4("view", view);

            lightVAO.bind();
            for (unsigned int i = 0; i < ARR_LEN(pointLightPositions); ++i) 
            {
                model = glm::translate(glm::mat4(1.0f), pointLightPositions[i]);
                model = glm::scale(model, glm::vec3(0.2f));
                objectShader.setUniMat4("model", model);
                Renderer::drawArrs(lightVAO, vertices.size(), lightCubeShader);
            }
        }

        {
            glm::mat4 projection = glm::perspective(glm::radians(camera.getFOV()), Renderer::getAspectRatio(), 0.1f, 100.0f);
            glm::mat4 view = camera.getViewMat();
            glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -10.0f));
            model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));

            ourShader.bind();
            ourShader.setUniMat4("projection", projection);
            ourShader.setUniMat4("view", view);
            ourShader.setUniMat4("model", model);

            ourModel.draw(ourShader);
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}


#endif