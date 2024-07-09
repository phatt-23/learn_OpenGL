#ifndef __CAMERA_SCROLL_HANDLER_H
#define __CAMERA_SCROLL_HANDLER_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

class MouseHandler
{
    private:
        static void scroll_Callback(GLFWwindow* window, double xoffset, double yoffset);
        static void cursorPos_Callback(GLFWwindow* window, double xpos, double ypos);

        double m_scrollX;
        double m_scrollY;
        float m_scrollSensi;
        
        glm::vec2 m_lastCursor;
        glm::vec2 m_cursor;
        float m_mouseSensi;

        int m_mouseMoveMode;

    public:
        MouseHandler(GLFWwindow* window, float mouseSensi, float scrollSensi);

        inline double getScrollX() const { return m_scrollX; }
        inline double getScrollY() const { return m_scrollY; }
        inline void resetScroll() { m_scrollX = 0.0; m_scrollY = 0.0; }

        inline glm::vec2& getCursorRef() { return m_cursor; }
        inline const glm::vec2& getCursor() const { return m_cursor; }
        inline void resetLastCursor() { m_lastCursor = m_cursor; }

        inline glm::vec2& getLastCursorRef() { return m_lastCursor; }
        inline const glm::vec2& getLastCursor() const { return m_lastCursor; }


        inline int getMouseMoveMode() const { return m_mouseMoveMode; }
        inline int& getMouseMoveModeRef() { return m_mouseMoveMode; }
        inline void setMouseMoveMode(int mode) { m_mouseMoveMode = mode; }

        inline float getMouseSensi() const { return m_mouseSensi; }
        inline float getScrollSensi() const { return m_scrollSensi; }
};

#endif//__CAMERA_SCROLL_HANDLER_H