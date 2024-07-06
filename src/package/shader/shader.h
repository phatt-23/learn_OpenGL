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

        int getUniormLocation(const std::string& name);

        void setUniFloat(const std::string& name, float v);
        void setUniVec1f(const std::string& name, float v0); 
        void setUniVec2f(const std::string& name, float v0, float v1); 
        void setUniVec3f(const std::string& name, float v0, float v1, float v2); 
        void setUniVec4f(const std::string& name, float v0, float v1, float v2, float v3); 

        void setUniVec3f(const std::string& name, const glm::vec3& v); 
        void setUniVec4f(const std::string& name, const glm::vec4& v); 
        
        void setUniDouble(const std::string& name, double v);
        void setUniVec1d(const std::string& name, double v0); 
        void setUniVec2d(const std::string& name, double v0, double v1); 
        void setUniVec3d(const std::string& name, double v0, double v1, double v2); 
        void setUniVec4d(const std::string& name, double v0, double v1, double v2, double v3); 

        void setUniInt(const std::string& name, int v);
        void setUniVec1i(const std::string& name, int v0); 
        void setUniVec2i(const std::string& name, int v0, int v1); 
        void setUniVec3i(const std::string& name, int v0, int v1, int v2); 
        void setUniVec4i(const std::string& name, int v0, int v1, int v2, int v3);

        void setUniUInt(const std::string& name, unsigned int v);
        void setUniVec1ui(const std::string& name, unsigned int v0); 
        void setUniVec2ui(const std::string& name, unsigned int v0, unsigned int v1); 
        void setUniVec3ui(const std::string& name, unsigned int v0, unsigned int v1, unsigned int v2); 
        void setUniVec4ui(const std::string& name, unsigned int v0, unsigned int v1, unsigned int v2, unsigned int v3); 

        void setUniMat4(const std::string& name, const glm::mat4& m);
};

#endif//__SHADER_H