#ifndef __SCENE_HPP__
#define __SCENE_HPP__

#include <vector>
#include <glm/glm.hpp>

#include "Mesh.hpp"
#include "Shader.hpp"
#include "Transform.hpp"

struct SceneObject
{
    Mesh *mesh;
    Transform transform;
    glm::vec3 color;
};

class Scene
{
private:
    Mesh cube;
    Mesh sphere;
    Mesh cone;
    Mesh torus;
    Mesh grid;
    Mesh axisX;
    Mesh axisY;
    Mesh axisZ;

    std::vector<SceneObject> objects;

    void createObjects();
    void drawAxes(const Shader &shader);

public:
    Scene();

    void draw(const Shader &shader);
};

#endif // __SCENE_HPP__