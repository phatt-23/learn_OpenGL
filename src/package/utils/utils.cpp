#include "utils.h"

void throwMessage(const char* message) {
    char strbuff[512] = {0};
    snprintf(strbuff, 512, "[ERR] %s", message);
    fprintf(stderr, "%s\n", strbuff);
    throw strbuff;
}

void customGlfwError_Callback(int error_code, const char* description) {
    std::cerr << std::format("[GLFW Error] ({}) {}\n", error_code, description) << std::endl;
}

void framebufferSize_Callback(GLFWwindow* window, int width, int height) {
    std::cout << std::format("[INFO {}] :: x={}, y={}", __FUNCTION__, width, height) << std::endl;
    glfwMakeContextCurrent(window);
    glViewport(0, 0, width, height);
    glViewport(0, 0, width, height);
}