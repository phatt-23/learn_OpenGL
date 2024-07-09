#ifndef __VERT_ARRAY_VERTEX_H
#define __VERT_ARRAY_VERTEX_H

#include <glm/glm.hpp>

struct Vertex
{
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texCoords;
    glm::vec3 tangent;
    glm::vec3 bitangent;
};

#endif//__VERT_ARRAY_VERTEX_H