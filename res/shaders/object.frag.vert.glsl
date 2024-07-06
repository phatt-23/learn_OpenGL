#version 330 core
// #define COMPILE_VERT
// #define COMPILE_FRAG

#ifdef COMPILE_VERT
/* ------------------------------ COMPILE_VERT ------------------------------ */

layout (location = 0) in vec3 vi_Pos;
layout (location = 1) in vec3 vi_Normal;
layout (location = 2) in vec2 vi_TexCoord;
out vec3 vo_FragPos;
out vec3 vo_Normal;
out vec2 vo_TexCoord;
uniform mat4 vu_Model;
uniform mat4 vu_View;
uniform mat4 vu_Proj;

void main() {
    vo_FragPos = vec3(vu_Model * vec4(vi_Pos, 1.0));
    vo_Normal = mat3(transpose(inverse(vu_Model))) * vi_Normal;
    vo_TexCoord = vi_TexCoord;
    gl_Position = vu_Proj * vu_View * vec4(vo_FragPos, 1.0);
}
#endif//COMPILE_VERT

#ifdef COMPILE_FRAG
/* ------------------------------ COMPILE_FRAG ------------------------------ */

out vec4 fo_Color;

in vec3 vo_FragPos;
in vec3 vo_Normal;
in vec2 vo_TexCoord;

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    // sampler2D emission;
    float shininess;
};
struct Light {
    vec3 position;
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;

    float cutoff;
    float outerCutoff;
};

uniform vec3 fu_ViewPos;
uniform Material fu_Material;
uniform Light fu_Light;

void main() {
    vec3 norm = normalize(vo_Normal);
    vec3 lightSrcDir = normalize(fu_Light.position - vo_FragPos);
    // vec3 lightSrcDir = normalize(-fu_Light.direction);
    float diff = max(dot(norm, lightSrcDir), 0.0);
    
    vec3 viewDir = normalize(fu_ViewPos - vo_FragPos);
    vec3 reflectDir = reflect(-lightSrcDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 64.0 * fu_Material.shininess);

    // 3 main components    
    vec3 ambient = fu_Light.ambient * texture2D(fu_Material.diffuse, vo_TexCoord).rgb;
    vec3 diffuse = fu_Light.diffuse * diff * texture2D(fu_Material.diffuse, vo_TexCoord).rgb;
    vec3 specular = fu_Light.specular * spec * texture2D(fu_Material.specular, vo_TexCoord).rgb;

    // spotlight soft edges
    float theta = dot(lightSrcDir, normalize(-fu_Light.direction));
    float epsilon = fu_Light.cutoff - fu_Light.outerCutoff;
    float intensity = clamp((theta - fu_Light.outerCutoff) / epsilon, 0.0, 1.0); 
    diffuse *= intensity;
    specular *= intensity;

    // attenuation
    float dist = length(fu_Light.position - vo_FragPos);
    float attenuation = 1.0 / (fu_Light.constant + fu_Light.linear * dist + fu_Light.quadratic * dist * dist);
    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;

    // vec3 emission = texture2D(fu_Material.emission, vo_TexCoord).rgb;
    // if (specTexPos != vec3(0.0, 0.0, 0.0)) emission = vec3(0.0);

    vec3 result = ambient + diffuse + specular;
    fo_Color = vec4(result, 1.0);
}
#endif//COMPILE_FRAG
