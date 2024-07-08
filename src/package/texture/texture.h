#ifndef __TEXTURE_H
#define __TEXTURE_H

#include <string>
#include <GL/glew.h>

class Texture2D
{
    public: 
        enum class Type { Diffuse, Specular };

    private:
        unsigned int m_id;
        Type m_type;
        std::string m_filepath;

    public:
        Texture2D(const std::string& filepath, Type type);
        void loadTextureFromFile(const std::string& filepath, Type type);

        void bind(unsigned int slot = GL_TEXTURE0);

        inline unsigned int getId() const { return m_id; }
        inline Type getType() const { return m_type; }
        inline const std::string& getFilepath() const { return m_filepath; }
};


#endif//__TEXTURE_H

// class Texture
// {
//     public:
//         enum class Type { Diffuse, Specular };

//     private:
//         unsigned int m_ID;
//         Type m_type;
//         int m_slot;
//         std::string m_filepath;

//     public:
//         Texture(const std::string& filepath, Type type);
//         ~Texture();

//         void bind(unsigned int slot = 0);
//         void unbind() const;

//         inline Type getType() const { return m_type; }
//         inline int getSlot() const { return m_slot; }
//         // inline int getWidth() const { return m_width; }
//         // inline int getHeight() const { return m_height; }
//         // inline int getBPP() const { return m_bpp; }
//         inline const std::string& getFilepath() const { return m_filepath; }
//         inline unsigned int getId() const { return m_ID; }
// };