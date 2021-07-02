#include "Shader.h"
#include <iostream>
#include <sstream>
#include "../core/glfunctions.h"

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

static GLuint createShader(const std::string& vertexShader, const std::string& fragmentShader)
{
    GLuint program = glCreateProgram();
    GLuint vs = compileShader(vertexShader.c_str(), GL_VERTEX_SHADER);
    GLuint fs = compileShader(fragmentShader.c_str(), GL_FRAGMENT_SHADER);
    glAttachShader(program, vs); glAttachShader(program, fs);
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
    return program;
}


Shader::Shader(const std::string& shader)
{
    // Split shader
    std::istringstream ss(shader);
    std::string vertexShader, fragmentShader;

    // Dolar sign used as a delimiter
    std::getline(ss, vertexShader, '$');
    std::getline(ss, fragmentShader, '$');

    mID = createShader(vertexShader, fragmentShader);
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

void Shader::setUniform(const std::string& name, float v0, float v1, float v2, float v3)
{
    int location = this->getUniformLocation(name);
    glUniform4f(location, v0, v1, v2, v3);
}

void Shader::setUniform(const std::string& name, int v)
{
    int location = this->getUniformLocation(name);
    glUniform1i(location, v);
}

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
