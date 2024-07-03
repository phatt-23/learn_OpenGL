#shader vertex
#version 330 core

layout (location = 0) in vec3 vi_Pos;
layout (location = 1) in vec3 vi_Color;
layout (location = 2) in vec2 vi_TexCoord;
out vec3 vo_Color;
out vec2 vo_TexCoord;
uniform mat4 vu_Model;
uniform mat4 vu_View;
uniform mat4 vu_Proj;

void main() {
    vo_Color = vi_Color;
    vo_TexCoord = vi_TexCoord;
    gl_Position = vu_Proj * vu_View * vu_Model * vec4(vi_Pos, 1.0);
}

#shader fragment
#version 330 core

in vec3 vo_Color;
in vec2 vo_TexCoord;
out vec4 fo_Color;
uniform sampler2D fu_Texture0;
uniform sampler2D fu_Texture1;

void main() {
    fo_Color = mix(
        texture2D(fu_Texture0, vo_TexCoord), 
        texture2D(fu_Texture1, vo_TexCoord), 
        0.2) * vec4(vo_Color, 1.0);
}
