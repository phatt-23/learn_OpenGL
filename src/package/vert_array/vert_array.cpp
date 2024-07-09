#include "vert_array.h"
#include <GL/glew.h>
#include <iostream>

VertArray::VertArray() : m_id(0)
{
    glGenVertexArrays(1, &m_id);
}

VertArray::~VertArray()
{
    // std::cout << "[INFO] " << __FUNCTION__ << std::endl;
    glDeleteVertexArrays(1, &m_id);
}

void VertArray::bind() const
{
    glBindVertexArray(m_id);
}

void VertArray::unbind() const
{
    glBindVertexArray(0);
}

void VertArray::addBuffer(const VertBuffer &vbo, const ElemBuffer& ebo, const VertBuffLayout &layout)
{
    this->bind();
    vbo.bind();
    ebo.bind();
    std::size_t offset = 0;
    const auto& elems = layout.getElems();
    for (std::size_t i = 0; i < elems.size(); ++i) {
        const auto& e = elems[i];
        glVertexAttribPointer(i, e.count, e.type, e.normalized, layout.getStride(), (void*) offset);
        glEnableVertexAttribArray(i);
        offset += e.count * VertBuffElem::getSizeOfType(e.type);
    }
    this->unbind();
}

void VertArray::addBuffer(const VertBuffer &vbo, const VertBuffLayout &layout)
{
    this->bind();
    vbo.bind();
    std::size_t offset = 0;
    const auto& elems = layout.getElems();
    for (std::size_t i = 0; i < elems.size(); ++i) {
        const auto& e = elems[i];
        glVertexAttribPointer(i, e.count, e.type, e.normalized, layout.getStride(), (void*) offset);
        glEnableVertexAttribArray(i);
        offset += e.count * VertBuffElem::getSizeOfType(e.type);
    }
    this->unbind();
}
