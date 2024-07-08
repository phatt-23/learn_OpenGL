#ifndef __ELEM_BUFFER_OBJECT_H
#define __ELEM_BUFFER_OBJECT_H

#include <vector>
#include <GL/glew.h>

class ElemBuffer
{
    private:
        unsigned int m_id;
        std::vector<unsigned int> m_indices;

    public:
        ElemBuffer(const unsigned int* data, const unsigned int count, GLenum usage = GL_STATIC_DRAW);
        ElemBuffer(const std::vector<unsigned int> indices, GLenum usage = GL_STATIC_DRAW);
        ~ElemBuffer();
        void bind() const;
        void unbind() const;
        inline unsigned int getCount() const { return m_indices.size(); }
        inline const std::vector<unsigned int>& getIndices() const { return m_indices; }
};

#endif//__ELEM_BUFFER_OBJECT_H