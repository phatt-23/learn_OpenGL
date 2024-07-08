#ifndef __TEXTURE_H
#define __TEXTURE_H

#include <string>

class Texture
{
    public:
        enum class Type { Diffuse, Specular };

    private:
        unsigned int m_ID;
        Type m_type;
        int m_slot;
        std::string m_filepath;

    public:
        Texture(const std::string& filepath, Type type);
        ~Texture();

        void bind(unsigned int slot = 0);
        void unbind() const;

        inline Type getType() const { return m_type; }
        inline int getSlot() const { return m_slot; }
        // inline int getWidth() const { return m_width; }
        // inline int getHeight() const { return m_height; }
        // inline int getBPP() const { return m_bpp; }
        inline const std::string& getFilepath() const { return m_filepath; }
        inline unsigned int getId() const { return m_ID; }
};

#endif//__TEXTURE_H