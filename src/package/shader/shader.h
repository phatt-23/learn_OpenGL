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
        unsigned int ID;
        std::unordered_map<std::string, int> uniformLocationCache; 
        std::string filepath;

        ShaderProgramSource parseShaderSource(const std::string& filepath) const;
        unsigned int compileShader(unsigned int type, const std::string& source) const;
        unsigned int createProgram(const ShaderProgramSource& shaders);
        
    public:
        Shader(const std::string& filepath);
        ~Shader();
        
        void bind();
        void unbind();

        int getUniformLocation(const std::string& name);

        void setUniform1f(const std::string& name, float v0); 
        void setUniform2f(const std::string& name, float v0, float v1); 
        void setUniform3f(const std::string& name, float v0, float v1, float v2); 
        void setUniform4f(const std::string& name, float v0, float v1, float v2, float v3); 

        void setUniform1d(const std::string& name, double v0); 
        void setUniform2d(const std::string& name, double v0, double v1); 
        void setUniform3d(const std::string& name, double v0, double v1, double v2); 
        void setUniform4d(const std::string& name, double v0, double v1, double v2, double v3); 

        void setUniform2i(const std::string& name, int v0, int v1); 
        void setUniform1i(const std::string& name, int v0); 
        void setUniform3i(const std::string& name, int v0, int v1, int v2); 
        void setUniform4i(const std::string& name, int v0, int v1, int v2, int v3);

        void setUniform1ui(const std::string& name, float v0); 
        void setUniform2ui(const std::string& name, float v0, float v1); 
        void setUniform3ui(const std::string& name, float v0, float v1, float v2); 
        void setUniform4ui(const std::string& name, float v0, float v1, float v2, float v3); 

        void setUniformMat4(const std::string& name, const glm::mat4& m);
};

#endif//__SHADER_H