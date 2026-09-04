#include "Shader.hpp"

#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>

#include <glm/gtc/type_ptr.hpp>

std::string Shader::readFile(const std::string &path)
{
    std::ifstream file(path);

    if (!file.is_open())
    {
        throw std::runtime_error(
            "No se pudo abrir: " + path);
    }

    std::stringstream buffer;

    buffer << file.rdbuf();

    return buffer.str();
}

GLuint Shader::compileShader(GLenum type, const std::string &source)
{
    GLuint shader = glCreateShader(type);
    const char *code = source.c_str();

    glShaderSource(shader, 1, &code, nullptr);
    glCompileShader(shader);

    GLint success;

    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        char log[1024];

        glGetShaderInfoLog(shader, 1024, nullptr, log);
        std::cerr << "Error compilando shader:\n"
                  << log << "\n";
    }

    return shader;
}

Shader::Shader(const std::string &vertexPath, const std::string &fragmentPath)
{
    std::string vertexSource = readFile(vertexPath);
    std::string fragmentSource = readFile(fragmentPath);

    GLuint vertexShader = compileShader(GL_VERTEX_SHADER, vertexSource);
    GLuint fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentSource);

    program = glCreateProgram();

    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);

    glLinkProgram(program);

    GLint success;

    glGetProgramiv(program, GL_LINK_STATUS, &success);

    if (!success)
    {
        char log[1024];
        glGetProgramInfoLog(program, 1024, nullptr, log);
        std::cerr << "Error enlazando programa:\n"
                  << log << "\n";
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

Shader::~Shader()
{
    glDeleteProgram(program);
}

void Shader::use() const
{
    glUseProgram(program);
}

void Shader::setMat4(const std::string &name, const glm::mat4 &matrix) const
{
    GLint location = glGetUniformLocation(program, name.c_str());
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
}

void Shader::setVec3(const std::string &name, const glm::vec3 &value) const
{
    GLint location = glGetUniformLocation(program, name.c_str());
    glUniform3fv(location, 1, glm::value_ptr(value));
}