#include "camera.h"


void Camera::updateVectors()
{
    m_front.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
    m_front.y = sin(glm::radians(m_pitch));
    m_front.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
    m_front = glm::normalize(m_front);

    m_right = glm::normalize(glm::cross(m_front, m_worldUp));
    m_up = glm::normalize(glm::cross(m_right, m_front));
}

Camera::Camera(const glm::vec3 &pos, const glm::vec3 &up, float yaw, float pitch)
    : m_pos(pos)
    , m_front(CAM_DIRECTION)
    , m_up(up)
    , m_right(glm::cross(CAM_DIRECTION, CAM_WORLD_UP))
    , m_worldUp(CAM_WORLD_UP)
    , m_yaw(yaw)
    , m_pitch(pitch)
    , m_fov(CAM_FOV)
    , m_moveSpeed(CAM_MOVE_SPEED)
    , m_mouseSensi(CAM_MOUSE_SENSI)
{
    this->updateVectors();
}

Camera::~Camera()
{
}

void Camera::processKeyboard(Key key, float dt)
{
    switch (key) {
        case Key::W: {
            m_pos += m_moveSpeed * m_front * dt;
        } break;
        case Key::A: {
            m_pos -= m_moveSpeed * m_right * dt;
        } break;
        case Key::S: {
            m_pos -= m_moveSpeed * m_front * dt;
        } break;
        case Key::D: {
            m_pos += m_moveSpeed * m_right * dt;
        } break;
        default: break;
    };
}

void Camera::processMouseMove(float xoffset, float yoffset)
{
    m_yaw   += xoffset * m_mouseSensi;
    m_pitch += yoffset * m_mouseSensi;
    if (m_pitch >  CAM_PITCH_CONSTRAINT) m_pitch =  CAM_PITCH_CONSTRAINT;
    if (m_pitch < -CAM_PITCH_CONSTRAINT) m_pitch = -CAM_PITCH_CONSTRAINT;
    this->updateVectors();
}

void Camera::processMouseScroll(float yoffset)
{
    m_fov -= yoffset * 3.0f;
    if (m_fov < CAM_FOV_MIN) m_fov = CAM_FOV_MIN;
    if (m_fov > CAM_FOV_MAX) m_fov = CAM_FOV_MAX;
}
