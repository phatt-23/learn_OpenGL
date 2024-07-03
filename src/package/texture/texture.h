#ifndef __TEXTURE_H
#define __TEXTURE_H

#include <string>

class Texture
{
    private:
        unsigned int m_ID;
        const std::string m_filepath;
        unsigned char* m_data;
        int m_width, m_height, m_bpp;

    public:
        Texture(const std::string& filepath);
        ~Texture();

        void bind(unsigned int slot = 0) const;
        void unbind();

        inline int getWidth() const { return m_width; }
        inline int getHeight() const { return m_height; }
        inline int getBPP() const { return m_bpp; }

};

#endif//__TEXTURE_H