#include "camera.h"
#include <GLFW/glfw3.h>
#include <functional>
#include <unordered_map>


static inline float clampFloat(float value, float low, float high) {
    if (value > high) return high;
    if (value < low)  return low;
    return value;
}

static inline float wrapFloat(float value, float low, float high) {
    if (value > high) return low;    
    if (value < low) return high;
    return value;
}

void Camera::updateVectors()
{
    m_front.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
    m_front.y = sin(glm::radians(m_pitch));
    m_front.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
    m_front = glm::normalize(m_front);

    m_right = glm::normalize(glm::cross(m_front, m_worldUp));
    m_up = glm::normalize(glm::cross(m_right, m_front));

    m_yaw = wrapFloat(m_yaw, -180.0f, 180.0f);
    m_pitch = clampFloat(m_pitch, -CAM_PITCH_CONSTRAINT, CAM_PITCH_CONSTRAINT);

    m_MouseHandler.resetLastCursor();
}

Camera::Camera(GLFWwindow* window, const glm::vec3 &pos, const glm::vec3& front, const glm::vec3 &up, float yaw, float pitch)
    : m_pos(pos)
    , m_front(front)
    , m_up(up)
    , m_right(glm::cross(front, up))
    , m_worldUp(CAM_UP)
    , m_yaw(yaw)
    , m_pitch(pitch)
    , m_fov(CAM_FOV)
    , m_moveSpeed(CAM_MOVE_SPEED)
    , m_MouseHandler(window, CAM_MOUSE_SENSI, CAM_SCROLL_SENSI)
{
    this->updateVectors();
}

Camera::~Camera()
{
}

void Camera::processInput(GLFWwindow *window, float dt)
{
    this->processKeyboard(window, dt);
    this->processMouseMove(window);
    this->processMouseScroll(window);
}

void Camera::debugInfo()
{
    ImGui::Begin("Camera");
        ImGui::DragFloat3("position",    &m_pos[0]);
        ImGui::DragFloat3("front",       &m_front[0]);
        ImGui::DragFloat ("yaw",         &m_yaw);
        ImGui::DragFloat ("pitch",       &m_pitch);
        ImGui::DragFloat2("last_cursor", &m_MouseHandler.getLastCursorRef()[0]);
        ImGui::DragFloat("fov",          &m_fov);
        ImGui::InputInt("mouse_move_mode", &m_MouseHandler.getMouseMoveModeRef());
    ImGui::End();
}

void Camera::processKeyboard(GLFWwindow *window, float dt)
{
    float moveSpeedMultiplier = (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)? 3.0f : 1.0f;
    glm::vec3 forward = glm::normalize(glm::cross(m_worldUp, m_right));
    glm::vec3 right = m_right;
    glm::vec3 up = m_worldUp;

    static std::unordered_map<int, std::function<void()>> keyActionsPress = {
        {GLFW_KEY_W,            [&]{ m_pos += m_moveSpeed * forward * dt * moveSpeedMultiplier;  }},
        {GLFW_KEY_A,            [&]{ m_pos -= m_moveSpeed * right * dt * moveSpeedMultiplier;    }},
        {GLFW_KEY_S,            [&]{ m_pos -= m_moveSpeed * forward * dt * moveSpeedMultiplier;  }},
        {GLFW_KEY_D,            [&]{ m_pos += m_moveSpeed * right * dt * moveSpeedMultiplier;    }},
        {GLFW_KEY_SPACE,        [&]{ m_pos += m_moveSpeed * up * dt * moveSpeedMultiplier;       }},
        {GLFW_KEY_LEFT_CONTROL, [&]{ m_pos -= m_moveSpeed * up * dt * moveSpeedMultiplier;       }},
        {GLFW_KEY_ESCAPE,       [&]{ glfwSetWindowShouldClose(window, true);                     }},
    };

    for (const auto& [key, action] : keyActionsPress) {
        if (glfwGetKey(window, key) == GLFW_PRESS) 
            action();
    }
}

void Camera::processMouseMove(GLFWwindow* window)
{
    static int period = 30;
    static int tick {};
    static bool clicked {};

    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_MIDDLE) == GLFW_PRESS && !clicked) {
        m_MouseHandler.setMouseMoveMode(!m_MouseHandler.getMouseMoveMode());
        clicked = true;
    }

    if (m_MouseHandler.getMouseMoveMode() == 1) {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        m_yaw   += m_MouseHandler.getMouseSensi() * (m_MouseHandler.getCursor().x - m_MouseHandler.getLastCursor().x);
        m_pitch += m_MouseHandler.getMouseSensi() * (m_MouseHandler.getLastCursor().y - m_MouseHandler.getCursor().y);
    }

    if (m_MouseHandler.getMouseMoveMode() == 0) {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }

    ImGui::Begin("tick");
    ImGui::SliderInt("current_tick", &tick, 0, period, "tick: %d");
    ImGui::End();

    tick++;
    if (tick > period) {
        clicked = false;
        tick = 0;
    }

    this->updateVectors();
}

void Camera::processMouseScroll(GLFWwindow* window)
{
    m_fov -= m_MouseHandler.getScrollSensi() * m_MouseHandler.getScrollY();
    if (m_fov < CAM_FOV_MIN) m_fov = CAM_FOV_MIN;
    if (m_fov > CAM_FOV_MAX) m_fov = CAM_FOV_MAX;

    m_MouseHandler.resetScroll();
}
