#ifndef __MESH_MESH_H
#define __MESH_MESH_H

#include <vector>
#include <GL/glew.h>
#include <glm/glm.hpp>

#include "../texture/texture.h"
#include "../shader/shader.h"
#include "../vert_array/vert_array.h"
#include "../vert_array/vertex.h"

class Mesh
{
    private:
        VertArray m_VAO;
        VertBuffer m_VBO;
        ElemBuffer m_EBO;
        std::vector<Texture2D*> m_textures;

        void setup();

    public:
        Mesh(const std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture2D*> textures);
        ~Mesh();
        void draw(Shader& shader);
};

#endif//__MESH_MESH_H