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
    static inline Vertex make(float p0, float p1, float p2, float n0, float n1, float n2, float t0, float t1)
    {
        return Vertex {
            .position = { p0, p1, p2 },
            .normal = { n0, n1, n2 },
            .texcoords = { t0, t1 },
        };
    }
};


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