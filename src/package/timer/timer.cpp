#include "timer.h"

Timer::Timer() : m_deltaTime(0.0), m_lastFrame(0.0)
{
}

void Timer::nextFrame()
{
    float currentFrame = glfwGetTime();
    m_deltaTime = currentFrame - m_lastFrame;
    m_lastFrame = currentFrame;
}