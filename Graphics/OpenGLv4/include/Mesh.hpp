#ifndef __MESH_HPP__
#define __MESH_HPP__

#include <vector>
#include <glad/gl.h>

struct Geometry
{
    std::vector<float> vertices;
    std::vector<unsigned int> indices;
};

class Mesh
{
private:
    GLuint VAO;
    GLuint VBO;
    GLuint EBO;

    GLsizei indexCount;

public:
    Mesh(const Geometry &geometry);
    ~Mesh();

    Mesh(const Mesh &) = delete;
    Mesh &operator=(const Mesh &) = delete;

    void draw() const;
};

#endif // __MESH_HPP__