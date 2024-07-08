#include "mesh.h"
#include <cstddef>
#include "../renderer/renderer.h"
#include "../../vendor/stb/stb_image.h"

void Mesh::setup()
{
    VertBuffLayout layout;
    layout.push<float>(3);
    layout.push<float>(3);
    layout.push<float>(2);
    m_VAO.addBuffer(m_VBO, m_EBO, layout);
    m_VAO.unbind();
}

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture2D> textures)
    : m_VAO()
    , m_VBO(vertices)
    , m_EBO(indices)
{
    m_textures = textures;
    this->setup();
}

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures)
    : m_VAO()
    , m_VBO(vertices)
    , m_EBO(indices)
{
    m_Textures = textures;
    this->setup();
}

void Mesh::draw(Shader &shader)
{
    // this->draw_with_Texture2D(shader);
    this->draw_with_Texture(shader);
}

void Mesh::draw_with_Texture2D(Shader &shader)
{
    shader.bind();
    unsigned int diffNum = 0;
    unsigned int specNum = 0;
    for (unsigned int i = 0; i < m_textures.size(); ++i)
    {
        Texture2D& tex = m_textures[i];
        glActiveTexture(GL_TEXTURE0 + i);

        std::string name = "material.";
        name += [tex, &diffNum, &specNum] {
            switch (tex.type) {
                case Texture::Type::Diffuse: return "diffuse" + std::to_string(diffNum++);
                case Texture::Type::Specular: return "specular" + std::to_string(specNum++);
                default: return std::string("error");
            }
        }();

        shader.setUniInt(name, i);
        glBindTexture(GL_TEXTURE_2D, tex.id);
    }

    m_VAO.bind();
    glDrawElements(GL_TRIANGLES, m_EBO.getCount(), GL_UNSIGNED_INT, 0);
    m_VAO.unbind();
    
    glActiveTexture(GL_TEXTURE0);
}

void Mesh::draw_with_Texture(Shader &shader)
{
    shader.bind();
    unsigned int diffNum = 0;
    unsigned int specNum = 0;
    
    for (unsigned int i = 0; i < m_textures.size(); ++i)
    {
        Texture2D& tex = m_textures[i];
        glActiveTexture(GL_TEXTURE0 + i);

        std::string name = "material.";
        name += [tex, &diffNum, &specNum] {
            switch (tex.type) {
                case Texture::Type::Diffuse: return "diffuse" + std::to_string(diffNum++);
                case Texture::Type::Specular: return "specular" + std::to_string(specNum++);
                default: return std::string("error");
            }
        }();

        shader.setUniInt(name, i);
        glBindTexture(GL_TEXTURE_2D, tex.id);
        std::cout << "[Mesh draw()] [Texture2D] texture bound " << i << " " << m_textures.size() << std::endl;
    }

    for (unsigned int i = 0; i < m_Textures.size(); ++i)
    {
        Texture tex = m_Textures[i];
        tex.bind(i);

        std::string name = "material.";
        name += [tex, &diffNum, &specNum] {
            switch (tex.getType()) {
                case Texture::Type::Diffuse: return "diffuse" + std::to_string(diffNum++);
                case Texture::Type::Specular: return "specular" + std::to_string(specNum++);
                default: return std::string("error");
            }
        }();

        shader.setUniInt(name, i);
        std::cout << "[Mesh draw()] [Texture] texture bound " << i << " " << m_textures.size() << std::endl;
    }

    // glActiveTexture(GL_TEXTURE0);
    // shader.setUniInt("material.diffuse0", 0);
    // glBindTexture(GL_TEXTURE_2D, m_textures[0].id);

    // glActiveTexture(GL_TEXTURE1);
    // shader.setUniInt("material.specular0", 1);
    // glBindTexture(GL_TEXTURE_2D, m_textures[1].id);

    m_VAO.bind();
    glDrawElements(GL_TRIANGLES, m_EBO.getCount(), GL_UNSIGNED_INT, 0);
    m_VAO.unbind();
    
    glActiveTexture(GL_TEXTURE0);
}

Texture2D::Texture2D(const std::string& filepath, Texture::Type type)
    : type(type)
    , path(filepath) 
{
    glGenTextures(1, &this->id);

    int m_width, m_height, m_bpp;
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

        glBindTexture(GL_TEXTURE_2D, this->id);
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

void Texture2D::loadTextureFromFile(const std::string& filepath, Texture::Type type)
{
    this->type = type;
    this->path = filepath; 
    glGenTextures(1, &this->id);

    int width, height, nrComponents;
    unsigned char *data = stbi_load(filepath.c_str(), &width, &height, &nrComponents, 0);
    if (data)
    {
        GLenum format;
        if (nrComponents == 1) format = GL_RED;
        else if (nrComponents == 3) format = GL_RGB;
        else if (nrComponents == 4) format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, this->id);
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
