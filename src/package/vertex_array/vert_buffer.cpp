#include "vert_buffer.h"

VertBuffer::VertBuffer(const void* data, unsigned int size, GLenum usage)
{
    glGenBuffers(1, &m_id);
    glBindBuffer(GL_ARRAY_BUFFER, m_id);
    glBufferData(GL_ARRAY_BUFFER, size, data, usage);
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
