#ifndef __CAMERA_H
#define __CAMERA_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "../../vendor/imgui/imgui.h"
#include "../../vendor/imgui/imgui_impl_glfw.h"
#include "../../vendor/imgui/imgui_impl_opengl3.h"

#include "mouse_handler.h"

// >>> default settings
constexpr glm::vec3 CAM_POS = glm::vec3(0.0f, 0.0f, 3.0f);
constexpr glm::vec3 CAM_FRONT = glm::vec3(0.0f, 0.0f, -1.0f);
constexpr glm::vec3 CAM_UP = glm::vec3(0.0f, 1.0f, 0.0f);

constexpr float CAM_YAW = -90.0f;
constexpr float CAM_PITCH = 0.0f;
constexpr float CAM_FOV = 45.0f;
constexpr float CAM_MOVE_SPEED = 5.0f;
constexpr float CAM_MOUSE_SENSI = 0.2f;
constexpr float CAM_SCROLL_SENSI = 3.0f;

constexpr float CAM_PITCH_CONSTRAINT = 89.0f;
constexpr float CAM_FOV_MIN = 1.0f;
constexpr float CAM_FOV_MAX = 120.0f;



class Camera
{
    private:
        glm::vec3 m_pos;
        glm::vec3 m_front;
        glm::vec3 m_up;
        glm::vec3 m_right;
        glm::vec3 m_worldUp;

        float m_yaw;
        float m_pitch;
        float m_fov;

        glm::vec2 m_displayDim;
        
        float m_moveSpeed;

        MouseHandler m_MouseHandler;

        void updateVectors();
        void processKeyboard(GLFWwindow* window, float dt);
        void processMouseMove(GLFWwindow* window);
        void processMouseScroll(GLFWwindow* window);

    public:
        Camera(GLFWwindow* window, const glm::vec3& pos, const glm::vec3& front, const glm::vec3& up, float yaw, float pitch);
        ~Camera();

        void processInput(GLFWwindow* window, float dt);
        void debugInfo();

        inline glm::mat4 getViewMat() const { return glm::lookAt(m_pos, m_pos + m_front, m_up); }
        inline glm::mat4 getProjMat(float nearPlane = 0.1f, float farPlane = 100.0f) const { return glm::perspective(glm::radians(m_fov), m_displayDim.x / m_displayDim.y, nearPlane, farPlane); }
        inline glm::mat4 getViewProjMat() const { return getViewMat() * getProjMat(); }
        inline float getFOV() const { return m_fov; }
        inline const glm::vec3& getPos() const { return m_pos; }
        inline const glm::vec3& getFront() const { return m_front; }
        inline const glm::vec2& getDisplayDim() const { return m_displayDim; }
        
        inline void setDisplayDim(const glm::vec2& v) { m_displayDim = v; }

};

#endif//__CAMERA_H