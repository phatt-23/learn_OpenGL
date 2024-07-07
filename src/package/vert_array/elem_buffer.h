#ifndef __ELEM_BUFFER_OBJECT_H
#define __ELEM_BUFFER_OBJECT_H

#include <vector>

class ElemBuffer
{
    private:
        unsigned int m_id;
        std::vector<unsigned int> m_indices;

    public:
        ElemBuffer(const unsigned int* data, const unsigned int count);
        ElemBuffer(const std::vector<unsigned int>& indices);
        ~ElemBuffer();
        void bind() const;
        void unbind() const;
        inline unsigned int getCount() const { return m_indices.size(); }
};

#endif//__ELEM_BUFFER_OBJECT_H