#include "utils.h"

void terminateMessage(int error_code, const char* message) {
    fprintf(stderr, "Error: %s", message);
    exit(error_code);
}

void customGlfwErrorCallback(int error_code, const char* description) {
    fprintf(stderr, "[GLFW Error] (%d) %s\n", error_code, description);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    (void) window;
    std::cout << __FUNCTION__ << " :: " << width << " x " << height << std::endl;
    glViewport(0, 0, width, height);
}