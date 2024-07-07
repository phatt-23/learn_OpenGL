#include "shader.h"
#include <sstream>
#include <fstream>
#include <format>
#include "../utils/utils.h"

Shader::ShaderProgramSource Shader::parseShaderSource(const std::string &filepath) const
{
    enum class ShaderType { None = -1, Vertex = 0, Fragment = 1 };

    auto _find = [](const std::string& buffer, const std::string& expr){ 
        return buffer.find(expr) != std::string::npos; 
    };

    std::ifstream stream(filepath);
    if (!stream.is_open()) {
        throwMessage("[Shader ERR] Filepath (%s) could not be read!", filepath.c_str()); 
    }

    std::string line;
    std::stringstream ss[2];
    ShaderType type = ShaderType::None;

    while (getline(stream, line)) 
    {
        if (_find(line, "#shader") || _find(line, "#ifdef")) 
        {
            if (_find(line, "vertex") || _find(line, "COMPILE_VERT"))
            {
                type = ShaderType::Vertex;
                ss[int(type)] << "#version 330 core" << std::endl << "#define COMPILE_VERT" << std::endl;
            }

            if (_find(line, "fragment") || _find(line, "COMPILE_FRAG")) 
            {
                type = ShaderType::Fragment;
                ss[int(type)] << "#version 330 core" << std::endl << "#define COMPILE_FRAG" << std::endl;
            }
        }

        if (type != ShaderType::None) 
            ss[int(type)] << line << std::endl;
    }

    std::cout
        << "[Compiling Shaders (" << filepath << ")]" << std::endl 
        << "<Vertex Shader> :: length=" << ss[0].str().length() << std::endl
        << ss[0].str() 
        << "</Vertex Shader>" << std::endl 
        << "<Fragment Shader> :: length=" << ss[1].str().length() << std::endl
        << ss[1].str() 
        << "</Fragment Shader>" << std::endl;
    
    return ShaderProgramSource{ ss[0].str(), ss[1].str() };
}

unsigned int Shader::compileShader(unsigned int type, const std::string &source) const
{
    const char* src = source.c_str();
    unsigned int id = glCreateShader(type);
    int success;
    int length;
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);
    glGetShaderiv(id, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* infoLog = (char*) alloca(length * sizeof(char));
        glGetShaderInfoLog(id, length, &length, infoLog);
        glDeleteShader(id);
        std::cerr << std::format("[Shader ({}) ERR] ({}) shader compile fail: {}", 
            m_filepath, (type==GL_VERTEX_SHADER)? "Vertex" : "Fragment", infoLog) << std::endl;
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

int Shader::getUniormLocation(const std::string &name)
{
    if (m_uniformLocationCache.find(name) != m_uniformLocationCache.end())
        return m_uniformLocationCache[name];
    int location = glGetUniformLocation(m_id, name.c_str());
    if (location == -1) {
        std::cout << std::format("[Shader ({}) WARN] Uniform ({}) doesnt exist!", m_filepath, name) << std::endl;
    }
    m_uniformLocationCache[name] = location;
    return location;
}

void Shader::setUniFloat(const std::string &name, float v)
{
    glUniform1f(this->getUniormLocation(name), v);
}

void Shader::setUniVec1f(const std::string &name, float v0)
{
    glUniform1f(this->getUniormLocation(name), v0);
}

void Shader::setUniVec2f(const std::string& name, float v0, float v1) 
{
    glUniform2f(this->getUniormLocation(name), v0, v1);
}

void Shader::setUniVec3f(const std::string& name, float v0, float v1, float v2) 
{
    glUniform3f(this->getUniormLocation(name), v0, v1, v2);
}

void Shader::setUniVec4f(const std::string& name, float v0, float v1, float v2, float v3) 
{
    glUniform4f(this->getUniormLocation(name), v0, v1, v2, v3);
}

void Shader::setUniVec3f(const std::string &name, const glm::vec3 &v)
{
    glUniform3fv(this->getUniormLocation(name), 1, glm::value_ptr(v));
}

void Shader::setUniVec4f(const std::string &name, const glm::vec4 &v)
{
    glUniform4fv(this->getUniormLocation(name), 1, glm::value_ptr(v));
}

void Shader::setUniDouble(const std::string &name, double v)
{
    glUniform1d(this->getUniormLocation(name), v);
}

void Shader::setUniVec1d(const std::string &name, double v0)
{
    glUniform1d(this->getUniormLocation(name), v0);
}

void Shader::setUniVec2d(const std::string& name, double v0, double v1) 
{
    glUniform2d(this->getUniormLocation(name), v0, v1);
}

void Shader::setUniVec3d(const std::string& name, double v0, double v1, double v2) 
{
    glUniform3d(this->getUniormLocation(name), v0, v1, v2);
}

void Shader::setUniVec4d(const std::string& name, double v0, double v1, double v2, double v3) 
{
    glUniform4d(this->getUniormLocation(name), v0, v1, v2, v3);
}

void Shader::setUniInt(const std::string &name, int v)
{
    glUniform1i(this->getUniormLocation(name), v);
}

void Shader::setUniVec1i(const std::string &name, int v0)
{
    glUniform1i(this->getUniormLocation(name), v0);
}

void Shader::setUniVec2i(const std::string& name, int v0, int v1) 
{
    glUniform2i(this->getUniormLocation(name), v0, v1);
}

void Shader::setUniVec3i(const std::string& name, int v0, int v1, int v2) 
{
    glUniform3i(this->getUniormLocation(name), v0, v1, v2);
}

void Shader::setUniVec4i(const std::string& name, int v0, int v1, int v2, int v3) 
{
    glUniform4i(this->getUniormLocation(name), v0, v1, v2, v3);
}

void Shader::setUniUInt(const std::string &name, unsigned int v)
{
    glUniform1ui(this->getUniormLocation(name), v);
}

void Shader::setUniVec1ui(const std::string& name, unsigned int v0) 
{
    glUniform1ui(this->getUniormLocation(name), v0);
}

void Shader::setUniVec2ui(const std::string& name, unsigned int v0, unsigned int v1) 
{
    glUniform2ui(this->getUniormLocation(name), v0, v1);
}

void Shader::setUniVec3ui(const std::string& name, unsigned int v0, unsigned int v1, unsigned int v2) 
{
    glUniform3ui(this->getUniormLocation(name), v0, v1, v2);
}

void Shader::setUniVec4ui(const std::string& name, unsigned int v0, unsigned int v1, unsigned int v2, unsigned int v3) 
{
    glUniform4ui(this->getUniormLocation(name), v0, v1, v2, v3);
}

void Shader::setUniMat4(const std::string &name, const glm::mat4 &m)
{
    glUniformMatrix4fv(this->getUniormLocation(name), 1, GL_FALSE, glm::value_ptr(m));
}
