#include "elem_buffer.h"
#include <GL/glew.h>

ElemBuffer::ElemBuffer(const unsigned int *data, const unsigned int count)
{
    glGenBuffers(1, &m_id);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_READ);
}

ElemBuffer::ElemBuffer(const std::vector<unsigned int> &indices)
    : m_indices(indices)
{
    glGenBuffers(1, &m_id);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(unsigned int), m_indices.data(), GL_STATIC_READ);
}

ElemBuffer::~ElemBuffer()
{
    glDeleteBuffers(1, &m_id);
}

void ElemBuffer::bind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
}

void ElemBuffer::unbind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
