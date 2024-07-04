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
    vo_Normal = mat3(transpose(inverse(vu_Model))) * vi_Normal;
    vo_FragPos = vec3(vu_Model * vec4(vi_Pos, 1.0));
    gl_Position = vu_Proj * vu_View * vec4(vo_FragPos, 1.0);
}

#shader fragment
#version 330 core
out vec4 fo_Color;

in vec3 vo_Normal;
in vec3 vo_FragPos;

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};
struct Light {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform vec3 fu_ViewPos;
uniform Material fu_Material;
uniform Light fu_Light;

void main() {
    vec3 norm       = normalize(vo_Normal);
    vec3 lightSrcDir = normalize(fu_Light.position - vo_FragPos);
    float diff      = max(dot(norm, lightSrcDir), 0.0);
    
    vec3 viewDir    = normalize(fu_ViewPos - vo_FragPos);
    vec3 reflectDir = reflect(-lightSrcDir, norm);
    float spec      = pow(max(dot(viewDir, reflectDir), 0.0), 64.0 * fu_Material.shininess);
    
    vec3 ambient  = fu_Light.ambient * fu_Material.ambient;
    vec3 diffuse  = fu_Light.diffuse * (diff * fu_Material.diffuse);
    vec3 specular = fu_Light.specular * (spec * fu_Material.specular);

    vec3 result = (ambient + diffuse + specular); 
    fo_Color = vec4(result, 1.0);
}
