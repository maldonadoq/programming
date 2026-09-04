#include "Scene.hpp"
#include "PrimitiveFactory.hpp"

Scene::Scene()
    : cube(PrimitiveFactory::cube(2.0f)),
      sphere(PrimitiveFactory::sphere(1.3f, 20, 12)),
      cone(PrimitiveFactory::cone(1.4f, 3.0f, 20)),
      torus(PrimitiveFactory::torus(1.2f, 0.3f, 24, 12)),
      grid(PrimitiveFactory::grid(20, 1.0f)),
      axisX(PrimitiveFactory::line(6, 0, 0)),
      axisY(PrimitiveFactory::line(0, 6, 0)),
      axisZ(PrimitiveFactory::line(0, 0, 6))
{
    createObjects();
}

void Scene::createObjects()
{
    SceneObject cubeObject;
    cubeObject.mesh = &cube;
    cubeObject.transform.position = glm::vec3(-3.0f, 1.0f, 0.0f);
    cubeObject.color = glm::vec3(1.0f, 0.3f, 0.3f);
    objects.push_back(cubeObject);

    SceneObject sphereObject;
    sphereObject.mesh = &sphere;
    sphereObject.transform.position = glm::vec3(3.0f, 1.5f, -4.0f);
    sphereObject.color = glm::vec3(0.2f, 1.0f, 0.3f);
    objects.push_back(sphereObject);

    SceneObject coneObject;
    coneObject.mesh = &cone;
    coneObject.transform.position = glm::vec3(0.0f, 0.0f, -8.0f);
    coneObject.color = glm::vec3(0.2f, 0.5f, 1.0f);
    objects.push_back(coneObject);

    SceneObject torusObject;
    torusObject.mesh = &torus;
    torusObject.transform.position = glm::vec3(-4.0f, 1.5f, -12.0f);
    torusObject.color = glm::vec3(1.0f, 1.0f, 0.2f);
    objects.push_back(torusObject);

    SceneObject cube2;
    cube2.mesh = &cube;
    cube2.transform.position = glm::vec3(4.0f, 1.0f, -15.0f);
    cube2.transform.rotation = glm::vec3(20.0f, 35.0f, 0.0f);
    cube2.transform.scale = glm::vec3(1.2f);
    cube2.color = glm::vec3(1.0f, 0.3f, 1.0f);
    objects.push_back(cube2);
}

void Scene::drawAxes(const Shader &shader)
{
    shader.setMat4("model", glm::mat4(1.0f));

    shader.setVec3("color", glm::vec3(1, 0, 0));
    axisX.draw();

    shader.setVec3("color", glm::vec3(0, 1, 0));
    axisY.draw();

    shader.setVec3("color", glm::vec3(0, 0, 1));
    axisZ.draw();
}

void Scene::draw(const Shader &shader)
{
    shader.setMat4("model", glm::mat4(1.0f));
    shader.setVec3("color", glm::vec3(0.25f));
    grid.draw();

    drawAxes(shader);

    for (const SceneObject &object : objects)
    {
        shader.setMat4("model", object.transform.getModelMatrix());
        shader.setVec3("color", object.color);
        object.mesh->draw();
    }
}