#include "renderer.h"

void customGlfwErrorCallback(int error_code, const char* description) {
    fprintf(stderr, "[GLFW Error] (%d) %s\n", error_code, description);
}

void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
    std::cout << __FUNCTION__ << " :: x=" << width << ", y=" << height << std::endl;
    glfwMakeContextCurrent(window);
    glViewport(0, 0, width, height);
    Renderer::setWidth(width);
    Renderer::setHeight(height);
    glViewport(0, 0, width, height);
}

unsigned int Renderer::s_width = 100;
unsigned int Renderer::s_height = 100;

Renderer::Renderer(unsigned int width, unsigned int height)
{
    Renderer::s_width = width;
    Renderer::s_height = height;
}

Renderer::~Renderer()
{
}

unsigned int Renderer::getWidth()
{
    return Renderer::s_width;
}

unsigned int Renderer::getHeight()
{
    return Renderer::s_height;
}

void Renderer::setWidth(unsigned int width)
{
    Renderer::s_width = width;
}

void Renderer::setHeight(unsigned int height)
{
    Renderer::s_height = height;
}

void Renderer::draw(const VertArray &VAO, const ElemBuffer &EBO, const Shader &sh)
{
    VAO.bind();
    EBO.bind();
    sh.bind();
    glDrawElements(GL_TRIANGLES, EBO.getCount(), GL_UNSIGNED_INT, nullptr);
}

double Renderer::getAspectRatio()
{
    if (Renderer::s_height == 0) {
        std::cerr << "[Renderer::getAspectRatio] Division by zero is not allowed!" << std::endl;
        return 0.0f;
    }
    return (double)Renderer::s_width / (double)Renderer::s_height;
}
