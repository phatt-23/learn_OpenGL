#ifndef __VERT_ARRAY_H
#define __VERT_ARRAY_H

#include "vert_buffer.h"
#include "vert_buffer_layout.h"
#include "elem_buffer.h"

class VertArray
{
    private:
        unsigned int m_id;
    
    public:
        VertArray();
        ~VertArray();
        
        void bind() const;
        void unbind() const;
        
        void addBuffer(const VertBuffer& vbo, const ElemBuffer& ebo, const VertBuffLayout& layout);
        void addBuffer(const VertBuffer& vbo, const VertBuffLayout& layout);
        
        inline unsigned int getId() const { return m_id; }
};

#endif//__VERT_ARRAY_H