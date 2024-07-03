#shader vertex
#version 330 core

layout (location = 0) in vec3 vi_Pos;
uniform mat4 vu_Model;
uniform mat4 vu_View;
uniform mat4 vu_Proj;

void main() {
    gl_Position = vu_Proj * vu_View * vu_Model * vec4(vi_Pos, 1.0);
}

#shader fragment
#version 330 core

out vec4 fo_Color;
uniform vec3 fu_LightColor;

void main() {
    fo_Color = vec4(fu_LightColor, 1.0);
}