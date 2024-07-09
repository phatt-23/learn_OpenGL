#include "mouse_handler.h"
#include "../../vendor/imgui/imgui.h"
#include "../../vendor/imgui/imgui_impl_glfw.h"


MouseHandler::MouseHandler(GLFWwindow* window, float mouseSensi, float scrollSensi) 
    : m_scrollX(0.0)
    , m_scrollY(0.0)
    , m_scrollSensi(scrollSensi)
    , m_lastCursor(0.0f)
    , m_cursor(0.0f)
    , m_mouseSensi(mouseSensi)
    , m_mouseMoveMode(0)
{
    glfwSetWindowUserPointer(window, this);
    glfwSetScrollCallback(window, scroll_Callback);
    glfwSetCursorPosCallback(window, cursorPos_Callback);
}

void MouseHandler::scroll_Callback(GLFWwindow* window, double xoffset, double yoffset)
{
    MouseHandler* handler = static_cast<MouseHandler*>(glfwGetWindowUserPointer(window));
    if (!handler) return;
    ImGui_ImplGlfw_ScrollCallback(window, xoffset, yoffset);
    
    handler->m_scrollX = xoffset;
    handler->m_scrollY = yoffset;
}

void MouseHandler::cursorPos_Callback(GLFWwindow* window, double xpos, double ypos)
{
    MouseHandler* handler = static_cast<MouseHandler*>(glfwGetWindowUserPointer(window));
    if (!handler) return;
    ImGui_ImplGlfw_CursorPosCallback(window, xpos, ypos);
    
    handler->m_lastCursor = handler->m_cursor;
    handler->m_cursor = {xpos, ypos};
}
