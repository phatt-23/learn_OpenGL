#include "texture.h"
#include <GL/glew.h>
#include "../../vendor/stb/stb_image.h"
#include <iostream>
#include <stdexcept>

#if 0
    constexpr auto TEXTURE_GL_MIPMAP_PROFILE_CONFIG = GL_LINEAR_MIPMAP_LINEAR
    constexpr auto TEXTURE_GL_PROFILE_CONFIG        = GL_LINEAR
#else
    constexpr auto TEXTURE_GL_MIPMAP_PROFILE_CONFIG = GL_NEAREST_MIPMAP_NEAREST;
    constexpr auto TEXTURE_GL_PROFILE_CONFIG        = GL_NEAREST;
#endif

Texture2D::Texture2D(const std::string& filepath, Texture2D::Type type)
    : m_type(type)
    , m_slot(GL_TEXTURE0)
    , m_filepath(filepath)
{
    glGenTextures(1, &m_id);
    int m_width, m_height, m_bpp;

    stbi_set_flip_vertically_on_load(true);

    unsigned char* m_data = stbi_load(filepath.c_str(), &m_width, &m_height, &m_bpp, 0);
    if (m_data) 
    {
        GLenum format = [m_bpp] {
            switch (m_bpp) {
                case 1: return GL_RED;
                case 3: return GL_RGB;
                case 4: return GL_RGBA;
                default: break;
            }
            throw std::runtime_error(std::format("Format can only be 1, 3, 4, {} was given!", m_bpp));
        }();

        glBindTexture(GL_TEXTURE_2D, m_id);
        glTexImage2D(GL_TEXTURE_2D, 0, format, m_width, m_height, 0, format, GL_UNSIGNED_BYTE, m_data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, TEXTURE_GL_MIPMAP_PROFILE_CONFIG);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, TEXTURE_GL_PROFILE_CONFIG);

    } else
       throw std::runtime_error( std::format("[Texture ERR] Failed to load an image ({})!\n", filepath.c_str()) );

    stbi_image_free(m_data);
}

Texture2D::~Texture2D()
{
    // std::cout << __PRETTY_FUNCTION__ << std::endl;
    glDeleteTextures(1, &m_id);
}

void Texture2D::bind(unsigned int slot)
{
    m_slot = slot;
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, m_id);
}
