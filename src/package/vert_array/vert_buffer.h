#ifndef __VERT_BUFFER_H
#define __VERT_BUFFER_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>

struct Vertex
{
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texcoords;
};


class VertBuffer
{
    private:
        unsigned int m_id;
        std::vector<Vertex> m_vertices;

    public:
        VertBuffer(const void* data, unsigned int size, GLenum usage = GL_STATIC_DRAW);
        VertBuffer(const std::vector<Vertex>& vertices, GLenum usage = GL_STATIC_DRAW);
        ~VertBuffer();
        void bind() const;
        void unbind() const;
};

#endif//__VERT_BUFFER_H