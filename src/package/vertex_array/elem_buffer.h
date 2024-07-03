#ifndef __ELEM_BUFFER_OBJECT_H
#define __ELEM_BUFFER_OBJECT_H

class ElemBuffer
{
    private:
        unsigned int m_id;
        unsigned int m_count;

    public:
        ElemBuffer(const unsigned int* data, const unsigned int count);
        ~ElemBuffer();
        void bind() const;
        void unbind() const;
        inline unsigned int getCount() const { return m_count; }
};

#endif//__ELEM_BUFFER_OBJECT_H