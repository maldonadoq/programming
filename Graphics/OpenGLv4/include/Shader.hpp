#ifndef __SHADER_HPP__
#define __SHADER_HPP__

#include <string>
#include <glad/gl.h>
#include <glm/glm.hpp>

class Shader
{
private:
    GLuint program;
    std::string readFile(const std::string &path);
    GLuint compileShader(GLenum type, const std::string &source);

public:
    Shader(const std::string &vertexPath, const std::string &fragmentPath);
    ~Shader();

    void use() const;
    void setMat4(const std::string &name, const glm::mat4 &matrix) const;
    void setVec3(const std::string &name, const glm::vec3 &value) const;
};

#endif // __SHADER_HPP__