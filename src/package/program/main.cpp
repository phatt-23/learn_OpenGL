
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
#include "../timer/timer.h"

glm::vec2 displayDim = glm::vec2(800, 600);

int main(void) 
{
    if (!glfwInit()) throwMessage("GLFW did not initialise");
    glfwSetErrorCallback(customGlfwError_Callback);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    GLFWwindow* window = glfwCreateWindow(displayDim.x, displayDim.y, "GLFW OpenGL Window", nullptr, nullptr);
    if (!window) { glfwTerminate(); return -1; }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    if (glewInit() != GLEW_OK) throwMessage("GLEW did not initialise");

    glfwSetFramebufferSizeCallback(window, framebufferSize_Callback);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_DEPTH_TEST);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard | ImGuiConfigFlags_NavEnableGamepad;  
    ImGui::StyleColorsDark();
    ImGui_ImplOpenGL3_Init("#version 330");
    ImGui_ImplGlfw_InitForOpenGL(window, true);

    Shader ourShader("res/shaders/model_loading.frag.vert.glsl");
    Model ourModel("res/models/backpack/backpack.obj");

    Camera camera(window, CAM_POS, CAM_FRONT, CAM_UP, CAM_YAW, CAM_PITCH);

    Timer timer;
    while (!glfwWindowShouldClose(window)) 
    {
        glfwPollEvents();

        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        displayDim = { display_w, display_h };
        glViewport(0, 0, displayDim.x, displayDim.y);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        timer.nextFrame();

        camera.processInput(window, timer.dt());
        camera.setDisplayDim(displayDim);
        camera.debugInfo();
        
        // backpack
        {
            glm::mat4 proj, view, model = glm::mat4(1.0f);
            proj = camera.getProjMat(0.1f, 100.0f);
            view = camera.getViewMat();
            model = glm::translate(model, glm::vec3(0.0f, 0.0f, -10.0f));
            model = glm::rotate(model, 23.0f, glm::vec3(0.0f, 1.0f, 0.0f));
            model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));

            ourShader.bind();
            ourShader.setMat4("proj", proj);
            ourShader.setMat4("view", view);
            ourShader.setMat4("model", model);

            ourModel.draw(ourShader);
        }

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(window);
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}

