#include "texture.h"
#include <GL/glew.h>
#include "../../vendor/stb/stb_image.h"
#include <iostream>

Texture2D::Texture2D(const std::string& filepath, Texture2D::Type type)
    : m_type(type)
    , m_filepath(filepath) 
{
    glGenTextures(1, &m_id);
    int m_width, m_height, m_bpp;

    stbi_set_flip_vertically_on_load(true);
    unsigned char* m_data = stbi_load(filepath.c_str(), &m_width, &m_height, &m_bpp, 0);
    if (m_data) 
    {
        GLenum format;
        switch (m_bpp) {
            case 1: format = GL_RED; break;
            case 3: format = GL_RGB; break;
            case 4: format = GL_RGBA; break;
            default: puts("You fucked up"), exit(1);
        }

        glBindTexture(GL_TEXTURE_2D, m_id);
        glTexImage2D(GL_TEXTURE_2D, 0, format, m_width, m_height, 0, format, GL_UNSIGNED_BYTE, m_data);
        glGenerateMipmap(GL_TEXTURE_2D);
    
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(m_data);
        std::cout << "[Texture INFO] (" << filepath << ") loaded successfuly" << std::endl; 
    } else {
        fprintf(stderr, "[Texture ERR] Failed to load an image (%s)!\n", filepath.c_str());
        stbi_image_free(m_data);
    }
}

void Texture2D::loadTextureFromFile(const std::string& filepath, Texture2D::Type type)
{
    m_type = type;
    m_filepath = filepath; 
    glGenTextures(1, &m_id);

    int width, height, nrComponents;
    unsigned char *data = stbi_load(filepath.c_str(), &width, &height, &nrComponents, 0);
    if (data)
    {
        GLenum format;
        if (nrComponents == 1) format = GL_RED;
        else if (nrComponents == 3) format = GL_RGB;
        else if (nrComponents == 4) format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, m_id);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    }
    else
    {
        std::cout << "Texture failed to load at path: " << filepath << std::endl;
        stbi_image_free(data);
    }
}

void Texture2D::bind(unsigned int slot)
{
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, m_id);
}



// Texture::Texture(const std::string &filepath, Type type)
//     : m_filepath(filepath)
//     , m_ID(0)
//     , m_type(type)
//     , m_slot(0)
// {
//     glGenTextures(1, &m_ID);
//     int m_width, m_height, m_bpp;

//     stbi_set_flip_vertically_on_load(true);
//     unsigned char* m_data = stbi_load(filepath.c_str(), &m_width, &m_height, &m_bpp, 0);
//     if (m_data) 
//     {
//         GLenum format;
//         switch (m_bpp) {
//             case 1: format = GL_RED; break;
//             case 3: format = GL_RGB; break;
//             case 4: format = GL_RGBA; break;
//             default: puts("You fucked up"), exit(1);
//         }

//         glBindTexture(GL_TEXTURE_2D, m_ID);
//         glTexImage2D(GL_TEXTURE_2D, 0, format, m_width, m_height, 0, format, GL_UNSIGNED_BYTE, m_data);
//         glGenerateMipmap(GL_TEXTURE_2D);
    
//         glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//         glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//         glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
//         glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

//         stbi_image_free(m_data);
//         std::cout << "[Texture INFO] (" << filepath << ") loaded successfuly" << std::endl; 
//     } else {
//         fprintf(stderr, "[Texture ERR] Failed to load an image (%s)!\n", filepath.c_str());
//         stbi_image_free(m_data);
//     }
// }

// Texture::~Texture()
// {
//     glDeleteTextures(1, &m_ID);
// }

// void Texture::bind(unsigned int slot)
// {
//     m_slot = slot;
//     glActiveTexture(GL_TEXTURE0 + slot);
//     glBindTexture(GL_TEXTURE_2D, m_ID);
// }

// void Texture::unbind() const
// {
//     glBindTexture(GL_TEXTURE_2D, 0);
// }
