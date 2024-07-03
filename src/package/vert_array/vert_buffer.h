#ifndef __VERT_BUFFER_H
#define __VERT_BUFFER_H

#include <GL/glew.h>

class VertBuffer
{
    private:
        unsigned int m_id;

    public:
        VertBuffer(const void* data, unsigned int size, GLenum usage = GL_STATIC_DRAW);
        ~VertBuffer();
        void bind() const;
        void unbind() const;
};

#endif//__VERT_BUFFER_H