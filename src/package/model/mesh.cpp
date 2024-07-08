#include "mesh.h"
#include <cstddef>
#include "../renderer/renderer.h"

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
    m_vertices = vertices;
    m_indices = indices;
    m_textures = textures;
    this->setup();
}

void Mesh::draw(Shader &shader)
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
