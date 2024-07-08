#ifndef __MESH_MESH_H
#define __MESH_MESH_H

#include <vector>
#include <GL/glew.h>
#include <glm/glm.hpp>

#include "../texture/texture.h"
#include "../shader/shader.h"
#include "../vert_array/vert_array.h"

struct Texture2D
{
    unsigned int id;
    Texture::Type type;
    std::string path;
};

class Mesh
{
    private:
        std::vector<Vertex> m_vertices;
        std::vector<unsigned int> m_indices;
        std::vector<Texture2D> m_textures;
        VertArray m_VAO;
        VertBuffer m_VBO;
        ElemBuffer m_EBO;

        void setup();

    public:
        Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture2D> textures);
        void draw(Shader& shader);
};

#endif//__MESH_MESH_H