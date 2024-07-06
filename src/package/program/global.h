#ifndef __PROGRAM_GLOBAL_H
#define __PROGRAM_GLOBAL_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

#include "../camera/camera.h"
#include "../renderer/renderer.h"

constexpr glm::vec2 SCREEN_DIM = glm::vec2(800, 600);

inline glm::vec2 cursorLast = SCREEN_DIM / 2.f;
inline float deltaTime = 0.0f;
inline float lastFrame = 0.0f;
inline Camera camera;

void mouse_Callback(GLFWwindow *window, double xpos, double ypos);
void scroll_Callback(GLFWwindow* window, double xoffset, double yoffset);
void customGlfwError_Callback(int error_code, const char* description);
void framebufferSize_Callback(GLFWwindow* window, int width, int height);

void processInput(GLFWwindow* window);

#endif//__PROGRAM_GLOBAL_H