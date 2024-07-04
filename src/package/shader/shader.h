#ifndef __SHADER_H
#define __SHADER_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <string>
#include <unordered_map>

class Shader
{
    struct ShaderProgramSource { std::string vertexShader, fragmentShader; };

    private:
        unsigned int m_id;
        std::unordered_map<std::string, int> m_uniformLocationCache; 
        std::string m_filepath;

        ShaderProgramSource parseShaderSource(const std::string& filepath) const;
        unsigned int compileShader(unsigned int type, const std::string& source) const;
        unsigned int createProgram(const ShaderProgramSource& shaders);
        
    public:
        Shader(const std::string& filepath);
        ~Shader();
        
        void bind() const;
        void unbind() const;

        int getUniformLocation(const std::string& name);

        void setUnifVec1f(const std::string& name, float v0); 
        void setUnifVec2f(const std::string& name, float v0, float v1); 
        void setUnifVec3f(const std::string& name, float v0, float v1, float v2); 
        void setUnifVec4f(const std::string& name, float v0, float v1, float v2, float v3); 

        void setUnifVec3f(const std::string& name, const glm::vec3& v); 
        void setUnifVec4f(const std::string& name, const glm::vec4& v); 

        void setUnifVec1d(const std::string& name, double v0); 
        void setUnifVec2d(const std::string& name, double v0, double v1); 
        void setUnifVec3d(const std::string& name, double v0, double v1, double v2); 
        void setUnifVec4d(const std::string& name, double v0, double v1, double v2, double v3); 

        void setUnifVec2i(const std::string& name, int v0, int v1); 
        void setUnifVec1i(const std::string& name, int v0); 
        void setUnifVec3i(const std::string& name, int v0, int v1, int v2); 
        void setUnifVec4i(const std::string& name, int v0, int v1, int v2, int v3);

        void setUnifVec1ui(const std::string& name, float v0); 
        void setUnifVec2ui(const std::string& name, float v0, float v1); 
        void setUnifVec3ui(const std::string& name, float v0, float v1, float v2); 
        void setUnifVec4ui(const std::string& name, float v0, float v1, float v2, float v3); 

        void setUnifMat4(const std::string& name, const glm::mat4& m);
};

#endif//__SHADER_H