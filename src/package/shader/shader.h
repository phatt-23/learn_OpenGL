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
        Shader();
        Shader(const std::string& filepath);
        ~Shader();
        
        void bind() const;
        void unbind() const;

        int getUniormLocation(const std::string& name);

        void setFloat(const std::string& name, float v);
        void setVec1f(const std::string& name, float v0); 
        void setVec2f(const std::string& name, float v0, float v1); 
        void setVec3f(const std::string& name, float v0, float v1, float v2); 
        void setVec4f(const std::string& name, float v0, float v1, float v2, float v3); 

        void setVec3f(const std::string& name, const glm::vec3& v); 
        void setVec4f(const std::string& name, const glm::vec4& v); 
        
        void setDouble(const std::string& name, double v);
        void setVec1d(const std::string& name, double v0); 
        void setVec2d(const std::string& name, double v0, double v1); 
        void setVec3d(const std::string& name, double v0, double v1, double v2); 
        void setVec4d(const std::string& name, double v0, double v1, double v2, double v3); 

        void setInt(const std::string& name, int v);
        void setVec1i(const std::string& name, int v0); 
        void setVec2i(const std::string& name, int v0, int v1); 
        void setVec3i(const std::string& name, int v0, int v1, int v2); 
        void setVec4i(const std::string& name, int v0, int v1, int v2, int v3);

        void setUInt(const std::string& name, unsigned int v);
        void setVec1ui(const std::string& name, unsigned int v0); 
        void setVec2ui(const std::string& name, unsigned int v0, unsigned int v1); 
        void setVec3ui(const std::string& name, unsigned int v0, unsigned int v1, unsigned int v2); 
        void setVec4ui(const std::string& name, unsigned int v0, unsigned int v1, unsigned int v2, unsigned int v3); 

        void setMat4(const std::string& name, const glm::mat4& m);
};

#endif//__SHADER_H