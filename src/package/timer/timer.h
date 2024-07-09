#ifndef __TIMER_TIMER_H
#define __TIMER_TIMER_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Timer
{
    private:
        float m_deltaTime = 0.0f;
        float m_lastFrame = 0.0f;
    public:
        Timer();
        void nextFrame();
        inline float dt() const { return m_deltaTime; };
};

#endif//__TIMER_TIMER_H