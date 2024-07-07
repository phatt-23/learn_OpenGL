#ifndef __MESH_MESH_H
#define __MESH_MESH_H

#include <vector>
#include <GL/glew.h>
#include <glm/glm.hpp>

#include "../texture/texture.h"
#include "../shader/shader.h"
#include "../vert_array/vert_array.h"

class Mesh
{
    private:
        VertBuffer m_vbo;
        ElemBuffer m_ebo;
        VertArray m_vao;

        std::vector<Texture> m_textures;
        
        void setup();

    public:
        Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, const std::vector<Texture>& textures);
        void draw(Shader& shader);
};

#endif//__MESH_MESH_H