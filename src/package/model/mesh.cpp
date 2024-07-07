#include "mesh.h"

void Mesh::setup()
{
    VertBuffLayout layout;
    layout.push<float>(3);
    layout.push<float>(3);
    layout.push<float>(2);
    m_vao.addBuffer(m_vbo, layout);
}

Mesh::Mesh(const std::vector<Vertex> &vertices, const std::vector<unsigned int> &indices, const std::vector<Texture> &textures)
    : m_vbo(vertices)
    , m_ebo(indices)
    , m_vao()
    , m_textures(textures)
{
    this->setup();
}

void Mesh::draw(Shader &shader)
{
    unsigned int diffNum = 0;
    unsigned int specNum = 0;

    for (unsigned int i = 0; i < m_textures.size(); ++i)
    {
        auto& tex = m_textures[i];
        tex.bind(i);

        std::string name = "material.";
        name += [tex, &diffNum, &specNum] {
            switch (tex.getType()) {
                case Texture::Type::Diffuse: return "diffuse" + std::to_string(diffNum++);
                case Texture::Type::Specular: return "specular" + std::to_string(specNum++);
            }
        }();

        shader.setUniInt(name, i);
    }
    glActiveTexture(GL_TEXTURE0);
    m_vao.bind();
    glDrawElements(GL_TRIANGLES, m_ebo.getCount(), GL_UNSIGNED_INT, 0);
    m_vao.unbind();
}
