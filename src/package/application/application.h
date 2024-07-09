#ifndef __PROGRAM_APPLICATION_H
#define __PROGRAM_APPLICATION_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include "../../vendor/imgui/imgui.h"
#include "../../vendor/imgui/imgui_impl_glfw.h"
#include "../../vendor/imgui/imgui_impl_opengl3.h"

#include "../utils/utils.h"
#include "../timer/timer.h"
#include "../camera/camera.h"
#include "../shader/shader.h"
#include "../model/model.h"

class Application
{
    private:
        GLFWwindow* window;
        glm::vec2 displayDim;
        Timer timer;

        // used inside init()
        void initGlfw();
        void initOpenGL();
        void initImGui();

        // used inside mainLoop()
        void onNextFrame();
        void onUpdate();
        void onRender();

    public:
        Application();
        ~Application();

        inline GLFWwindow* getGlfwWindow() { return window; }
        inline glm::vec2& getDisplayDim() { return displayDim; }
        inline void setDisplayDim(glm::vec2 v) { displayDim = v; }
    
    private:
        void init();
        void setUp();
        void mainLoop();
        void clean();
        
    public:
        void run();

    private:
        Camera* camera;
        Shader* ourShader;
        Model* ourModel;
};


#endif//__PROGRAM_APPLICATION_H
