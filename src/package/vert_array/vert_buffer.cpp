#include "vert_buffer.h"
#include <cstddef>

VertBuffer::VertBuffer(const void* data, unsigned int size, GLenum usage)
{
    glGenBuffers(1, &m_id);
    glBindBuffer(GL_ARRAY_BUFFER, m_id);
    glBufferData(GL_ARRAY_BUFFER, size, data, usage);

    // WARNING: this is wack, assuming it is of type float
    float* d = (float*)data;
    for (std::size_t i = 0; i < size / sizeof(Vertex); ++i)
    {
        unsigned int off = i * sizeof(Vertex);
        m_vertices.push_back(Vertex {
            .position  = { d[0]+off, d[1]+off, d[2]+off },
            .normal    = { d[3]+off, d[4]+off, d[5]+off },
            .texcoords = { d[6]+off, d[7]+off },
        });
    }
}

VertBuffer::VertBuffer(const std::vector<Vertex> &vertices, GLenum usage)
{
    m_vertices = vertices;
    glGenBuffers(1, &m_id);
    glBindBuffer(GL_ARRAY_BUFFER, m_id);
    glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(Vertex), m_vertices.data(), usage);
}

VertBuffer::~VertBuffer()
{
    glDeleteBuffers(1, &m_id);
}

void VertBuffer::bind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, m_id);
}

void VertBuffer::unbind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
