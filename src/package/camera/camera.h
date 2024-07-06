#ifndef __CAMERA_H
#define __CAMERA_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

// >>> default settings
constexpr glm::vec3 CAM_POS = glm::vec3(0.0f, 0.0f, 3.0f);
constexpr glm::vec3 CAM_DIRECTION = glm::vec3(0.0f, 0.0f, -1.0f);
constexpr glm::vec3 CAM_WORLD_UP = glm::vec3(0.0f, 1.0f, 0.0f);
constexpr float CAM_YAW = -90.0f;
constexpr float CAM_PITCH = 0.0f;
constexpr float CAM_FOV = 45.0f;
constexpr float CAM_MOVE_SPEED = 5.0f;
constexpr float CAM_MOUSE_SENSI = 0.08f;
constexpr float CAM_PITCH_CONSTRAINT = 89.0f;
constexpr float CAM_FOV_MIN = 1.0f;
constexpr float CAM_FOV_MAX = 360.0f;

class Camera
{
    public:
        enum class Key
        {
            A, B, C, D, E, F, G, 
            H, I, J, K, L, M, N, 
            O, P, Q, R, S, T, U, 
            V, W, X, Y, Z,
            lCtrl, lShift, 
            rCtrl, rShift, 
            Space, Escape
        };

    private:
        glm::vec3 m_pos;
        glm::vec3 m_front;
        glm::vec3 m_up;
        glm::vec3 m_right;
        glm::vec3 m_worldUp;

        float m_yaw;
        float m_pitch;
        float m_fov;

        float m_moveSpeed;
        float m_mouseSensi;

        void updateVectors();

    public:
        Camera(const glm::vec3& pos = CAM_POS, const glm::vec3& up = CAM_WORLD_UP, float yaw = CAM_YAW, float pitch = CAM_PITCH);
        ~Camera();

        inline glm::mat4 getViewMat() const { return glm::lookAt(m_pos, m_pos + m_front, m_up); }
        inline float getFOV() const { return m_fov; }
        inline const glm::vec3& getPos() const { return m_pos; }
        inline const glm::vec3& getFront() const { return m_front; }

        void processKeyboard(Key key, float dt, unsigned char type = GLFW_PRESS);
        void processMouseMove(float xoffset, float yoffset);
        void processMouseScroll(float yoffset);
};

#endif//__CAMERA_H