#version 330 core
// #define COMPILE_VERT
// #define COMPILE_FRAG

#ifdef COMPILE_VERT
/* ------------------------------ COMPILE_VERT ----------------------------- */

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

out vec2 TexCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

void main()
{
    TexCoords = aTexCoords;    
    gl_Position = proj * view * model * vec4(aPos, 1.0);
}
#endif//COMPILE_VERT

#ifdef COMPILE_FRAG
/* ------------------------------ COMPILE_FRAG ------------------------------ */

out vec4 FragColor;

in vec2 TexCoords;

struct Material {
    sampler2D diffuse0;
    sampler2D specular0;
};

uniform Material material;

void main()
{    
    FragColor = texture2D(material.diffuse0, TexCoords);
}
#endif//COMPILE_FRAG
