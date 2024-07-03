#shader vertex
#version 330 core

layout (location = 0) in vec3 vi_Pos;
layout (location = 1) in vec3 vi_Normal;
out vec3 vo_Normal;
out vec3 vo_FragPos;
uniform mat4 vu_Model;
uniform mat4 vu_View;
uniform mat4 vu_Proj;

void main() {
    vo_Normal = vi_Normal;
    vo_FragPos = vec3(vu_Model * vec4(vi_Pos, 1.0));
    gl_Position = vu_Proj * vu_View * vu_Model * vec4(vi_Pos, 1.0);
}

#shader fragment
#version 330 core

in vec3 vo_Normal;
in vec3 vo_FragPos;
out vec4 fo_Color;
uniform vec3 fu_ObjectColor;
uniform vec3 fu_LightSrcColor;
uniform vec3 fu_LightSrcPos;

void main() {
    vec3 lightSrcDir = normalize(fu_LightSrcPos - vo_FragPos);
    vec3 normal = normalize(vo_Normal);
    float diff = max(dot(normal, lightSrcDir), 0.0);
    vec3 diffuse = diff * fu_LightSrcColor;
    
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * fu_LightSrcColor;
    
    vec3 result = (ambient + diffuse) * fu_ObjectColor; 
    fo_Color = vec4(result, 1.0);
}
