#shader vertex
#version 330 core

layout (location = 0) in vec3 vi_Pos;
layout (location = 1) in vec3 vi_Color;
layout (location = 2) in vec2 vi_TexCoord;
out vec3 vo_Color;
out vec2 vo_TexCoord;

void main() {
    gl_Position = vec4(vi_Pos, 1.0);
    vo_Color = vi_Color;
    vo_TexCoord = vi_TexCoord;
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
