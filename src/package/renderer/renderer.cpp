#include "renderer.h"

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

float Renderer::getAspectRatio()
{
    if (Renderer::s_height == 0) {
        std::cerr << "[Renderer::getAspectRatio] Division by zero is not allowed!" << std::endl;
        return 0.0f;
    }
    return (float)Renderer::s_width / (float)Renderer::s_height;
}
