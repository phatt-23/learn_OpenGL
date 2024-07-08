#include "vert_buffer.h"
#include <cstddef>

VertBuffer::VertBuffer(const void *data, unsigned int size, GLenum usage)
{
    glGenBuffers(1, &m_id);
    glBindBuffer(GL_ARRAY_BUFFER, m_id);
    glBufferData(GL_ARRAY_BUFFER, size, data, usage);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

VertBuffer::VertBuffer(const std::vector<Vertex>& vertices, GLenum usage)
{
    glGenBuffers(1, &m_id);
    glBindBuffer(GL_ARRAY_BUFFER, m_id);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), usage);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
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
