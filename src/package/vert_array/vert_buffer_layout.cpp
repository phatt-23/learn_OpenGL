#include "vert_buffer_layout.h"
#include <GL/glew.h>
#include <iostream>

unsigned int VertBuffElem::getSizeOfType(unsigned int type)
{
    switch (type) {
        case GL_FLOAT:         return sizeof(float);
        case GL_UNSIGNED_INT:  return sizeof(unsigned int);  
        case GL_UNSIGNED_BYTE: return sizeof(unsigned char);
        default:               throw std::runtime_error("[VertBuffElem] Incompatible type!"); 
    };
    return 0; 
}

VertBuffLayout::VertBuffLayout()
    : m_stride(0)
{
}

VertBuffLayout::~VertBuffLayout()
{
}

template <>
void VertBuffLayout::push<float>(unsigned int count)
{
    m_elems.push_back(VertBuffElem{
        .type=GL_FLOAT, 
        .count=count, 
        .normalized=GL_FALSE
    });
    m_stride += count * sizeof(float);
}

template <>
void VertBuffLayout::push<unsigned int>(unsigned int count)
{
    m_elems.push_back(VertBuffElem{
        .type=GL_UNSIGNED_INT, 
        .count=count, 
        .normalized=GL_FALSE
    });
    m_stride += count * sizeof(unsigned int);
}

template <>
void VertBuffLayout::push<unsigned char>(unsigned int count)
{
    m_elems.push_back(VertBuffElem{
        .type=GL_UNSIGNED_BYTE, 
        .count=count, 
        .normalized=GL_TRUE
    });
    m_stride += count * sizeof(unsigned char);
}


