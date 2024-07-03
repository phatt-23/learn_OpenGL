#include "shader.h"
#include <sstream>
#include <fstream>
#include "../utils/utils.h"

Shader::ShaderProgramSource Shader::parseShaderSource(const std::string &filepath) const
{
    enum class ShaderType { None = -1, Vertex = 0, Fragment = 1 };
    
    std::ifstream stream(filepath);
    if (!stream.is_open()) {
        throwMessage("[Shader ERR] Filepath (%s) could not be read!", filepath.c_str()); 
    }

    std::string line;
    std::stringstream ss[2];
    ShaderType type = ShaderType::None;

    while (getline(stream, line)) {
        if (line.find("#shader") != std::string::npos) {
            if (line.find("vertex") != std::string::npos) type = ShaderType::Vertex;
            if (line.find("fragment") != std::string::npos) type = ShaderType::Fragment;
        } else if (type != ShaderType::None) {
            ss[int(type)] << line << std::endl;
        }
    }
    // std::cout << "[Vertex Shader]" << std::endl << ss[0].str() << std::endl << "[Fragment Shader]" << std::endl << ss[1].str() << std::endl;
    return ShaderProgramSource(ss[0].str(), ss[1].str());
}

unsigned int Shader::compileShader(unsigned int type, const std::string &source) const
{
    const char* src = source.c_str();
    unsigned int id = glCreateShader(type);
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);
    int success;
    int length;
    glGetShaderiv(id, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* infoLog = (char*) alloca(length * sizeof(char));
        glGetShaderInfoLog(id, length, &length, infoLog);
        glDeleteShader(id);
        std::cerr << std::format("[Shader :: ERR GL] Shader ({}) Compilation Failed ({}): {}", m_filepath, id, infoLog) << std::endl;
        return 0;
    }
    return id;
}

unsigned int Shader::createProgram(const ShaderProgramSource &shaders)
{
    unsigned int program = glCreateProgram();
    unsigned int vs = this->compileShader(GL_VERTEX_SHADER, shaders.vertexShader);
    unsigned int fs = this->compileShader(GL_FRAGMENT_SHADER, shaders.fragmentShader);
    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);
    glDetachShader(program, vs);
    glDetachShader(program, fs);
    glDeleteShader(vs);
    glDeleteShader(fs);
    return program;
}

Shader::Shader(const std::string &filepath) 
    : m_id(0)
    , m_filepath(filepath)
{
    m_id = this->createProgram(this->parseShaderSource(filepath));
}

Shader::~Shader()
{
    glDeleteProgram(m_id);
}

void Shader::bind() const
{
    glUseProgram(m_id);
}

void Shader::unbind() const
{
    glUseProgram(0);
}

int Shader::getUniformLocation(const std::string &name)
{
    if (m_uniformLocationCache.find(name) != m_uniformLocationCache.end())
        return m_uniformLocationCache[name];
    int location = glGetUniformLocation(m_id, name.c_str());
    if (location == -1) {
        std::cout << "[Shader WARN] Uniform (" << name << ") doesnt exist!" << std::endl;
    }
    m_uniformLocationCache[name] = location;
    return location;
}

void Shader::setUniform1f(const std::string& name, float v0) 
{
    glUniform1f(this->getUniformLocation(name), v0);
}

void Shader::setUniform2f(const std::string& name, float v0, float v1) 
{
    glUniform2f(this->getUniformLocation(name), v0, v1);
}

void Shader::setUniform3f(const std::string& name, float v0, float v1, float v2) 
{
    glUniform3f(this->getUniformLocation(name), v0, v1, v2);
}

void Shader::setUniform4f(const std::string& name, float v0, float v1, float v2, float v3) 
{
    glUniform4f(this->getUniformLocation(name), v0, v1, v2, v3);
}

void Shader::setUniform3f(const std::string &name, const glm::vec3 &v)
{
    glUniform3fv(this->getUniformLocation(name), 1, glm::value_ptr(v));
}

void Shader::setUniform4f(const std::string &name, const glm::vec4 &v)
{
    glUniform4fv(this->getUniformLocation(name), 1, glm::value_ptr(v));
}

void Shader::setUniform1d(const std::string& name, double v0) 
{
    glUniform1d(this->getUniformLocation(name), v0);
}

void Shader::setUniform2d(const std::string& name, double v0, double v1) 
{
    glUniform2d(this->getUniformLocation(name), v0, v1);
}

void Shader::setUniform3d(const std::string& name, double v0, double v1, double v2) 
{
    glUniform3d(this->getUniformLocation(name), v0, v1, v2);
}

void Shader::setUniform4d(const std::string& name, double v0, double v1, double v2, double v3) 
{
    glUniform4d(this->getUniformLocation(name), v0, v1, v2, v3);
}

void Shader::setUniform1i(const std::string& name, int v0) 
{
    glUniform1i(this->getUniformLocation(name), v0);
}

void Shader::setUniform2i(const std::string& name, int v0, int v1) 
{
    glUniform2i(this->getUniformLocation(name), v0, v1);
}

void Shader::setUniform3i(const std::string& name, int v0, int v1, int v2) 
{
    glUniform3i(this->getUniformLocation(name), v0, v1, v2);
}

void Shader::setUniform4i(const std::string& name, int v0, int v1, int v2, int v3) 
{
    glUniform4i(this->getUniformLocation(name), v0, v1, v2, v3);
}

void Shader::setUniform1ui(const std::string& name, float v0) 
{
    glUniform1ui(this->getUniformLocation(name), v0);
}

void Shader::setUniform2ui(const std::string& name, float v0, float v1) 
{
    glUniform2ui(this->getUniformLocation(name), v0, v1);
}

void Shader::setUniform3ui(const std::string& name, float v0, float v1, float v2) 
{
    glUniform3ui(this->getUniformLocation(name), v0, v1, v2);
}

void Shader::setUniform4ui(const std::string& name, float v0, float v1, float v2, float v3) 
{
    glUniform4ui(this->getUniformLocation(name), v0, v1, v2, v3);
}

void Shader::setUniformMat4(const std::string &name, const glm::mat4 &m)
{
    glUniformMatrix4fv(this->getUniformLocation(name), 1, GL_FALSE, glm::value_ptr(m));
}
