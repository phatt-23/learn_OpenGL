#ifndef __RENDERER_H
#define __RENDERER_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "../vert_array/vert_array.h"
#include "../shader/shader.h"

void customGlfwErrorCallback(int error_code, const char* description);
void framebufferSizeCallback(GLFWwindow* window, int width, int height);

class Renderer
{
    private:
        static unsigned int s_width, s_height;

    public:
        Renderer(unsigned int m_width, unsigned int m_height);
        ~Renderer();

        static unsigned int getWidth();
        static unsigned int getHeight();
        static void setWidth(unsigned int width);
        static void setHeight(unsigned int heigt);
        static double getAspectRatio();

        static void draw(const VertArray& VAO, const ElemBuffer& EBO, const Shader& sh);
};

#endif//__RENDERER_H