#ifndef __UTILITIES_H
#define __UTILITIES_H

#include <GLFW/glfw3.h>
#include <iostream>

template<typename... Args>
void terminateMessage(int error_code, const char* format, Args... args) {
    fprintf(stderr, "Error: ");
    fprintf(stderr, format, args...);
    exit(error_code);
}

void terminateMessage(int error_code, const char* message);
void customGlfwErrorCallback(int error_code, const char* description);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);


#endif//__UTILITIES_H