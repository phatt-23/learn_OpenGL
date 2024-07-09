#include "application.h"
#include "../utils/utils.h"

// GLFWwindow* GL_Window_Init(int majorVersion, int minorVersion, int width, int height, const char *title, GLFWmonitor *monitor, GLFWwindow *share)
// {
//     // GLFW init
//     if (!glfwInit()) throwMessage("GLFW did not initialise");

//     // OpenGL version
//     glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, majorVersion);
//     glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minorVersion);
//     glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
//     // window creation
//     GLFWwindow* window = glfwCreateWindow(width, height, title, monitor, share);
//     if (!window) { 
//         glfwTerminate(); 
//         throw std::runtime_error("GLFW Window didnt initialise!"); 
//     }
//     glfwMakeContextCurrent(window);
//     glfwSwapInterval(1);

//     // OpenGL GLEW init
//     if (glewInit() != GLEW_OK) {
//         throw std::runtime_error("GLEW did not initialise");
//     }

//     // OpenGL settings
//     glEnable(GL_BLEND);
//     glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//     glEnable(GL_DEPTH_TEST);

//     // callback
//     glfwSetErrorCallback(customGlfwError_Callback);
//     glfwSetFramebufferSizeCallback(window, framebufferSize_Callback);
//     glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
//     glfwSetCursorPosCallback(window, mouse_Callback);
//     glfwSetScrollCallback(window, scroll_Callback);

//     return window;
// }