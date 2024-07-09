#ifndef __VERT_BUFFER_H
#define __VERT_BUFFER_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>

#include "vertex.h"

class VertBuffer
{
    private:
        unsigned int m_id;

    public:
        VertBuffer(const void* data, unsigned int size, GLenum usage = GL_STATIC_DRAW);
        VertBuffer(const std::vector<Vertex>& vertices, GLenum usage = GL_STATIC_DRAW);
        ~VertBuffer();

        void bind() const;
        void unbind() const;
        
        inline unsigned int getId() const { return m_id; }
};

#endif//__VERT_BUFFER_H