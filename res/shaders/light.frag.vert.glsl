#version 330 core
// #define COMPILE_VERT
// #define COMPILE_FRAG

#ifdef COMPILE_VERT
/* ------------------------------ COMPILE_VERT ----------------------------- */

layout (location = 0) in vec3 iPos;
uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

void main() {
    gl_Position = proj * view * model * vec4(iPos, 1.0);
}
#endif//COMPILE_VERT

#ifdef COMPILE_FRAG
/* ------------------------------ COMPILE_FRAG ------------------------------ */

out vec4 FragColor;

void main() {
    FragColor = vec4(1.0, 0.5, 0.4, 1.0);
}
#endif//COMPILE_FRAG
