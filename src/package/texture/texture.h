#ifndef __TEXTURE_H
#define __TEXTURE_H

#include <string>
#include <GL/glew.h>

class Texture2D
{
    public: 
        enum class Type { Diffuse, Specular, Normal, Height };

    private:
        unsigned int m_id;
        Type m_type;
        unsigned int m_slot;
        std::string m_filepath;

    public:
        Texture2D(const std::string& filepath, Type type);
        ~Texture2D();
        
        void bind(unsigned int slot = GL_TEXTURE0);

        inline unsigned int getId() const { return m_id; }
        inline Type getType() const { return m_type; }
        inline const std::string& getFilepath() const { return m_filepath; }
        inline unsigned int getSlot() const { return m_slot; }

        // void loadTextureFromFile(const std::string& filepath, Type type);
};


#endif//__TEXTURE_H