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
    
    Texture2D(const std::string& filepath, Texture::Type type);
    void loadTextureFromFile(const std::string& filepath, Texture::Type type);
};

class Mesh
{
    private:
        VertArray m_VAO;
        VertBuffer m_VBO;
        ElemBuffer m_EBO;
        std::vector<Texture2D> m_textures;
        std::vector<Texture> m_Textures;

        void setup();
        void draw_with_Texture2D(Shader &shader);
        void draw_with_Texture(Shader &shader);

    public:
        Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture2D> textures);
        Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
        void draw(Shader& shader);
};

#endif//__MESH_MESH_H