#include "texture.h"
#include <GL/glew.h>
#include "../../vendor/stb/stb_image.h"

Texture::Texture(const std::string &filepath, Type type)
    : m_filepath(filepath), m_ID(0), m_type(type), m_slot(0), m_data(nullptr), m_width(0), m_height(0), m_bpp(0)
{
    glGenTextures(1, &m_ID);
    glBindTexture(GL_TEXTURE_2D, m_ID);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    stbi_set_flip_vertically_on_load(true);
    m_data = stbi_load(filepath.c_str(), &m_width, &m_height, &m_bpp, 4);
    if (m_data) {
        GLenum format = (m_bpp == 4)? GL_RGBA : (m_bpp == 3)? GL_RGB : (m_bpp == 2)? GL_RG : GL_RED;
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_width, m_height, 0, format, GL_UNSIGNED_BYTE, m_data);
        glGenerateMipmap(GL_TEXTURE_2D);
        stbi_image_free(m_data);
    } else fprintf(stderr, "[Texture ERR] Failed to load an image (%s)!\n", filepath.c_str());
}

Texture::~Texture()
{
    glDeleteTextures(1, &m_ID);
}

void Texture::bind(unsigned int slot)
{
    m_slot = slot;
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, m_ID);
}

void Texture::unbind() const
{
    glActiveTexture(GL_TEXTURE0 + m_slot);
    glBindTexture(GL_TEXTURE_2D, 0);
}
