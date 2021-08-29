#include "Shader.h"
#include <iostream>
#include <sstream>
#include "../core/glfunctions.h"

// TODO: REPLACE WITH LOG SYSTEM
#define DEBUGGING_GL 1

static GLuint compileShader(const char* src, GLuint type)
{
    GLuint id = glCreateShader(type);
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

#ifdef DEBUGGING_GL
    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    
    if (result == GL_FALSE)
    {
        GLsizei log_length = 0;
        GLchar message[1024];
        std::cout << "GLShader compilation error:\n";
        glGetShaderInfoLog(id, 1024, &log_length, message);
        std::cout << message << "\n";
        glDeleteShader(id);
        return 0;
    }
#endif

    return id;
}

static GLuint createShader(const std::string& vertexShader, const std::string& fragmentShader, const std::string& geometryShader)
{
    GLuint program = glCreateProgram();
    GLuint vs = compileShader(vertexShader.c_str(), GL_VERTEX_SHADER);
    GLuint fs = compileShader(fragmentShader.c_str(), GL_FRAGMENT_SHADER);
    GLuint gs;
    glAttachShader(program, vs); glAttachShader(program, fs);

    if (geometryShader.length())
    {
        gs = compileShader(geometryShader.c_str(), GL_GEOMETRY_SHADER);
        glAttachShader(program, gs);
    }

    glLinkProgram(program);
    glValidateProgram(program);

#ifdef DEBUGGING_GL
    int result;
    glGetProgramiv(program, GL_VALIDATE_STATUS, &result);

    if (result == GL_FALSE)
    {
        GLsizei log_length = 0;
        GLchar message[1024];
        std::cout << "GLProgram validation error:\n";
        glGetProgramInfoLog(program, 1024, &log_length, message);
        std::cout << message << "\n";
        return 0;
    }
#endif

    glDeleteShader(vs); glDeleteShader(fs);
    if (geometryShader.length())
        glDeleteShader(gs);
    return program;
}

Shader::Shader(const std::string& shader, bool hasGeometryShader)
{
    // Split shader
    std::istringstream ss(shader);
    std::string vertexShader, fragmentShader;
    std::string geometryShader = "";

    // Dolar sign used as a delimiter
    std::getline(ss, vertexShader, '$');

    if (hasGeometryShader)
        std::getline(ss, geometryShader);

    std::getline(ss, fragmentShader, '$');

    mID = createShader(vertexShader, fragmentShader, geometryShader);
}

Shader::Shader(const std::string& vertexShader, const std::string& fragmentShader)
{
    mID = createShader(vertexShader, fragmentShader, "");
}

Shader::Shader(const std::string& vertexShader, const std::string& geometryShader, const std::string& fragmentShader)
{
    mID = createShader(vertexShader, fragmentShader, geometryShader);
}

Shader::~Shader()
{
    glDeleteProgram(mID);
}

void Shader::bind() const
{
    glUseProgram(mID);
}

void Shader::unbind() const
{
    glUseProgram(0);
}

// FLOAT
void Shader::setUniform(const std::string& name, float v)
{
    int location = this->getUniformLocation(name);
    glUniform1f(location, v);
}
void Shader::setUniform(const std::string& name, const jdw::Vec2f& vec)
{
    int location = this->getUniformLocation(name);
    glUniform2f(location, vec.x, vec.y);
}
void Shader::setUniform(const std::string& name, const jdw::Vec3f& vec)
{
    int location = this->getUniformLocation(name);
    glUniform3f(location, vec.x, vec.y, vec.z);
}
void Shader::setUniform(const std::string& name, const jdw::Vec4f& vec)
{
    int location = this->getUniformLocation(name);
    glUniform4f(location, vec.x, vec.y, vec.z, vec.w);
}

// INT
void Shader::setUniform(const std::string& name, int v)
{
    int location = this->getUniformLocation(name);
    glUniform1i(location, v);
}
void Shader::setUniform(const std::string& name, const jdw::Vec2i& vec)
{
    int location = this->getUniformLocation(name);
    glUniform2i(location, vec.x, vec.y);
}
void Shader::setUniform(const std::string& name, const jdw::Vec3i& vec)
{
    int location = this->getUniformLocation(name);
    glUniform3i(location, vec.x, vec.y, vec.z);
}
void Shader::setUniform(const std::string& name, const jdw::Vec4i& vec)
{
    int location = this->getUniformLocation(name);
    glUniform4i(location, vec.x, vec.y, vec.z, vec.w);
}

// UNSIGNED INT
void Shader::setUniform(const std::string& name, unsigned int v)
{
    int location = this->getUniformLocation(name);
    glUniform1ui(location, v);
}
void Shader::setUniform(const std::string& name, const jdw::Vec2ui& vec)
{
    int location = this->getUniformLocation(name);
    glUniform2ui(location, vec.x, vec.y);
}
void Shader::setUniform(const std::string& name, const jdw::Vec3ui& vec)
{
    int location = this->getUniformLocation(name);
    glUniform3ui(location, vec.x, vec.y, vec.z);
}
void Shader::setUniform(const std::string& name, const jdw::Vec4ui& vec)
{
    int location = this->getUniformLocation(name);
    glUniform4ui(location, vec.x, vec.y, vec.z, vec.w);
}

// 4x4 MATRIX
void Shader::setUniform(const std::string& name, const jdw::Mat4f& mat)
{
    int location = this->getUniformLocation(name);
    glUniformMatrix4fv(location, 1, GL_FALSE, mat.getPtr());
}

int Shader::getUniformLocation(const std::string& name)
{
    if (mUniformCache.find(name) != mUniformCache.end()) return mUniformCache[name];
    int location = glGetUniformLocation(mID, name.c_str());
#ifdef DEBUGGING_GL
    if (location == -1) std::cout << "Warning, no uniform: " << name << "\n";
#endif
    mUniformCache[name] = location;
    return location;
}
