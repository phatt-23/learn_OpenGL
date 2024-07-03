#ifndef __VERT_BUFFER_LAYOUT_H
#define __VERT_BUFFER_LAYOUT_H

#include <vector>

struct VertBuffElem
{
    unsigned int type, count;
    unsigned char normalized;
    static unsigned int getSizeOfType(unsigned int type);
};

class VertBuffLayout
{
    private:
        std::vector<VertBuffElem> m_elems;
        unsigned int m_stride;

    public:
        VertBuffLayout();
        ~VertBuffLayout();

        template <typename T> void push(unsigned int count);
        template <> void push<float>(unsigned int count);
        template <> void push<unsigned int>(unsigned int count);
        template <> void push<unsigned char>(unsigned int count);

        inline const std::vector<VertBuffElem>& getElems() const { return m_elems; }
        inline unsigned int getStride() const { return m_stride; }
};

template <typename T>
void VertBuffLayout::push(unsigned int count) {
    static_assert(false && "[VertBuffLayout::push] Unsupported type, must be of [float, uint, uchar]");
    (void)count;
}

#endif//__VERT_BUFFER_LAYOUT_H