#ifndef __UTILITIES_H
#define __UTILITIES_H

#include <iostream>
#include <string>
#include <format>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

template<typename... Args>
void throwMessage(const char* format, Args... args) {
    char strbuff[512] = {0};
    sprintf(strbuff, "[ERR] ");
    sprintf(strbuff, format, args...);
    fprintf(stderr, "%s\n", strbuff);
    throw std::runtime_error(strbuff);
}

void throwMessage(const char* message);

void customGlfwError_Callback(int error_code, const char* description);

void framebufferSize_Callback(GLFWwindow* window, int width, int height);

#endif//__UTILITIES_H