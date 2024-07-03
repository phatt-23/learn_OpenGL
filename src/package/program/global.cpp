#include "global.h"

void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.processKeyboard(Camera::Key::W, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) 
        camera.processKeyboard(Camera::Key::S, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) 
        camera.processKeyboard(Camera::Key::A, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) 
        camera.processKeyboard(Camera::Key::D, deltaTime);
}

void mouse_Callback(GLFWwindow *window, double xpos, double ypos)
{
    static bool firstMouse = true;
    if (firstMouse) {
        cursorLast = glm::vec2(xpos, ypos);
        firstMouse = false;
    }
    camera.processMouseMove(xpos - cursorLast.x, cursorLast.y - ypos);
    cursorLast = glm::vec2(xpos, ypos);
}

void scroll_Callback(GLFWwindow* window, double xoffset, double yoffset) 
{
    camera.processMouseScroll(yoffset);
}

void customGlfwErrorCallback(int error_code, const char* description) {
    std::cerr << std::format("[GLFW Error] ({}) {}\n", error_code, description) << std::endl;
}

void framebufferSize_Callback(GLFWwindow* window, int width, int height) {
    std::cout << std::format("[INFO {}] :: x={}, y={}", __FUNCTION__, width, height) << std::endl;
    glfwMakeContextCurrent(window);
    glViewport(0, 0, width, height);
    Renderer::setWidth(width);
    Renderer::setHeight(height);
    glViewport(0, 0, width, height);
}
